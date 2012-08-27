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

#include "ac_gui_graphicsview.h"
//#include <ac_gui_graphicsentityitem.h>
//#include <ac_gui_graphicsgripitem.h>
//#include <ac_gui_graphicsitem.h>
#include "ac_gui_graphicsviewmanager.h"
//#include <ac_gripselectionmodel.h>
//#include <ac_noteselectionmodel.h>
//#include <ac_trackselectionmodel.h>
#include <idatabase.h>
#include <ieditor.h>
#include <ientity.h>
#include <imodel.h>
#include <imodelitem.h>
#include <iplaycursor.h>
#include <qmath.h>
#include <QApplication>
#include <QGraphicsRectItem>
#include <QMouseEvent>
#include <QUndoStack>
#include <QtDebug>

using namespace Qt;

enum ViewState {
    Zooming = 1,
    Panning
};

enum DragState {
    Picking = 1,
    DraggingGrips
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
//    QList<GraphicsEntityItem*> pickedEntities;
    QList<IGripItem*> pickedGrips;
    IGripItem *curGrip;
    QList<IEntity*> hoveredEntities;
    QList<IGripItem*> hoveredGrips;
//    QList<IEntityItem*> entitiesToUpdate;
//    GraphicsRootItem *rootItem;
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
//        ,   rootItem(new GraphicsRootItem)
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
//        scene->addItem(rootItem);
//        rootItem->setZValue(Q_FLOAT_MAX - 1.0f);
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
        return q->sceneScale().map(QPointF(vm->position(q->positionRoleX()), vm->position(q->positionRoleY())) - posDC);
    }

    void recenter(const QPointF &startPosDC, const QPointF &centerOffsetDC)
    {
        const QPointF center = startPosDC + QTransform::fromScale(q->sceneWidth() / q->width(), -q->sceneHeight() / q->height()).map(centerOffsetDC);
        GraphicsViewManager *vm = GraphicsViewManager::instance();
        vm->setPosition(center.x(), q->positionRoleX());
        vm->setPosition(center.y(), q->positionRoleY());
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
        zoomStartScaleX = vm->scale(q->scaleRoleX());
        zoomStartScaleY = vm->scale(q->scaleRoleY());
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
            GraphicsViewManager::instance()->setScale((x < 0 ? qreal(1.0f) / scale : scale) * zoomStartScaleX, q->scaleRoleX());
        }
        const int y = offset.y();
        if (y) {
            const qreal scale = qreal(1.0f) + qreal(qAbs(y) / qreal(10.0f));
            GraphicsViewManager::instance()->setScale((0 < y ? qreal(1.0f) / scale : scale) * zoomStartScaleY, q->scaleRoleY());
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
        panStartCenter.setX(vm->position(q->positionRoleX()));
        panStartCenter.setY(vm->position(q->positionRoleY()));
    }

    void panTo(const QPoint &pos)
    {
        q->setCursor(ClosedHandCursor);
        const QPointF offset = q->sceneScale().inverted().map(QPointF(pos - dragStartPos));
        const QPointF center = panStartCenter - offset;
        GraphicsViewManager *vm = GraphicsViewManager::instance();
        vm->setPosition(center.x(), q->positionRoleX());
        vm->setPosition(center.y(), q->positionRoleY());
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
//        clearHovered();
//        if (viewState || Picking == dragState || insertingPoints)
//            return;
//        const QRect viewPickRect = pickOneRect(curPos);
//        const QRectF scenePickRect = q->sceneTransform().inverted().mapRect(QRectF(viewPickRect));
//        bool gripIsHovered = false;
//        bool entityIsHovered = false;
//        const QList<QGraphicsItem*> items = q->items(viewPickRect);
//        foreach (QGraphicsItem *item, items) {
//            IUnknown *unknown = static_cast<IUnknown*>(qvariant_cast<void*>(item->data(0)));
//            if (unknown) {
//                IPlayCursor *cursor = query<IPlayCursor>(unknown);
//                if (cursor) {
//                    playCursorHovered = true;
//                    previousCursor = q->cursor();
//                    q->setCursor(QCursor(SplitHCursor));
//                    break;
//                }
//                IGripItem *grip = query<IGripItem>(unknown);
//                if (grip) {
//                    gripIsHovered = true;
//                    if (!pickedGrips.contains(grip)) {
//                        grip->highlight(IGripItem::HoverHighlight);
//                        hoveredGrips.append(grip);
//                    }
//                } else if (!gripIsHovered) {
//                    IEntity *entity = query<IEntity>(unknown);
//                    if (entity && entity->intersects(scenePickRect)) {
//                        entityIsHovered = true;
//                        if (!entityIsPicked(entity)) {
//                            hoveredEntities.append(entity);
//                            ISubEntity *subEntity = query<ISubEntity>(entity);
//                            if (subEntity)
//                                entity = subEntity->parentEntity();
//                            entity->highlight();
//                        }
//                    }
//                }
//                if (!(QApplication::keyboardModifiers() & ShiftModifier)
//                        && (gripIsHovered || entityIsHovered))
//                    break;
//            }
//        }
    }

    void clearHovered()
    {
//        if (playCursorHovered) {
//            playCursorHovered = false;
//            q->setCursor(previousCursor);
//        }
//        foreach (IGripItem *grip, hoveredGrips)
//            if (!pickedGrips.contains(grip))
//                grip->unhighlight();
//        hoveredGrips.clear();
//        foreach (IEntity *entity, hoveredEntities) {
//            if (!entityIsPicked(entity)) {
//                ISubEntity *subEntity = query<ISubEntity>(entity);
//                if (subEntity)
//                    entity = subEntity->parentEntity();
//                entity->unhighlight();
//            }
//        }
//        hoveredEntities.clear();
    }

    IPlayCursor *findPlayCursor(const QList<QGraphicsItem*> &items)
    {
        IPlayCursor *play_cursor = 0;
//        foreach (QGraphicsItem *item, items) {
//            IUnknown *unknown = static_cast<IUnknown*>(qvariant_cast<void*>(item->data(0)));
//            if (unknown) {
//                play_cursor = query<IPlayCursor>(unknown);
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
        if (!playCursor) {
            playCursor = findPlayCursor(q->items());
            if (!playCursor) {
                qWarning() << Q_FUNC_INFO << ": play cursor not found";
                return;
            }
        }

        // The view manager might have different view settings than the
        // database.  Update the database's view settings so they don't
        // overwrite the view manager's view settings in the view manager's
        // dataChanged implementation when the cursor position is changed.
        GraphicsViewManager *vm = GraphicsViewManager::instance();
        vm->updateDatabase();

//        const qreal fromScenePos = playCursor->playCursorPosition();
//        const QPointF toScenePos = rootItem->transform().map(q->mapToScene(pos));
//        const qreal sceneOffset = vm->snappedScenePos(toScenePos, q->sceneType()).x() - fromScenePos;
//        playCursor->setPlayCursorPosition(fromScenePos + sceneOffset);
        playCursor = 0;
        q->setCursor(GraphicsView::normalCrosshair());
    }

    bool selectGrips(const QPoint &pos)
    {
//        bool selectedGrip = false;
//        const QList<QGraphicsItem*> items = q->items(pickOneRect(pos));
//        foreach (QGraphicsItem *item, items) {
//            IUnknown *unknown = static_cast<IUnknown*>(qvariant_cast<void*>(item->data(0)));
//            if (unknown) {
//                IGripItem *grip = query<IGripItem>(unknown);
//                if (grip) {
//                    if (!selectedGrip)
//                        clearHovered();
//                    selectedGrip = true;
//                    dragStartPos = pos;
//                    curGrip = grip;
//                    if (pickedGrips.contains(grip))
//                        keepGripsPicked = true;
//                    if (ControlModifier & QApplication::keyboardModifiers()) {
//                        grip->unhighlight();
//                        pickedGrips.removeOne(grip);
//                    } else {
//                        if (ShiftModifier & QApplication::keyboardModifiers())
//                            keepGripsPicked = true;
//                        else if (!keepGripsPicked)
//                            clearPickedGrips();
//                        grip->highlight();
//                        if (!pickedGrips.contains(grip)) {
//                            pickedGrips.append(grip);
//                            IEntityItem *entity = grip->parentEntityItem();
//                            if (!entitiesToUpdate.contains(entity))
//                                entitiesToUpdate.append(entity);
//                        }
//                    }
//                }
//            }
//        }
//        return selectedGrip;
        return false;
    }

    void selectAllGrips()
    {
//        clearPickedGrips();
//        foreach (GraphicsEntityItem *entity_item, pickedEntities) {
//            entitiesToUpdate.append(entity_item);
//            const QList<IGripItem*> &grips = entity_item->gripItems();
//            pickedGrips.append(grips);
//            foreach (IGripItem *grip, grips)
//                grip->highlight();
//        }
    }

    void startGripDrag()
    {
//        selectAllGrips();
//        if (pickedGrips.isEmpty())
//            return;

//        // Set curGrip to the lowest and earliest grip.
//        curGrip = pickedGrips.first();
//        foreach (IGripItem *grip_item, pickedGrips) {
//            const QPointF pos = grip_item->position();
//            if (pos.x() < curGrip->position().x()
//                    || (pos.x() == curGrip->position().x()
//                        && pos.y() < curGrip->position().y()))
//                curGrip = grip_item;
//        }

//        startDraggingGrips();
    }

    void clearPickedGrips()
    {
//        keepGripsPicked = false;
//        clearHovered();
//        foreach (IGripItem *grip, pickedGrips)
//            grip->unhighlight();
//        pickedGrips.clear();
//        entitiesToUpdate.clear();
    }

    void startDraggingGrips()
    {
//        dragState = DraggingGrips;
//        foreach (IEntityItem *entityItem, entitiesToUpdate)
//            entityItem->startUpdatingPoints();
    }

    void dragGripsTo(const QPoint &pos)
    {
//        GraphicsViewManager *vm = GraphicsViewManager::instance();
//        vm->disableUpdates();
//        const QPointF fromScenePos = curGrip->originalPosition();
//        const QPointF toScenePos = rootItem->transform().map(q->mapToScene(pos));
//        const QPointF sceneOffset = vm->snappedScenePos(toScenePos, q->sceneType()) - fromScenePos;
//        foreach (IGripItem *grip, pickedGrips)
//            grip->setPosition(grip->originalPosition() + sceneOffset);
//        foreach (IEntityItem *entity, entitiesToUpdate)
//            entity->updatePoints();
//        gripsDragged = true;
//        vm->enableUpdates();
    }

    void finishDraggingGrips(const QPoint &pos)
    {
//        dragGripsTo(pos);
//        dragState = 0;
//        curGrip = 0;
//        if (gripsDragged) {
//            IEditor *editor = IEditor::instance();
//            editor->beginCommand();
//            foreach (IEntityItem *entityItem, entitiesToUpdate)
//                entityItem->finishUpdatingPoints();
//            editor->endCommand();
//            gripsDragged = false;
//        }
    }

    void cancelGripDrag()
    {
//        dragState = 0;
//        curGrip = 0;
//        const int n = entitiesToUpdate.count();
//        for (int i = 0;  i < n;  ++i)
//            entitiesToUpdate.at(i)->entity()->popPoints();
//        gripsDragged = false;
//        resetPickedEntities();
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
//        const QRect rect = (pickOne = (pos - dragStartPos).manhattanLength() < QApplication::startDragDistance())
//                ? pickOneRect(dragStartPos)
//                : QRect(dragStartPos, pos).normalized().intersected(pickBoxBounds());
//        const QRectF pickRect = q->sceneTransform().inverted().mapRect(QRectF(rect));
//        const QList<QGraphicsItem*> items = q->items(rect);
//        QList<IEntity*> entities;
//        foreach (QGraphicsItem *item, items) {
//            IUnknown *unknown = variantToUnknown_cast(item->data(0));
//            if (unknown) {
//                IEntity *entity = query<IEntity>(unknown);
//                if (entity && entity->intersects(pickRect)) {
//                    ISubEntity *sub_entity = query<ISubEntity>(unknown);
//                    if (sub_entity) {
//                        IEntity *parent_entity = sub_entity->parentEntity();
//                        entities.append(parent_entity);
//                        if (pickOne && !(QApplication::keyboardModifiers() & ShiftModifier))
//                            break;
//                    }
//                }
//            }
//        }
//        QItemSelection ss;
//        ss.reserve(entities.count());
//        foreach (IEntity *entity, entities) {
//            const QModelIndex index = IModel::instance()->indexFromItem(query<IModelItem>(entity));
//            ss.select(index, index);
//        }
//        QItemSelectionModel::SelectionFlags ss_flags = QItemSelectionModel::Clear;
//        if (entities.count()) {
//            ss_flags = QItemSelectionModel::Select;
//            if (QApplication::keyboardModifiers() & ControlModifier)
//                ss_flags = QItemSelectionModel::Deselect;
//            if (!(QApplication::keyboardModifiers() & ShiftModifier))
//                ss_flags |= QItemSelectionModel::Clear;
//            NoteSelectionModel::instance()->select(ss, ss_flags);
//        } else if (pickOne) {
//            if (!pickedGrips.isEmpty())
//                GraphicsViewManager::instance()->clearPickedGrips();
//            else {
//                NoteSelectionModel::instance()->clear();
//                TrackSelectionModel::instance()->clear();
//            }
//        }
        if (!pickOne)
            pickBox->hide();
        dragState = 0;
    }

    bool entityIsPicked(IEntity *entity)
    {
//        ISubEntity *subEntity = query<ISubEntity>(entity);
//        IEntity *parentEntity = subEntity ? subEntity->parentEntity() : 0;
//        foreach (GraphicsEntityItem *item, pickedEntities) {
//            const IEntity *itemEntity = item->entity();
//            if (itemEntity == entity || itemEntity == parentEntity)
//                return true;
//        }
        return false;
    }

