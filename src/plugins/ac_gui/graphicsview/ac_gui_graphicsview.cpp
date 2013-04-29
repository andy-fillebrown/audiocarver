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

#include "ac_gui_graphicsview.h"
//#include <ac_gui_graphicsentityitem.h>
//#include <ac_gui_graphicsgripitem.h>
#include "ac_gui_graphicsrootnode.h"
#include "ac_gui_graphicsviewmanager.h"
#include "ac_gui_griplist_tools.h"
#include "ac_gui_namespace.h"
#include <ac_core_point.h>
//#include <ac_gripselectionmodel.h>
//#include <ac_noteselectionmodel.h>
//#include <ac_trackselectionmodel.h>
#include <iaggregate.h>
#include <idatabase.h>
#include <ieditor.h>
#include <igraphicsdelegate.h>
#include <igraphicsgrip.h>
#include <igraphicsgriplist.h>
#include <igraphicsitem.h>
#include <imodel.h>
#include <imodelitem.h>
#include <iplaycursor.h>
#include <iselectionset.h>
#include <QApplication>
#include <QGraphicsRectItem>
#include <QMouseEvent>
#include <QUndoStack>
#include <qmath.h>

#include <QtDebug>

using namespace Ac;
using namespace Mi;
using namespace Qt;

enum ViewState {
    Zooming = 1,
    Panning
};

enum DragState {
    Picking = 1,
    DraggingGrips,
    CancelledGripDrag
};

class GraphicsViewPrivate
{
public:
    GraphicsView *q;
    QPoint dragStartPos;
    QPoint curPos;
    qreal zoomStartScaleX;
    qreal zoomStartScaleY;
    QPointF zoomStartPosDC;
    QPointF zoomCenterOffsetDC;
    QRect prevZoomGlyphRect;
    QPointF panStartCenter;
    QGraphicsRectItem *pickBox;
    QList<IGraphicsItem*> pickedEntities;
    QList<IGraphicsGrip*> pickedGrips;
    IGraphicsGrip *curGrip;
    QList<IGraphicsItem*> hoveredEntities;
    QList<IGraphicsGrip*> hoveredGrips;
    QList<IGraphicsDelegate*> delegatesToUpdate;
    GraphicsRootNode *rootNode;
    IPlayCursor *playCursor;
    QCursor previousCursor;
    uint playCursorHovered : 1;
    uint viewState : 2;
    uint dragState : 2;
    uint keepGripsPicked : 1;
    uint gripsDragged : 1;
    uint insertingPoints : 1;
    uint dirty : 1;

    GraphicsViewPrivate(GraphicsView *q)
        :   q(q)
        ,   pickBox(new QGraphicsRectItem)
        ,   curGrip(0)
        ,   rootNode(new GraphicsRootNode)
        ,   playCursor(0)
        ,   playCursorHovered(false)
        ,   viewState(0)
        ,   dragState(0)
        ,   keepGripsPicked(false)
        ,   gripsDragged(false)
        ,   insertingPoints(false)
        ,   dirty(true)
    {
        QGraphicsScene *scene = q->scene();
        scene->addItem(rootNode);
        rootNode->setZValue(Q_FLOAT_MAX - 1.0f);
        scene->addItem(pickBox);
        pickBox->setZValue(Q_FLOAT_MAX);
        pickBox->setPen(QPen(QColor(0, 0, 255)));
        pickBox->setBrush(QBrush(QColor(0, 0, 255, 63)));
        pickBox->hide();
    }

    virtual ~GraphicsViewPrivate()
    {}

    QPointF startPosDC(const QPoint &pos)
    {
        return q->sceneTransform().inverted().map(QPointF(pos) + q->sceneOffset());
    }

    QPointF centerOffsetDC(const QPointF &posDC)
    {
        const GraphicsViewManager *vm = GraphicsViewManager::instance();
        return q->sceneScale().map(QPointF(vm->position(q->horizontalPositionRole()), vm->position(q->verticalPositionRole())) - posDC);
    }

    void recenter(const QPointF &startPosDC, const QPointF &centerOffsetDC)
    {
        const QPointF center = startPosDC + QTransform::fromScale(q->sceneWidth() / q->width(), -q->sceneHeight() / q->height()).map(centerOffsetDC);
        GraphicsViewManager *vm = GraphicsViewManager::instance();
        vm->setPosition(center.x(), q->horizontalPositionRole());
        vm->setPosition(center.y(), q->verticalPositionRole());
    }

    QRect zoomGlyphLineRect() const
    {
        return QRect(dragStartPos, curPos).normalized().adjusted(-1, -1, 2, 2);
    }

    QRect zoomGlyphCircleRect() const
    {
        return QRect(dragStartPos, dragStartPos).adjusted(-2, -2, 4, 4);
    }

    QRect pickOneRect(const QPoint &pos) const
    {
        return QRect(pos.x() - 2, pos.y() - 2, 4, 4);
    }

