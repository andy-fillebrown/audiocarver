/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2013 Andrew Fillebrown.
**
** Contact: Andy Fillebrown (andy.fillebrown@gmail.com)
**
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file.  Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
**************************************************************************/

#include "ac_gui_graphicspitchview.h"
#include "ac_gui_constants.h"
#include "ac_gui_graphicsviewmanager.h"
#include "ac_gui_namespace.h"
#include <ac_core_namespace.h>
#include <ac_core_point.h>
#include <iaggregate.h>
#include <idatabase.h>
#include <idatabaseobjectfactory.h>
#include <ieditor.h>
#include <igraphicsdelegate.h>
#include <igraphicsgrip.h>
#include <igraphicsgriplist.h>
#include <igraphicsitem.h>
#include <imodel.h>
#include <imodelitem.h>
#include <iselectionset.h>
#include <iundomanager.h>
#include <QApplication>
#include <QKeyEvent>
#include <QMessageBox>
#include <QGraphicsItem>

using namespace Ac;
using namespace Qt;

class GraphicsPitchViewPrivate
{
public:
    GraphicsPitchView *q;
    IModelItem *noteList;
    IModelItem *noteItem;
    IGraphicsItem *noteGraphicsItem;
    IGraphicsGripList *pitchGrips;
    IGraphicsDelegate *pitchDelegate;
    PointList points;
    QList<IGraphicsItem*> noteSS;
    QList<IGraphicsGripList*> noteGripLists;
    QList<IGraphicsGrip*> highlightedGrips;
    QPointF origNotePos;
    uint creatingNote : 1;
    uint noteStarted : 1;
    uint curve : 1;
    uint movingNotes : 1;
    uint noteMoveStarted : 1;


    GraphicsPitchViewPrivate(GraphicsPitchView *q)
        :   q(q)
        ,   noteList(0)
        ,   noteItem(0)
        ,   noteGraphicsItem(0)
        ,   pitchGrips(0)
        ,   pitchDelegate(0)
        ,   creatingNote(false)
        ,   noteStarted(false)
        ,   curve(false)
        ,   movingNotes(false)
        ,   noteMoveStarted(false)
    {}

    void startNote(const QPoint &pos)
    {
        IUndoManager::instance()->pause();
        noteItem = query<IModelItem>(IDatabaseObjectFactory::instance()->create(NoteItem));
        noteList->appendItem(noteItem);
        noteGraphicsItem = query<IGraphicsItem>(noteItem);
        IGraphicsItem *pitchcurve_graphics = noteGraphicsItem->findItem(PitchCurveItem);
        pitchGrips = query<IGraphicsGripList>(pitchcurve_graphics);
        pitchDelegate = query<IGraphicsDelegate>(pitchcurve_graphics);
        QPointF scene_pos = GraphicsViewManager::instance()->snappedScenePos(PitchScene, pos);
        points.append(scene_pos);
        addNotePoint(pos);
        noteStarted = true;
    }

    void addNotePoint(const QPoint &pos)
    {
        if (ControlModifier & QApplication::keyboardModifiers())
            points.last().curveType = BezierCurve;
        QPointF scene_pos = GraphicsViewManager::instance()->snappedScenePos(PitchScene, pos);
        points.append(scene_pos);
        pitchGrips->update(PointsRole, QVariant::fromValue(points));
        pitchDelegate->updateGraphics();
    }

    void moveNotePoint(const QPoint &pos)
    {
        QPointF scene_pos = GraphicsViewManager::instance()->snappedScenePos(PitchScene, pos);
        points[points.count() - 1].pos = scene_pos;
        pitchGrips->update(PointsRole, QVariant::fromValue(points));
        pitchDelegate->updateGraphics();
    }

    void finishNote()
    {
        if (points.count() <= 2) {
            cancelNote();
            return;
        }
        points.removeLast();
        pitchGrips->update(PointsRole, QVariant::fromValue(points));
        pitchDelegate->updateGraphics();
        pitchDelegate->updateModel();
        noteList->removeItem(noteItem);
        IUndoManager *undo_manager = IUndoManager::instance();
        undo_manager->resume();
        undo_manager->beginCommand();
        noteList->appendItem(noteItem);
        undo_manager->endCommand();
        endNote();
    }