//    GraphicsEntityItem *findEntityItem(IEntity *entity)
//    {
//        foreach (GraphicsEntityItem *item, pickedEntities)
//            if (item->entity() == entity)
//                return item;
//        return 0;
//    }

    void setPickedEntities(const QList<IEntity*> &entities)
    {
        clearPickedEntities();
        appendPickedEntities(entities);
    }

    void appendPickedEntities(const QList<IEntity*> &entities)
    {
//        if (entities.isEmpty())
//            return;
//        GraphicsViewManager *vm = GraphicsViewManager::instance();
//        vm->disableUpdates();
//        foreach (IEntity *entity, entities) {
//            if (entity->isVisible() && !entityIsPicked(entity)) {
//                GraphicsEntityItem *item = new GraphicsEntityItem(entity);
//                pickedEntities.append(item);
//                item->setParentItem(rootItem);
//                item->highlight();
//            }
//        }
//        vm->enableUpdates();
    }

    void removePickedEntities(const QList<IEntity*> &entities)
    {
//        if (entities.isEmpty())
//            return;
//        GraphicsViewManager *vm = GraphicsViewManager::instance();
//        vm->disableUpdates();
//        foreach (IEntity *entity, entities) {
//            GraphicsEntityItem *item = findEntityItem(entity);
//            if (item) {
//                pickedEntities.removeOne(item);
//                entitiesToUpdate.removeOne(item);
//                for (int i = 0;  i < pickedGrips.count();  ++i) {
//                    IGripItem *grip = pickedGrips[i];
//                    if (item == grip->parentEntityItem())
//                        pickedGrips.removeAt(i--);
//                }

//                // Unhighlight and remove any hovered grips on the item before
//                // deleting it.
//                IEntityItem *entity_item = query<IEntityItem>(item);
//                for (int i = 0;  i < hoveredGrips.count();  ++i) {
//                    IGripItem *grip = hoveredGrips[i];
//                    if (entity_item == grip->parentEntityItem()) {
//                        grip->unhighlight();
//                        hoveredGrips.removeAt(i);
//                        --i;
//                    }
//                }

//                item->unhighlight();
//                delete item;
//            }
//        }
//        clearPickedGrips();
//        vm->enableUpdates();
    }

    void clearPickedEntities()
    {
//        GraphicsViewManager *vm = GraphicsViewManager::instance();
//        vm->disableUpdates();
//        clearPickedGrips();
//        NoteSelectionModel::instance()->clear();
//        vm->enableUpdates();
    }

    void resetPickedEntities()
    {
//        clearPickedGrips();
//        NoteSelectionModel *noteSSModel = NoteSelectionModel::instance();
//        QItemSelection ss = noteSSModel->selection();
//        noteSSModel->clear();
//        noteSSModel->select(ss, QItemSelectionModel::Select);
    }

    void clearPicks()
    {
//        if (!pickedGrips.isEmpty())
//            GraphicsViewManager::instance()->clearPickedGrips();
//        else {
//            clearPickedEntities();
//            TrackSelectionModel::instance()->clear();
//        }
    }

    void insertPoint(const QPoint &pos)
    {
//        const QPointF scenePos = GraphicsViewManager::instance()->snappedScenePos(q->sceneTransform().inverted().map(QPointF(pos)), q->sceneType());
//        foreach (GraphicsEntityItem *entityItem, pickedEntities) {
//            IEntity *entity = entityItem->entity();
//            PointList pts = entity->points();
//            Point pt = Point(scenePos);
//            if (ControlModifier & QApplication::keyboardModifiers())
//                pt.curveType = Ac::BezierCurve;
//            pts.append(pt);
//            entity->popPoints();
//            entity->pushPoints(pts);
//            entityItem->resetGripItems();
//        }
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

const QCursor &GraphicsView::normalCrosshair()
{
    static const QCursor cursor(QPixmap(":/ac_guiplugin/images/crosshair-black.png"));
    return cursor;
}

const QCursor &GraphicsView::creationCrosshair()
{
    static const QCursor cursor(QPixmap(":/ac_guiplugin/images/crosshair-red.png"));
    return cursor;
}

static const QCursor &zoomCursor()
{
    static const QCursor cursor(QPixmap(":/ac_guiplugin/images/zoom-cursor.png"));
    return cursor;
}

QTransform GraphicsView::sceneScale() const
{
    QTransform xform = sceneTransform();
    return QTransform::fromScale(xform.m11(), xform.m22());
}

QTransform GraphicsView::sceneTransform() const
{
//    return d->rootItem->transform() * viewportTransform();
    Q_ASSERT(0);
    return QTransform();
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
//    d->insertingPoints = true;
//    foreach (GraphicsEntityItem *entityItem, d->pickedEntities) {
//        IEntity *entity = entityItem->entity();
//        entity->pushPoints();
//    }
//    setCursor(creationCrosshair());
//    d->clearPickedGrips();
}

void GraphicsView::finishInsertingPoints()
{
//    foreach (GraphicsEntityItem *entityItem, d->pickedEntities) {
//        IEntity *entity = entityItem->entity();
//        entity->setPoints();
//        entityItem->resetGripItems();
//    }
//    setCursor(normalCrosshair());
//    d->insertingPoints = false;
//    d->resetPickedEntities();
}

void GraphicsView::cancelPointInsertion()
{
//    const int n = d->pickedEntities.count();
//    for (int i = 0;  i < n;  ++i)
//        d->pickedEntities.at(i)->entity()->popPoints();
//    setCursor(normalCrosshair());
//    d->insertingPoints = false;
//    d->resetPickedEntities();
}

bool GraphicsView::pointsAreSelected() const
{
    return 0 < d->pickedGrips.count();
}

void GraphicsView::selectAllGrips()
{
    d->selectAllGrips();
}

void GraphicsView::startGripDrag()
{
    d->startGripDrag();
}

void GraphicsView::clearPickedGrips()
{
    d->clearPickedGrips();
}

void GraphicsView::modelAboutToBeReset()
{
    d->clearPickedEntities();
}

void GraphicsView::dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{
//    if (DraggingGrips == d->dragState)
//        return;

//    // If topLeft is an entity (or subentity) and is showing grips, reset the grips.
//    IModelItem *item = IModel::instance()->itemFromIndex(topLeft);
//    IEntity *entity = query<IEntity>(item);
//    if (!entity) {
//        ISubEntity *subEntity = query<ISubEntity>(item);
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
//    if (Ac::TrackItem == topLeft.data(Mi::ItemTypeRole))
//        d->resetPickedEntities();
}

void GraphicsView::noteSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
//    const IModel *model = IModel::instance();
//    const QModelIndexList selectedIndexes = selected.indexes();
//    QList<IEntity*> selectedEntities;
//    foreach (const QModelIndex &index, selectedIndexes) {
//        IEntity *note = query<IEntity>(model->itemFromIndex(index));
//        QList<IEntity*> curves = note->subEntities(sceneType());
//        selectedEntities.append(curves);
//    }
//    d->appendPickedEntities(selectedEntities);
//    const QModelIndexList deselectedIndexes = deselected.indexes();
//    QList<IEntity*> deselectedEntities;
//    foreach (const QModelIndex &index, deselectedIndexes) {
//        IEntity *note = query<IEntity>(model->itemFromIndex(index));
//        QList<IEntity*> curves = note->subEntities(sceneType());
//        deselectedEntities.append(curves);
//    }
//    d->removePickedEntities(deselectedEntities);
}