    void startZoom(const QPoint &pos)
    {
        q->zoomStarting();
        clearHovered();
        viewState = Zooming;
        dragStartPos = pos;
        const GraphicsViewManager *vm = GraphicsViewManager::instance();
        zoomStartScaleX = vm->scale(q->horizontalScaleRole());
        zoomStartScaleY = vm->scale(q->verticalScaleRole());
        zoomStartPosDC = startPosDC(pos);
        zoomCenterOffsetDC = centerOffsetDC(zoomStartPosDC);
        prevZoomGlyphRect = QRect();
        q->update(zoomGlyphCircleRect());
    }

    void zoomTo(const QPoint &pos)
    {
        QPoint offset = pos - dragStartPos;
        const int x = offset.x();
        if (x) {
            qreal scale = qreal(1.0f) + (qreal(qAbs(x)) / qreal(10.0f));
            GraphicsViewManager::instance()->setScale((x < 0 ? qreal(1.0f) / scale : scale) * zoomStartScaleX, q->horizontalScaleRole());
        }
        const int y = offset.y();
        if (y) {
            const qreal scale = qreal(1.0f) + qreal(qAbs(y) / qreal(10.0f));
            GraphicsViewManager::instance()->setScale((0 < y ? qreal(1.0f) / scale : scale) * zoomStartScaleY, q->verticalScaleRole());
        }
        recenter(zoomStartPosDC, zoomCenterOffsetDC);
        if (dirty)
            GraphicsViewManager::instance()->updateViews();
        else {
            const QRect rect = zoomGlyphLineRect();
            q->update(prevZoomGlyphRect.united(rect));
            prevZoomGlyphRect = rect;
        }
    }

    void finishZoom(const QPoint &pos)
    {
        zoomTo(pos);
        viewState = 0;
        q->update(QRect(dragStartPos, dragStartPos).adjusted(-2, -2, 4, 4));
        q->zoomFinished();
    }

    void startPan(const QPoint &pos)
    {
        q->panStarting();
        clearHovered();
        viewState = Panning;
        dragStartPos = pos;
        const GraphicsViewManager *vm = GraphicsViewManager::instance();
        panStartCenter.setX(vm->position(q->horizontalPositionRole()));
        panStartCenter.setY(vm->position(q->verticalPositionRole()));
    }

    void panTo(const QPoint &pos)
    {
        q->setCursor(ClosedHandCursor);
        const QPointF offset = q->sceneScale().inverted().map(QPointF(pos - dragStartPos));
        const QPointF center = panStartCenter - offset;
        GraphicsViewManager *vm = GraphicsViewManager::instance();
        vm->setPosition(center.x(), q->horizontalPositionRole());
        vm->setPosition(center.y(), q->verticalPositionRole());
        vm->updateViews();
    }

    void finishPan(const QPoint &pos)
    {
        panTo(pos);
        viewState = 0;
        q->panFinished();
    }

    void hover()
    {
        clearHovered();
        if (viewState || Picking == dragState || insertingPoints)
            return;
        const QRect view_pick_rect = pickOneRect(curPos);
        const QRectF scene_pick_rect = q->sceneTransform().inverted().mapRect(QRectF(view_pick_rect));
        bool grip_is_hovered = false;
        bool entity_is_hovered = false;
        const QList<QGraphicsItem*> items = q->items(view_pick_rect);
        foreach (QGraphicsItem *item, items) {
            IUnknown *unknown = reinterpret_cast<IUnknown*>(qvariant_cast<quintptr>(item->data(0)));
            if (unknown) {
                IPlayCursor *cursor = query<IPlayCursor>(unknown);
                if (cursor) {
                    playCursorHovered = true;
                    previousCursor = q->cursor();
                    q->setCursor(QCursor(SplitHCursor));
                    break;
                }
                IGraphicsGrip *grip = query<IGraphicsGrip>(unknown);
                if (grip) {
                    grip_is_hovered = true;
                    if (!pickedGrips.contains(grip)) {
                        grip->update(HighlightRole, HoverHighlight);
                        hoveredGrips.append(grip);
                    }
                } else if (!grip_is_hovered) {
                    IGraphicsItem *curve_graphics = query<IGraphicsItem>(unknown);
                    if (curve_graphics && curve_graphics->intersects(scene_pick_rect)) {
                        entity_is_hovered = true;
                        IGraphicsItem *parent_graphics = query<IGraphicsItem>(curve_graphics->parent());
                        if (!pickedEntities.contains(parent_graphics)) {
                            hoveredEntities.append(parent_graphics);
                            parent_graphics->update(HighlightRole, HoverHighlight);
                        }
                    }
                }
                if (!(ShiftModifier & QApplication::keyboardModifiers())
                        && (grip_is_hovered || entity_is_hovered))
                    break;
            }
        }
    }