    void cancelNote()
    {
        noteList->removeItem(noteItem);
        delete query<IAggregate>(noteItem);
        IUndoManager::instance()->resume();
        endNote();
    }

    void endNote()
    {
        noteList = 0;
        noteItem = 0;
        noteGraphicsItem = 0;
        pitchGrips = 0;
        pitchDelegate = 0;
        points.clear();
        creatingNote = false;
        noteStarted = false;
        curve = false;
        q->setCursor(GraphicsView::normalCrosshair());
    }

    void highlightGrips(const QPoint &pos)
    {
        const QList<QGraphicsItem*> items = q->items(GraphicsView::pickOneRect(pos));
        foreach (QGraphicsItem *item, items) {
            IUnknown *unknown = reinterpret_cast<IUnknown*>(qvariant_cast<quintptr>(item->data(0)));
            if (unknown) {
                IGraphicsGrip *grip = query<IGraphicsGrip>(unknown);
                if (grip) {
                    grip->update(HighlightRole, FullHighlight);
                    highlightedGrips.append(grip);
                }
            }
        }
    }

    void clearHighlightedGrips()
    {
        foreach (IGraphicsGrip *grip, highlightedGrips)
            grip->update(HighlightRole, NoHighlight);
        highlightedGrips.clear();
    }

    void startMovingNotes(const QPoint &pos)
    {
        clearHighlightedGrips();
        origNotePos = GraphicsViewManager::instance()->snappedScenePos(PitchScene, pos);
        foreach (IGraphicsItem *note, noteSS)
            noteGripLists.append(query<IGraphicsGripList>(note->findItem(PitchCurveItem)));
        noteMoveStarted = true;
        foreach (IGraphicsGripList *griplist, noteGripLists) {
            QList<IGraphicsGrip*> grips = griplist->grips();
            foreach (IGraphicsGrip *grip, grips)
                grip->update(OriginalPositionRole, grip->position());
        }
        highlightGrips(pos);
    }

    void moveNotes(const QPoint &pos)
    {
        const QPointF scene_pos = GraphicsViewManager::instance()->snappedScenePos(PitchScene, pos);
        foreach (IGraphicsGripList *griplist, noteGripLists) {
            QList<IGraphicsGrip*> grips = griplist->grips();
            foreach (IGraphicsGrip *grip, grips) {
                grip->reset();
                grip->update(PositionRole, QVariant::fromValue(grip->originalPosition() + scene_pos - origNotePos));
            }
            query<IGraphicsDelegate>(griplist)->updateGraphics();
        }
    }

    void finishMovingNotes(const QPoint &pos)
    {
        moveNotes(pos);
        IUndoManager *undo_manager = IUndoManager::instance();
        undo_manager->beginCommand();
        foreach (IGraphicsGripList *griplist, noteGripLists) {
            QList<IGraphicsGrip*> grips = griplist->grips();
            foreach (IGraphicsGrip *grip, grips)
                grip->update(OriginalPositionRole, grip->position());
            query<IGraphicsDelegate>(griplist)->updateModel();
        }
        undo_manager->endCommand();
        endMovingNotes();
    }

    void cancelMovingNotes()
    {
        foreach (IGraphicsGripList *griplist, noteGripLists) {
            QList<IGraphicsGrip*> grips = griplist->grips();
            foreach (IGraphicsGrip *grip, grips) {
                grip->update(PositionRole, QVariant::fromValue(grip->originalPosition()));
            }
            query<IGraphicsDelegate>(griplist)->updateGraphics();
        }
        endMovingNotes();
    }

    void endMovingNotes()
    {
        noteMoveStarted = false;
        movingNotes = false;
        noteGripLists.clear();
        noteSS.clear();
        q->setCursor(GraphicsView::normalCrosshair());
        clearHighlightedGrips();
    }
};

GraphicsPitchView::GraphicsPitchView(QGraphicsScene *scene, QWidget *parent)
    :   GraphicsHorizontalView(scene, parent)
    ,   d(new GraphicsPitchViewPrivate(this))
{
    setObjectName("PitchView");
    setStyleSheet("QFrame {"
                  "border-top: 0px solid palette(shadow);"
                  "border-bottom: 1px solid palette(shadow);"
                  "border-left: 1px solid palette(shadow);"
                  "border-right: 1px solid palette(shadow);"
                  "}");
}

