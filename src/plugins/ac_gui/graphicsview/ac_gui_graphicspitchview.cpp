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
#include <igraphicsitem.h>
#include <igriplistdata.h>
#include <imodel.h>
#include <imodelitemlist.h>
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
    IModelItemList *noteList;
    IModelItem *noteItem;
    IGraphicsItem *noteGraphicsItem;
    IGripListData *pitchGrips;
    IGraphicsDelegate *pitchDelegate;
    PointList points;
    uint creatingNote : 1;
    uint noteStarted : 1;
    uint curve : 1;

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
    {}

    void startNote(const QPoint &pos)
    {
        IEditor::instance()->startCreating();
        noteItem = QUERY(IModelItem, IDatabaseObjectFactory::instance()->create(NoteItem));
        noteList->append(noteItem);
        noteGraphicsItem = QUERY(IGraphicsItem, noteItem);
        IGraphicsItem *pitchcurve_gitem = noteGraphicsItem->findItem(PitchCurveItem);
        pitchGrips = QUERY(IGripListData, pitchcurve_gitem->findItem(GripListItem));
        pitchDelegate = QUERY(IGraphicsDelegate, pitchcurve_gitem);
        const QPointF scenePos = q->sceneTransform().inverted().map(QPointF(pos));
        points.append(scenePos);
        addNotePoint(pos);
        noteStarted = true;
    }

    void addNotePoint(const QPoint &pos)
    {
        if (ControlModifier & QApplication::keyboardModifiers())
            points.last().curveType = BezierCurve;
        const QPointF scene_pos = q->sceneTransform().inverted().map(QPointF(pos));
        points.append(scene_pos);
        pitchGrips->update(PointsRole, QVariant::fromValue(points));
        pitchDelegate->updateGraphics();
    }

    void moveNotePoint(const QPoint &pos)
    {
        const QPointF scene_pos = q->sceneTransform().inverted().map(QPointF(pos));
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
        noteList->remove(noteItem);
        IEditor *editor = IEditor::instance();
        editor->finishCreating();
        editor->beginCommand();
        noteList->append(noteItem);
        editor->endCommand();
        endNote();
    }

    void cancelNote()
    {
        noteList->remove(noteItem);
        delete QUERY(IAggregate, noteItem);
        IEditor::instance()->finishCreating();
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
    IModelItem *tracklist_item = root_item->findList(TrackItem);
    IModelItem *track_item = 0;
    if (tracklist_item && tracklist_item->count())
       track_item = tracklist_item->at(0);
    if (!track_item)
        QMessageBox::warning(this, PRO_NAME_STR, "No tracks found.");
    else {
        d->noteList = track_item->findList(NoteItem);
        setCursor(creationCrosshair());
        d->creatingNote = true;
    }
}

void GraphicsPitchView::mousePressEvent(QMouseEvent *event)
{
    if (d->creatingNote) {
        if (LeftButton == event->button()) {
            if (!d->points.count())
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
    if (d->creatingNote) {
        if (d->noteStarted)
            d->moveNotePoint(event->pos());
    } else
        GraphicsHorizontalView::mouseMoveEvent(event);
}

void GraphicsPitchView::mouseReleaseEvent(QMouseEvent *event)
{
    if (d->creatingNote) {
        if (RightButton == event->button()) {
            d->finishNote();
            event->accept();
        }
    } else
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
    if (d->creatingNote) {
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