    void clearHovered()
    {
        if (playCursorHovered) {
            playCursorHovered = false;
            q->setCursor(previousCursor);
        }
        foreach (IGraphicsGrip *grip, hoveredGrips)
            if (!pickedGrips.contains(grip))
                grip->update(HighlightRole, NoHighlight);
        hoveredGrips.clear();
        foreach (IGraphicsItem *entity, hoveredEntities) {
            if (!entityIsPicked(entity))
                entity->update(HighlightRole, NoHighlight);
        }
        hoveredEntities.clear();
    }

    IPlayCursor *findPlayCursor(const QList<QGraphicsItem*> &items)
    {
        IPlayCursor *play_cursor = 0;
//        foreach (QGraphicsItem *item, items) {
//            IUnknown *unknown = static_cast<IUnknown*>(qvariant_cast<void*>(item->data(0)));
//            if (unknown) {
//                play_cursor = QUERY(IPlayCursor, unknown);
//                if (play_cursor)
//                    break;
//            }
//        }
        return play_cursor;
    }

    bool selectPlayCursor(const QPoint &pos)
    {
        playCursor = findPlayCursor(q->items(pickOneRect(pos)));
        return playCursor != 0;
    }

    void dragPlayCursorTo(const QPoint &pos)
    {
        GraphicsViewManager *vm = GraphicsViewManager::instance();
        vm->disableUpdates();
//        const qreal fromScenePos = playCursor->playCursorPosition();
//        const QPointF toScenePos = rootItem->transform().map(q->mapToScene(pos));
//        const qreal sceneOffset = vm->snappedScenePos(toScenePos, q->sceneType()).x() - fromScenePos;
//        playCursor->dragPlayCursorTo(fromScenePos + sceneOffset);
        vm->enableUpdates();
    }

    void finishDraggingPlayCursor(const QPoint &pos)
    {
//        if (!playCursor) {
//            playCursor = findPlayCursor(q->items());
//            if (!playCursor) {
//                qWarning() << Q_FUNC_INFO << ": play cursor not found";
//                return;
//            }
//        }

//        // The view manager might have different view settings than the
//        // database.  Update the database's view settings so they don't
//        // overwrite the view manager's view settings in the view manager's
//        // dataChanged implementation when the cursor position is changed.
//        GraphicsViewManager *vm = GraphicsViewManager::instance();
//        vm->updateDatabase();

////        const qreal fromScenePos = playCursor->playCursorPosition();
////        const QPointF toScenePos = rootItem->transform().map(q->mapToScene(pos));
////        const qreal sceneOffset = vm->snappedScenePos(toScenePos, q->sceneType()).x() - fromScenePos;
////        playCursor->setPlayCursorPosition(fromScenePos + sceneOffset);
//        playCursor = 0;
//        q->setCursor(GraphicsView::normalCrosshair());
    }

    bool selectGrips(const QPoint &pos)
    {
        bool selectedGrip = false;
        const QList<QGraphicsItem*> items = q->items(pickOneRect(pos));
        foreach (QGraphicsItem *item, items) {
            IUnknown *unknown = reinterpret_cast<IUnknown*>(qvariant_cast<quintptr>(item->data(0)));
            if (unknown) {
                IGraphicsGrip *grip = query<IGraphicsGrip>(unknown);
                if (grip) {
                    if (!selectedGrip)
                        clearHovered();
                    selectedGrip = true;
                    dragStartPos = pos;
                    curGrip = grip;
                    if (pickedGrips.contains(grip))
                        keepGripsPicked = true;
                    if (ControlModifier & QApplication::keyboardModifiers()) {
                        grip->update(HighlightRole, NoHighlight);
                        pickedGrips.removeOne(grip);
                    } else {
                        if (ShiftModifier & QApplication::keyboardModifiers())
                            keepGripsPicked = true;
                        else if (!keepGripsPicked)
                            clearPickedGrips();
                        grip->update(HighlightRole, FullHighlight);
                        if (!pickedGrips.contains(grip)) {
                            pickedGrips.append(grip);
                            IGraphicsItem *grip_graphics = query<IGraphicsItem>(grip);
                            IGraphicsDelegate *curve_gdelegate = query<IGraphicsDelegate>(grip_graphics->parent());
                            Q_ASSERT(curve_gdelegate);
                            if (!delegatesToUpdate.contains(curve_gdelegate))
                                delegatesToUpdate.append(curve_gdelegate);
                        }
                    }
                }
            }
        }
        return selectedGrip;
    }

//    void selectAllGrips()
//    {
//        clearPickedGrips();
//        foreach (IGraphicsItem *entity, pickedEntities) {
//            delegatesToUpdate.append(query<IGraphicsDelegate>(entity));
//            const QList<IGraphicsGrip*> &grips = query<IGraphicsGripList>(entity)->grips();
//            pickedGrips.append(grips);
//            foreach (IGraphicsGrip *grip, grips)
//                grip->update(HighlightRole, FullHighlight);
//        }
//    }

//    void startGripDrag()
//    {
//        selectAllGrips();
//        if (pickedGrips.isEmpty())
//            return;
//
//        // Set curGrip to the lowest and earliest grip.
//        curGrip = pickedGrips.first();
//        foreach (IGripData *grip, pickedGrips) {
//            const QPointF pos = grip->position();
//            if (pos.x() < curGrip->position().x()
//                    || (pos.x() == curGrip->position().x()
//                        && pos.y() < curGrip->position().y()))
//                curGrip = grip;
//        }
//
//        startDraggingGrips();
//    }