void GraphicsView::viewPositionChanged(int role)
{
    if (IDatabase::instance()->isReading())
        return;
    if (positionRoleX() == role || positionRoleY() == role)
        d->dirty = true;
}

void GraphicsView::viewScaleChanged(int role)
{
    if (IDatabase::instance()->isReading())
        return;
    if (scaleRoleX() == role || scaleRoleY() == role)
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
//    // Store the view's picked grips locally so they can be cleared before
//    // they're deleted by the entity item in resetGrips.
//    QList<IGripItem*> picked_grips = d->pickedGrips;
//    d->clearPickedGrips();

//    foreach (IGripItem *grip, picked_grips) {
//        IEntity *entity = grip->parentEntityItem()->entity();
//        PointList points = entity->points();
//        const int n = points.count();
//        for (int i = 0;  i < n;  ++i) {
//            if (grip->position() == points.at(i).pos) {
//                points.removeAt(i);
//                break;
//            }
//        }
//        entity->setPoints(points);
//        GraphicsEntityItem *entity_item = d->findEntityItem(entity);
//        if (entity_item)
//            entity_item->resetGripItems();
//    }
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
    vm->setScale(scaleAmount * vm->scale(scaleRoleX()), scaleRoleX());
    vm->setScale(scaleAmount * vm->scale(scaleRoleY()), scaleRoleY());
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

void GraphicsView::gripDeselected(IGripItem *grip)
{
    d->hoveredGrips.removeOne(grip);
    d->pickedGrips.removeOne(grip);
}

void GraphicsView::modelAboutToBeDestroyed()
{
    d->cancelGripDrag();
    d->clearPickedEntities();
}

qreal GraphicsHView::sceneWidth() const
{
    const GraphicsViewManager *vm = GraphicsViewManager::instance();
    return vm->scoreLength() / vm->scale(Ac::TimeScaleRole);
}
