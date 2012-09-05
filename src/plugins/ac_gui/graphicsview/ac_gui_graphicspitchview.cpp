/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2012 Andrew Fillebrown.
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
#include <idatabaseobjectfactory.h>
#include <ieditor.h>
#include <ientity.h>
#include <imodel.h>
#include <imodelitem.h>
#include <QApplication>
#include <QKeyEvent>
#include <QMessageBox>
#include <QModelIndexList>

using namespace Ac;
using namespace Qt;

class GraphicsPitchViewPrivate
{
public:
    GraphicsPitchView *q;
    QModelIndexList trackSSIndexes;
    QList<IEntity*> currentNotes;
    QList<IEntity*> currentPitchCurves;
    PointList currentPoints;
    uint creatingNotes : 1;
    uint notesStarted : 1;
    uint curve : 1;

    GraphicsPitchViewPrivate(GraphicsPitchView *q)
        :   q(q)
        ,   creatingNotes(false)
        ,   notesStarted(false)
        ,   curve(false)
    {}

    void startNote(const QPoint &pos)
    {
//        IEditor::instance()->startCreating();

//        IModel *model = IModel::instance();

//        const int trackSS_n = trackSSIndexes.count();
//        currentNotes.reserve(trackSS_n);
//        currentPitchCurves.reserve(trackSS_n);

//        for (int i = 0;  i < trackSS_n;  ++i) {
//            const QModelIndex &trackIndex = trackSSIndexes.at(i);
//            IModelItem *notesItem = model->itemFromIndex(trackIndex)->findModelItemList(NoteItem);
//            const QModelIndex notesIndex = model->indexFromItem(notesItem);

//            IModelItem *noteItem = ObjectFactory::instance()->create(NoteItem);
//            model->insertItem(noteItem, model->rowCount(notesIndex), notesIndex);

//            IEntity *noteEntity = query<IEntity>(noteItem);
//            const QList<IEntity*> pitchSubEntities = noteEntity->subEntities(PitchScene);
//            IEntity *pitchCurveEntity = pitchSubEntities.first();

//            trackSSIndexes.append(trackIndex);
//            currentNotes.append(noteEntity);
//            currentPitchCurves.append(pitchCurveEntity);
//        }

//        const QPointF scenePos = q->sceneTransform().inverted().map(QPointF(pos));
//        currentPoints.append(scenePos);

//        addNotePoint(pos);
//        notesStarted = true;
    }

    void addNotePoint(const QPoint &pos)
    {
//        if (ControlModifier & QApplication::keyboardModifiers())
//            currentPoints.last().curveType = BezierCurve;

//        const QPointF scenePos = q->sceneTransform().inverted().map(QPointF(pos));
//        currentPoints.append(scenePos);

//        const int notes_n = currentNotes.count();
//        for (int i = 0;  i < notes_n;  ++i)
//            currentPitchCurves.at(i)->setPoints(currentPoints);
    }

    void moveNotePoint(const QPoint &pos)
    {
//        const QPointF scenePos = q->sceneTransform().inverted().map(QPointF(pos));
//        currentPoints[currentPoints.count() - 1].pos = scenePos;

//        const int notes_n = currentNotes.count();
//        for (int i = 0;  i < notes_n;  ++i)
//            currentPitchCurves[i]->setPoints(currentPoints);
    }

    void finishNote()
    {
//        if (currentPoints.count() <= 2) {
//            cancelNote();
//            return;
//        }

//        currentPoints.removeLast();

//        IModel *model = IModel::instance();
//        const int notes_n = currentNotes.count();

//        QModelIndexList notesIndexes;
//        notesIndexes.reserve(notes_n);

//        QList<IModelItem*> noteItems;
//        noteItems.reserve(notes_n);

//        for (int i = 0;  i < notes_n;  ++i) {
//            currentPitchCurves[i]->setPoints(currentPoints);

//            const QModelIndex &trackIndex = trackSSIndexes.at(i);
//            IModelItem *notesItem = model->itemFromIndex(trackIndex)->findModelItemList(NoteItem);
//            const QModelIndex notesIndex = model->indexFromItem(notesItem);
//            model->removeItem(model->rowCount(notesIndex) - 1, notesIndex);

//            notesIndexes.append(notesIndex);
//            noteItems.append(query<IModelItem>(currentNotes.at(i)));
//        }

//        IEditor *editor = IEditor::instance();
//        editor->finishCreating();
//        editor->beginCommand();

//        for (int i = 0;  i < notes_n;  ++i)
//            model->insertItem(noteItems.at(i), model->rowCount(notesIndexes.at(i)), notesIndexes.at(i));

//        editor->endCommand();
//        endNote();
    }

    void cancelNote()
    {
//        IModel *model = IModel::instance();
//        const int notes_n = currentNotes.count();

//        for (int i = 0;  i < notes_n;  ++i) {
//            const QModelIndex &trackIndex = trackSSIndexes.at(i);
//            IModelItem *notesItem = model->itemFromIndex(trackIndex)->findModelItemList(NoteItem);
//            const QModelIndex notesIndex = model->indexFromItem(notesItem);
//            model->removeItem(model->rowCount(notesIndex) - 1, notesIndex);
//        }

//        qDeleteAll(currentNotes);

//        IEditor::instance()->finishCreating();
//        endNote();
    }

    void endNote()
    {
//        notesStarted = false;
//        creatingNotes = false;
//        trackSSIndexes.clear();
//        currentNotes.clear();
//        currentPitchCurves.clear();
//        currentPoints.clear();
//        q->setCursor(GraphicsView::normalCrosshair());
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
//    d->trackSSIndexes = IModel::instance()->findIndexes(TrackItem, RecordingRole, true);
//    if (d->trackSSIndexes.isEmpty())
//        QMessageBox::warning(this, PRO_NAME_STR, "No tracks are recording.");
//    else {
//        setCursor(creationCrosshair());
//        d->creatingNotes = true;
//    }
}

void GraphicsPitchView::mousePressEvent(QMouseEvent *event)
{
    if (d->creatingNotes) {
        if (LeftButton == event->button()) {
            if (!d->currentPoints.count())
                d->startNote(event->pos());
            else
                d->addNotePoint(event->pos());
            setFocus(MouseFocusReason);
        }
    } else
        GraphicsHorizontalView::mousePressEvent(event);
}

void GraphicsPitchView::mouseMoveEvent(QMouseEvent *event)
{
    if (d->creatingNotes) {
        if (d->notesStarted)
            d->moveNotePoint(event->pos());
    } else
        GraphicsHorizontalView::mouseMoveEvent(event);
}

void GraphicsPitchView::mouseReleaseEvent(QMouseEvent *event)
{
    if (d->creatingNotes) {
        if (RightButton == event->button()) {
            d->finishNote();
            event->accept();
        }
    } else
        GraphicsHorizontalView::mouseReleaseEvent(event);
}

void GraphicsPitchView::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (d->creatingNotes) {
        if (LeftButton == event->button()) {
            d->finishNote();
            event->accept();
        }
    } else
        GraphicsHorizontalView::mouseDoubleClickEvent(event);
}

void GraphicsPitchView::keyReleaseEvent(QKeyEvent *event)
{
    if (d->creatingNotes) {
        const int key = event->key();
        switch (key) {
        case Key_Enter:
            d->finishNote();
            break;
        case Key_Escape:
            d->cancelNote();
            break;
        }
    } else
        GraphicsHorizontalView::keyReleaseEvent(event);
}