    void clearPickedGrips()
    {
        keepGripsPicked = false;
        clearHovered();
        foreach (IGraphicsGrip *grip, pickedGrips)
            grip->update(HighlightRole, NoHighlight);
        pickedGrips.clear();
        delegatesToUpdate.clear();
    }

    void startDraggingGrips()
    {
        dragState = DraggingGrips;
        foreach (IGraphicsDelegate *delegate, delegatesToUpdate) {
            IGraphicsItem *curve = query<IGraphicsItem>(delegate);
            IGraphicsGripList *griplist = query<IGraphicsGripList>(curve);
            griplist->update(OriginalPositionRole);
        }
    }

    void dragGripsTo(const QPoint &pos)
    {
        GraphicsViewManager *vm = GraphicsViewManager::instance();
        vm->disableUpdates();
        const QPointF fromScenePos = curGrip->originalPosition();
        const QPointF toScenePos = rootNode->transform().map(q->mapToScene(pos));
        const QPointF sceneOffset = vm->snappedScenePos(toScenePos, q->sceneType()) - fromScenePos;
        foreach (IGraphicsGrip *grip, pickedGrips)
            grip->update(PositionRole, grip->originalPosition() + sceneOffset);
        foreach (IGraphicsDelegate *delegate, delegatesToUpdate)
            delegate->updateGraphics();
        gripsDragged = true;
        vm->enableUpdates();
    }

    void finishDraggingGrips(const QPoint &pos)
    {
        dragGripsTo(pos);
        dragState = 0;
        curGrip = 0;
        if (gripsDragged) {
            IEditor *editor = IEditor::instance();
            editor->beginCommand();
            foreach (IGraphicsDelegate *delegate, delegatesToUpdate)
                delegate->updateModel();
            editor->endCommand();
            gripsDragged = false;
            if (!keepGripsPicked)
                clearPickedGrips();
        }
    }

    void cancelGripDrag()
    {
        dragState = CancelledGripDrag;
        curGrip = 0;
        foreach (IGraphicsGrip *grip, pickedGrips)
            grip->update(PositionRole, grip->originalPosition());
        foreach (IGraphicsDelegate *delegate, delegatesToUpdate)
            delegate->updateGraphics();
        gripsDragged = false;
    }

    QRect pickBoxBounds() const
    {
        return QRect(QPoint(), q->size()).adjusted(0, 0, -2, -1);
    }

    void startPicking(const QPoint &pos)
    {
        dragStartPos = pos;
        dragState = Picking;
    }

    void dragPickBoxTo(const QPoint &pos)
    {
        if (QApplication::startDragDistance() <= (pos - dragStartPos).manhattanLength()) {
            const QRect pickRect = QRect(dragStartPos, pos).normalized().intersected(pickBoxBounds());
            pickBox->setRect(QRectF(q->mapToScene(pickRect.topLeft()), q->mapToScene(pickRect.bottomRight())));
            pickBox->show();
        }
    }

    void finishPicking(const QPoint &pos)
    {
        bool pickOne = false;
        const QRect rect = (pickOne = (pos - dragStartPos).manhattanLength() < QApplication::startDragDistance())
                ? pickOneRect(dragStartPos)
                : QRect(dragStartPos, pos).normalized().intersected(pickBoxBounds());
        const QRectF pickRect = q->sceneTransform().inverted().mapRect(QRectF(rect));
        const QList<QGraphicsItem*> items = q->items(rect);
        QList<IGraphicsItem*> entities;
        foreach (QGraphicsItem *item, items) {
            IUnknown *unknown = reinterpret_cast<IUnknown*>(qvariant_cast<quintptr>(item->data(0)));
            if (unknown) {
                IGraphicsItem *entity = query<IGraphicsItem>(unknown);
                if (entity && entity->intersects(pickRect)) {
                    IGraphicsItem *parent = entity->parent();
                     entities.append(parent);
                     if (pickOne && !(QApplication::keyboardModifiers() & ShiftModifier))
                        break;
                }
            }
        }
        ISelectionSet *ss = query<ISelectionSet>(IEditor::instance()->currentSelection());
        if (entities.count()) {
            if (ControlModifier & QApplication::keyboardModifiers()) {
                QList<IGraphicsItem*> items = ss->items();
                foreach (IGraphicsItem *entity, entities) {
                    if (items.contains(entity))
                        ss->remove(entity);
                    else
                        ss->append(entity);
                }
            } else if (ShiftModifier & QApplication::keyboardModifiers())
                ss->append(entities);
            else {
                ss->clear();
                ss->append(entities);
            }
        } else if (pickOne) {
            if (!pickedGrips.isEmpty())
                GraphicsViewManager::instance()->clearPickedGrips();
            else if (!(ShiftModifier & QApplication::keyboardModifiers()))
                clearPicks();
        }
        if (!pickOne)
            pickBox->hide();
        dragState = 0;
    }