GraphicsPitchView::~GraphicsPitchView()
{
    delete d;
}

int GraphicsPitchView::sceneType() const
{
    return PitchScene;
}

int GraphicsPitchView::verticalPositionRole() const
{
    return PitchPositionRole;
}

int GraphicsPitchView::verticalScaleRole() const
{
    return PitchScaleRole;
}

qreal GraphicsPitchView::sceneHeight() const
{
    return qreal(127.0f) / GraphicsViewManager::instance()->scale(PitchScaleRole);
}

QPointF GraphicsPitchView::sceneCenter() const
{
    GraphicsViewManager *vm = GraphicsViewManager::instance();
    return QPointF(vm->position(TimePositionRole), -vm->position(PitchPositionRole));
}

void GraphicsPitchView::createNote()
{
    IModelItem *root_item = IDatabase::instance()->rootItem();
    IModelItem *tracklist_item = root_item->findItem(TrackListItem);
    IModelItem *track_item = 0;
    if (tracklist_item && tracklist_item->itemCount())
       track_item = tracklist_item->itemAt(0);
    if (!track_item)
        QMessageBox::warning(this, PRO_NAME_STR, "No tracks found.");
    else {
        d->noteList = track_item->findItem(NoteListItem);
        setCursor(creationCrosshair());
        d->creatingNote = true;
    }
}

void GraphicsPitchView::moveNotes()
{
    d->noteSS = IEditor::instance()->currentSelection(NoteItem)->items();
    if (d->noteSS.isEmpty())
        QMessageBox::warning(this, PRO_NAME_STR, "No notes selected.");
    else {
        setCursor(creationCrosshair());
        d->movingNotes = true;
    }
}

void GraphicsPitchView::mousePressEvent(QMouseEvent *event)
{
    // Don't let the base class do a selection operation if notes are being
    // created or moved.
    if (d->creatingNote || d->movingNotes)
        return;
    GraphicsHorizontalView::mousePressEvent(event);
}

void GraphicsPitchView::mouseMoveEvent(QMouseEvent *event)
{
    if (d->creatingNote) {
        if (d->noteStarted)
            d->moveNotePoint(event->pos());
        return;
    }
    if (d->movingNotes) {
        if (d->noteMoveStarted)
            d->moveNotes(event->pos());
        else {
            d->clearHighlightedGrips();
            d->highlightGrips(event->pos());
        }
        event->accept();
        return;
    }
    GraphicsHorizontalView::mouseMoveEvent(event);
}

void GraphicsPitchView::mouseReleaseEvent(QMouseEvent *event)
{
    if (LeftButton == event->button()) {
        if (d->creatingNote) {
            if (!d->points.count())
                d->startNote(event->pos());
            else
                d->addNotePoint(event->pos());
            setFocus(MouseFocusReason);
            return;
        }
        if (d->movingNotes) {
            if (!d->noteMoveStarted)
                d->startMovingNotes(event->pos());
            else
                d->finishMovingNotes(event->pos());
            event->accept();
            return;
        }
    }
    if (RightButton == event->button()) {
        if (d->creatingNote) {
            d->finishNote();
            event->accept();
            return;
        }
    }
    GraphicsHorizontalView::mouseReleaseEvent(event);
}

void GraphicsPitchView::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (d->creatingNote) {
        if (LeftButton == event->button()) {
            d->finishNote();
            event->accept();
        }
    } else
        GraphicsHorizontalView::mouseDoubleClickEvent(event);
}

void GraphicsPitchView::keyReleaseEvent(QKeyEvent *event)
{
    const int key = event->key();
    switch (key) {
    case Key_Enter:
        if (d->creatingNote)
            d->finishNote();
        return;
    case Key_Escape:
        if (d->creatingNote)
            d->cancelNote();
        else if (d->movingNotes)
            d->cancelMovingNotes();
        return;
    }
    GraphicsHorizontalView::keyReleaseEvent(event);
}