    void clearPicks()
    {
        if (!pickedGrips.isEmpty())
            GraphicsViewManager::instance()->clearPickedGrips();
        else {
            IEditor *editor = IEditor::instance();
            editor->currentSelection()->clear();
            editor->currentSelection(TrackItem)->clear();
        }
    }

    bool entityIsPicked(IGraphicsItem *entity)
    {
        return pickedEntities.contains(entity);
    }

    void setPickedEntities(const QList<IGraphicsItem*> &entities)
    {
        clearPickedEntities();
        appendPickedEntities(entities);
    }

    void appendPickedEntities(const QList<IGraphicsItem*> &entities)
    {
        if (entities.isEmpty())
            return;
        foreach (IGraphicsItem *entity, entities) {
            if (!entityIsPicked(entity)) {
                pickedEntities.append(entity);
                entity->update(HighlightRole, FullHighlight);
            }
        }
        IEditor *editor = IEditor::instance();
        editor->currentSelection(TrackItem)->clear();
    }

    void removePickedEntities(const QList<IGraphicsItem*> &entities)
    {
        if (entities.isEmpty())
            return;
        foreach (IGraphicsItem *entity, entities) {
            pickedEntities.removeOne(entity);
            int curve_count = entity->itemCount();
            for (int i = 0;  i < curve_count;  ++i) {
                IGraphicsItem *curve = entity->itemAt(i);
                if (!curve)
                    continue;
                IGraphicsDelegate *curve_delegate = query<IGraphicsDelegate>(curve);
                delegatesToUpdate.removeOne(curve_delegate);
                for (int i = 0;  i < pickedGrips.count();  ++i) {
                    IGraphicsItem *grip = query<IGraphicsItem>(pickedGrips[i]);
                    if (curve == grip->parent())
                        pickedGrips.removeAt(i--);
                }
                for (int i = 0;  i < hoveredGrips.count();  ++i) {
                    IGraphicsItem *grip = query<IGraphicsItem>(hoveredGrips[i]);
                    if (curve == grip->parent())
                        hoveredGrips.removeAt(i--);
                }
            }
            entity->update(HighlightRole, NoHighlight);
        }
        clearPickedGrips();
    }

    void clearPickedEntities()
    {
        clearPickedGrips();
        QList<IGraphicsItem*> picked_entities = pickedEntities;
        removePickedEntities(picked_entities);
    }

    void insertPoint(const QPoint &pos)
    {
        const QPointF scenePos = GraphicsViewManager::instance()->snappedScenePos(q->sceneTransform().inverted().map(QPointF(pos)), q->sceneType());
        foreach (IGraphicsItem *item, pickedEntities) {
            IGraphicsItem *pitch_item = item->findItem(PitchCurveItem);
            IGraphicsGripList *grips = query<IGraphicsGripList>(pitch_item);
            PointList points = GripList::toPointList(grips);
            Point pt = Point(scenePos);
            if (ControlModifier & QApplication::keyboardModifiers())
                pt.curveType = BezierCurve;
            points.append(pt);
            grips->update(OriginalPositionRole, QVariant::fromValue(points));
            query<IGraphicsDelegate>(pitch_item)->updateGraphics();
        }
    }

    void updateViewSettings()
    {
        const qreal sceneWidth = q->sceneWidth();
        const qreal sceneHeight = q->sceneHeight();
        const qreal viewWidth = q->width();
        const qreal viewHeight = q->height();
        const QRectF sceneRect(0.0f, 0.0f, sceneWidth, sceneHeight);
        const QPointF sceneOffset = q->sceneCenter() - sceneRect.center();
        q->setSceneRect(sceneRect.translated(sceneOffset + q->sceneOffset()));
        q->setTransform(QTransform::fromScale(viewWidth / sceneWidth, viewHeight / sceneHeight));
        dirty = false;
    }
};

const QCursor &GraphicsView::normalCrosshair()
{
    static const QCursor cursor(QPixmap(":/ac_gui/images/crosshair-black.png"));
    return cursor;
}

const QCursor &GraphicsView::creationCrosshair()
{
    static const QCursor cursor(QPixmap(":/ac_gui/images/crosshair-red.png"));
    return cursor;
}

static const QCursor &zoomCursor()
{
    static const QCursor cursor(QPixmap(":/ac_gui/images/zoom-cursor.png"));
    return cursor;
}

GraphicsView::GraphicsView(QGraphicsScene *scene, QWidget *parent)
    :   Base::GraphicsView(scene, parent)
    ,   d(new GraphicsViewPrivate(this))
{
    setInteractive(false);
    setOptimizationFlag(DontAdjustForAntialiasing);
    setOptimizationFlag(DontSavePainterState);
    setTransformationAnchor(NoAnchor);
    setViewportUpdateMode(FullViewportUpdate);
    setHorizontalScrollBarPolicy(ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(ScrollBarAlwaysOff);
    setCursor(normalCrosshair());
    setMouseTracking(true);

//    connect(IEditor::instance(), SIGNAL(commandUndone()), SLOT(clearGripSelection()));
//    connect(IEditor::instance(), SIGNAL(commandRedone()), SLOT(clearGripSelection()));
//    connect(GripSelectionModel::instance(), SIGNAL(gripDeselected(IGripItem*)), SLOT(gripDeselected(IGripItem*)));
//    connect(IModel::instance(), SIGNAL(modelAboutToBeDestroyed()), SLOT(modelAboutToBeDestroyed()));
}

GraphicsView::~GraphicsView()
{
    delete d;
}

QTransform GraphicsView::sceneScale() const
{
    QTransform xform = sceneTransform();
    return QTransform::fromScale(xform.m11(), xform.m22());
}

QTransform GraphicsView::sceneTransform() const
{
    return d->rootNode->transform() * viewportTransform();
}

bool GraphicsView::isDirty() const
{
    return d->dirty;
}

void GraphicsView::updateView()
{
    if (d->dirty)
        updateViewSettings();
    update();
}

void GraphicsView::startInsertingPoints()
{
    d->insertingPoints = true;
    setCursor(creationCrosshair());
    d->clearPickedGrips();
}

void GraphicsView::finishInsertingPoints()
{
    setCursor(normalCrosshair());
    foreach (IGraphicsItem *item, d->pickedEntities)
        query<IGraphicsDelegate>(item->findItem(PitchCurveItem))->updateModel();
    d->insertingPoints = false;
}

void GraphicsView::cancelPointInsertion()
{
    setCursor(normalCrosshair());
    foreach (IGraphicsItem *item, d->pickedEntities)
        query<IGraphicsDelegate>(item->findItem(PitchCurveItem))->reset();
    d->insertingPoints = false;
}

bool GraphicsView::pointsAreSelected() const
{
    return 0 < d->pickedGrips.count();
}

//void GraphicsView::selectAllGrips()
//{
//    d->selectAllGrips();
//}

//void GraphicsView::startGripDrag()
//{
//    d->startGripDrag();
//}

void GraphicsView::clearPickedGrips()
{
    d->clearPickedGrips();
}

void GraphicsView::updateSelection(const QList<IGraphicsItem*> &ss)
{
    if (ss.isEmpty()) {
        d->clearPickedEntities();
        return;
    }
    QList<IGraphicsItem*> entities_to_select;
    foreach (IGraphicsItem *entity, ss) {
        IModelItem *item = query<IModelItem>(entity);
        if (item->isTypeOfItem(TrackItem))
            continue;
        if (!d->entityIsPicked(entity))
            entities_to_select.append(entity);
    }
    if (!entities_to_select.isEmpty()) {
        d->appendPickedEntities(entities_to_select);
        return;
    }
    QList<IGraphicsItem*> entities_to_deselect;
    foreach (IGraphicsItem *entity, d->pickedEntities) {
        if (!ss.contains(entity))
            entities_to_deselect.append(entity);
    }
    if (!entities_to_deselect.isEmpty())
        d->removePickedEntities(entities_to_deselect);
}

void GraphicsView::modelAboutToBeReset()
{
    d->clearPickedEntities();
}

void GraphicsView::dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{
    if (DraggingGrips == d->dragState)
        return;

//    // If topLeft is an entity (or subentity) and is showing grips, reset the grips.
//    IModelItem *item = IModel::instance()->itemFromIndex(topLeft);
//    IEntity *entity = QUERY(IEntity, item);
//    if (!entity) {
//        ISubEntity *subEntity = QUERY(ISubEntity, item);
//        if (subEntity)
//            entity = subEntity->parentEntity();
//    }
//    if (entity) {
//        GraphicsEntityItem *entityItem = d->findEntityItem(entity);
//        if (entityItem)
//            entityItem->resetGripItems();
//        else {
//            QList<IEntity*> subEntities = entity->subEntities(sceneType());
//            foreach (IEntity* subEntity, subEntities) {
//                entityItem = d->findEntityItem(subEntity);
//                if (entityItem)
//                    entityItem->resetGripItems();
//            }
//        }
//    }

//    // If topLeft is a track, gripped entities might have been hidden.
//    // Re-append the selected entities so the hidden ones are filtered out.
//    if (TrackItem == topLeft.data(ItemTypeRole))
//        d->resetPickedEntities();
}

void GraphicsView::viewPositionChanged(int role)
{
    if (IDatabase::instance()->isReading())
        return;
    if (horizontalPositionRole() == role || verticalPositionRole() == role)
        d->dirty = true;
}

void GraphicsView::viewScaleChanged(int role)
{
    if (IDatabase::instance()->isReading())
        return;
    if (horizontalScaleRole() == role || verticalScaleRole() == role)
        d->dirty = true;
}

void GraphicsView::scoreLengthChanged()
{
    if (IDatabase::instance()->isReading())
        return;
    d->updateViewSettings();
}

void GraphicsView::removePoints()
{
    QList<IGraphicsGrip*> picked_grips = d->pickedGrips;
    QList<IGraphicsDelegate*> delegates = d->delegatesToUpdate;
    d->clearPickedGrips();
    int grip_count = picked_grips.count();
    for (int i = 0;  i < grip_count;  ++i) {
        IGraphicsGrip *grip = picked_grips.at(i);
        IModelItem *grip_item = query<IModelItem>(grip);
        IModelItem *curve_item = grip_item->parent();
        IGraphicsGripList *curve_griplist = query<IGraphicsGripList>(curve_item);
        QList<IGraphicsGrip*> curve_grips = curve_griplist->grips();
        QList<IGraphicsGrip*> curve_grips_to_remove;
        for (int j = 0;  j < grip_count;  ++j)
            if (curve_item == query<IModelItem>(picked_grips.at(j))->parent())
                curve_grips_to_remove.append(picked_grips.at(j));
        int curve_grips_to_remove_count = curve_grips_to_remove.count();
        if (curve_grips.count() - curve_grips_to_remove_count < 2) {
            foreach (IGraphicsGrip *grip, curve_grips_to_remove)
                picked_grips.removeOne(grip);
            IModelItem *note_item = curve_item->parent();
            note_item->set(VisibilityRole, false);
            note_item->remove();
            curve_griplist->findNode()->setVisible(false);
            break;
        } else {
            foreach (IGraphicsGrip *grip, curve_grips_to_remove)
                curve_grips.removeOne(grip);
            curve_griplist->update(PointsRole, QVariant::fromValue(GripList::toPointList(curve_grips)));
        }
        i -= curve_grips_to_remove_count;
        grip_count -= curve_grips_to_remove_count;
    }
    foreach (IGraphicsDelegate *delegate, delegates) {
        delegate->updateModel();
        delegate->updateGraphics();
    }
}

int GraphicsView::horizontalPositionRole() const
{
    return InvalidRole;
}

int GraphicsView::verticalPositionRole() const
{
    return InvalidRole;
}

int GraphicsView::horizontalScaleRole() const
{
    return InvalidRole;
}

int GraphicsView::verticalScaleRole() const
{
    return InvalidRole;
}

void GraphicsView::zoomStarting()
{
    setCursor(zoomCursor());
}

void GraphicsView::zoomFinished()
{
    setCursor(normalCrosshair());
}

void GraphicsView::panStarting()
{
    setCursor(ClosedHandCursor);
}

void GraphicsView::panFinished()
{
    setCursor(normalCrosshair());
}

void GraphicsView::updateViewSettings()
{
    d->updateViewSettings();
}

void GraphicsView::paintGlyphs(QPaintEvent *event)
{
    Q_UNUSED(event);
    if (Zooming == d->viewState) {
        QPainter painter(viewport());
        painter.drawEllipse(d->dragStartPos, 2, 2);
        painter.setPen(DotLine);
        painter.drawLine(d->dragStartPos, d->curPos);
    }
}

bool GraphicsView::isPlayCursorSelected() const
{
    return d->playCursor;
}

bool GraphicsView::selectPlayCursor(const QPoint &pos)
{
    return d->selectPlayCursor(pos);
}

void GraphicsView::dragPlayCursorTo(const QPoint &pos)
{
    d->dragPlayCursorTo(pos);
}

void GraphicsView::finishDraggingPlayCursor(const QPoint &pos)
{
    d->finishDraggingPlayCursor(pos);
}

void GraphicsView::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    d->dirty = true;
}

void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    if (d->insertingPoints)
        return;
    if (RightButton == event->button()) {
        if (Picking == d->dragState)
            return;
        if (ControlModifier & event->modifiers())
            d->startZoom(event->pos());
        else
            d->startPan(event->pos());
    } else if (LeftButton == event->button()) {
        if (!d->selectGrips(event->pos()))
            if (!selectPlayCursor(event->pos()))
                d->startPicking(event->pos());
    }
}

void GraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    d->curPos = event->pos();
    switch (d->viewState) {
    case Zooming:
        d->zoomTo(event->pos());
        break;
    case Panning:
        d->panTo(event->pos());
    }
    if (isPlayCursorSelected()) {
        dragPlayCursorTo(event->pos());
        return;
    }
    if (d->curGrip
            && DraggingGrips != d->dragState
            && QApplication::startDragDistance() <= QPoint(event->pos() - d->dragStartPos).manhattanLength())
        d->startDraggingGrips();
    switch (d->dragState) {
    case DraggingGrips:
        d->dragGripsTo(event->pos());
        break;
    case Picking:
        d->dragPickBoxTo(event->pos());
    }
    event->setAccepted(d->viewState || d->dragState);
    d->hover();
}

void GraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if (RightButton == event->button()) {
        if (d->insertingPoints)
            GraphicsViewManager::instance()->finishInsertingPoints();
        else {
            switch (d->viewState) {
            case Zooming:
                d->finishZoom(event->pos());
                break;
            case Panning:
                d->finishPan(event->pos());
                break;
            }
        }
    } else if (LeftButton == event->button()) {
        if (isPlayCursorSelected()) {
            finishDraggingPlayCursor(event->pos());
            return;
        }
        if (d->insertingPoints)
            d->insertPoint(event->pos());
        else {
            switch (d->dragState) {
            case CancelledGripDrag:
                d->dragState = 0;
                break;
            case DraggingGrips:
                d->finishDraggingGrips(event->pos());
                break;
            case Picking:
                d->finishPicking(event->pos());
                break;
            default:
                if (!d->curGrip ||
                        ((!(ShiftModifier & QApplication::keyboardModifiers()))
                        && !(ControlModifier & QApplication::keyboardModifiers())))
                    d->clearPicks();
            }
        }
        d->curGrip = 0;
    }
    d->hover();
}

void GraphicsView::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (LeftButton == event->button()) {
        if (d->insertingPoints)
            GraphicsViewManager::instance()->finishInsertingPoints();
        else
            finishDraggingPlayCursor(event->pos());
    }
}

void GraphicsView::wheelEvent(QWheelEvent *event)
{
    // Mac "magic mouse" scroll-wheel handling is annoying and buggy.
#ifdef Q_WS_MAC
    return;
#endif

    if (0 < d->viewState)
        return;
    const QPointF posDC = d->startPosDC(event->pos());
    const QPointF offsetDC = d->centerOffsetDC(posDC);
    const qreal scaleAmount = event->delta() < 0 ? qreal(1.0f) / qreal(1.25f) : qreal(1.25f);
    GraphicsViewManager *vm = GraphicsViewManager::instance();
    const int horizontal_scale_role = horizontalScaleRole();
    const int vertical_scale_role = verticalScaleRole();
    vm->setScale(scaleAmount * vm->scale(horizontal_scale_role), horizontal_scale_role);
    vm->setScale(scaleAmount * vm->scale(vertical_scale_role), vertical_scale_role);
    d->recenter(posDC, offsetDC);
    vm->updateViews();
    d->hover();
}

void GraphicsView::keyPressEvent(QKeyEvent *event)
{
    Base::GraphicsView::keyPressEvent(event);
    d->hover();
}

void GraphicsView::keyReleaseEvent(QKeyEvent *event)
{
    if (Key_Escape == event->key()) {
        if (d->insertingPoints)
            GraphicsViewManager::instance()->cancelPointInsertion();
        else if (DraggingGrips == d->dragState)
            d->cancelGripDrag();
        else
            d->clearPicks();
    } else if (Key_Return == event->key() || Key_Enter == event->key()) {
        if (d->insertingPoints)
            GraphicsViewManager::instance()->finishInsertingPoints();
    } else
        Base::GraphicsView::keyReleaseEvent(event);
    d->hover();
}

void GraphicsView::leaveEvent(QEvent *event)
{
    d->clearHovered();
    Base::GraphicsView::leaveEvent(event);
}

bool GraphicsView::viewportEvent(QEvent *event)
{
    bool result = Base::GraphicsView::viewportEvent(event);
    switch (event->type()) {
    // Return event "accepted" status for the following event types, so they'll
    // be passed to the main widget if ignored.
    case QEvent::MouseMove:
        return event->isAccepted();
    default:
        return result;
    }
}

void GraphicsView::paintEvent(QPaintEvent *event)
{
    QGraphicsView::paintEvent(event);
    paintGlyphs(event);
}

void GraphicsView::clearGripSelection()
{
    d->clearPickedGrips();
}

void GraphicsView::gripDeselected(IGraphicsGrip *grip)
{
    d->hoveredGrips.removeOne(grip);
    d->pickedGrips.removeOne(grip);
}

void GraphicsView::modelAboutToBeDestroyed()
{
    d->cancelGripDrag();
    d->clearPickedEntities();
}
