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

#include "ac_graphicsview.h"

#include <ac_graphicsentityitem.h>
#include <ac_graphicsgripitem.h>
#include <ac_ientity.h>
#include <ac_iplaycursor.h>
#include <ac_viewmanager.h>

#include <ac_noteselectionmodel.h>
#include <ac_trackselectionmodel.h>

#include <mi_ieditor.h>

#include <mi_idatabase.h>
#include <mi_imodel.h>
#include <mi_imodelitem.h>

#include <QApplication>
#include <QMouseEvent>

#include <qmath.h>

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
    QList<GraphicsEntityItem*> pickedEntities;
    QList<IGripItem*> pickedGrips;
    IGripItem *curGrip;
    QList<IEntity*> hoveredEntities;
    QList<IGripItem*> hoveredGrips;
    QList<IEntityItem*> entitiesToUpdate;
    GraphicsRootItem *rootItem;
    IPlayCursor *playCursor;
    QCursor previousCursor;
    uint playCursorHovered : 1;
    uint viewState : 2;
    uint dragState : 2;
    uint extraGripsPicked : 1;
    uint insertingPoints : 1;
    uint dirty : bitsizeof(uint) - 7;

    GraphicsViewPrivate(GraphicsView *q)
        :   q(q)
        ,   pickBox(new QGraphicsRectItem)
        ,   curGrip(0)
        ,   rootItem(new GraphicsRootItem)
        ,   playCursor(0)
        ,   playCursorHovered(false)
        ,   viewState(0)
        ,   dragState(0)
        ,   extraGripsPicked(false)
        ,   insertingPoints(false)
        ,   dirty(true)
    {
        QGraphicsScene *scene = q->scene();

        scene->addItem(rootItem);
        rootItem->setZValue(Q_FLOAT_MAX - 1.0f);

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
        const ViewManager *vm = ViewManager::instance();
        return q->sceneScale().map(QPointF(vm->position(q->positionRoleX()), vm->position(q->positionRoleY())) - posDC);
    }

    void recenter(const QPointF &startPosDC, const QPointF &centerOffsetDC)
    {
        const QPointF center = startPosDC + QTransform::fromScale(q->sceneWidth() / q->width(), -q->sceneHeight() / q->height()).map(centerOffsetDC);
        ViewManager *vm = ViewManager::instance();
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
        const ViewManager *vm = ViewManager::instance();
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
            ViewManager::instance()->setScale((x < 0 ? qreal(1.0f) / scale : scale) * zoomStartScaleX, q->scaleRoleX());
        }
        const int y = offset.y();
        if (y) {
            const qreal scale = qreal(1.0f) + qreal(qAbs(y) / qreal(10.0f));
            ViewManager::instance()->setScale((0 < y ? qreal(1.0f) / scale : scale) * zoomStartScaleY, q->scaleRoleY());
        }
        recenter(zoomStartPosDC, zoomCenterOffsetDC);
        if (dirty)
            ViewManager::instance()->updateViews();
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
        const ViewManager *vm = ViewManager::instance();
        panStartCenter.setX(vm->position(q->positionRoleX()));
        panStartCenter.setY(vm->position(q->positionRoleY()));
    }

    void panTo(const QPoint &pos)
    {
        q->setCursor(Qt::ClosedHandCursor);
        const QPointF offset = q->sceneScale().inverted().map(QPointF(pos - dragStartPos));
        const QPointF center = panStartCenter - offset;
        ViewManager *vm = ViewManager::instance();
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
        clearHovered();

        if (viewState || Picking == dragState || insertingPoints)
            return;

        const QRect viewPickRect = pickOneRect(curPos);
        const QRectF scenePickRect = q->sceneTransform().inverted().mapRect(QRectF(viewPickRect));

        bool gripIsHovered = false;
        bool entityIsHovered = false;

        const QList<QGraphicsItem*> items = q->items(viewPickRect);
        foreach (QGraphicsItem *item, items) {
            IUnknown *unknown = variantToUnknown_cast(item->data(0));
            if (unknown) {
                IPlayCursor *cursor = query<IPlayCursor>(unknown);
                if (cursor) {
                    playCursorHovered = true;
                    previousCursor = q->cursor();
                    q->setCursor(QCursor(Qt::SplitHCursor));
                    break;
                }
                IGripItem *grip = query<IGripItem>(unknown);
                if (grip) {
                    gripIsHovered = true;
                    if (!pickedGrips.contains(grip)) {
                        grip->highlight(IGripItem::HoverHighlight);
                        hoveredGrips.append(grip);
                    }
                } else if (!gripIsHovered) {
                    IEntity *entity = query<IEntity>(unknown);
                    if (entity && entity->intersects(scenePickRect)) {
                        entityIsHovered = true;
                        if (!entityIsPicked(entity)) {
                            hoveredEntities.append(entity);
                            ISubEntity *subEntity = query<ISubEntity>(entity);
                            if (subEntity)
                                entity = subEntity->parentEntity();
                            entity->highlight();
                        }
                    }
                }

                if (!(QApplication::keyboardModifiers() & Qt::ShiftModifier)
                        && (gripIsHovered || entityIsHovered))
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
        foreach (IGripItem *grip, hoveredGrips)
            if (!pickedGrips.contains(grip))
                grip->unhighlight();
        hoveredGrips.clear();
        foreach (IEntity *entity, hoveredEntities) {
            if (!entityIsPicked(entity)) {
                ISubEntity *subEntity = query<ISubEntity>(entity);
                if (subEntity)
                    entity = subEntity->parentEntity();
                entity->unhighlight();
            }
        }
        hoveredEntities.clear();
    }

    IPlayCursor *findPlayCursor(const QList<QGraphicsItem*> &items)
    {
        IPlayCursor *play_cursor = 0;
        foreach (QGraphicsItem *item, items) {
            IUnknown *unknown = variantToUnknown_cast(item->data(0));
            if (unknown) {
                play_cursor = query<IPlayCursor>(unknown);
                if (play_cursor)
                    break;
            }
        }
        return play_cursor;
    }

    bool selectPlayCursor(const QPoint &pos)
    {
        playCursor = findPlayCursor(q->items(pickOneRect(pos)));
        return playCursor != 0;
    }

    void dragPlayCursorTo(const QPoint &pos)
    {
        ViewManager *vm = ViewManager::instance();
        vm->disableUpdates();
        const qreal fromScenePos = playCursor->playCursorPosition();
        const QPointF toScenePos = rootItem->transform().map(q->mapToScene(pos));
        const qreal sceneOffset = toScenePos.x() - fromScenePos;
        playCursor->dragPlayCursorTo(fromScenePos + sceneOffset);
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
        ViewManager::instance()->updateDatabase();

        const qreal fromScenePos = playCursor->playCursorPosition();
        const QPointF toScenePos = rootItem->transform().map(q->mapToScene(pos));
        const qreal sceneOffset = toScenePos.x() - fromScenePos;
        playCursor->setPlayCursorPosition(fromScenePos + sceneOffset);
        playCursor = 0;
        q->setCursor(GraphicsView::normalCrosshair());
    }

    bool selectGrips(const QPoint &pos)
    {
        bool selectedGrip = false;

        const int prevPickedGrips_n = pickedGrips.count();

        const QList<QGraphicsItem*> items = q->items(pickOneRect(pos));
        foreach (QGraphicsItem *item, items) {
            IUnknown *unknown = variantToUnknown_cast(item->data(0));
            if (unknown) {
                IGripItem *grip = query<IGripItem>(unknown);
                if (grip) {
                    if (!selectedGrip)
                        clearHovered();

                    selectedGrip = true;
                    dragStartPos = pos;
                    curGrip = grip;

                    if (QApplication::keyboardModifiers() & Qt::ControlModifier) {
                        grip->unhighlight();
                        pickedGrips.removeOne(grip);
                    } else {
                        if ((!(QApplication::keyboardModifiers() & Qt::ShiftModifier))
                                && !extraGripsPicked)
                            clearPickedGrips();

                        grip->highlight();
                        if (!pickedGrips.contains(grip)) {
                            pickedGrips.append(grip);
                            IEntityItem *entity = grip->parentEntityItem();
                            if (!entitiesToUpdate.contains(entity))
                                entitiesToUpdate.append(entity);
                        }
                    }
                }
            }
        }

        if (!extraGripsPicked && prevPickedGrips_n != 0)
            extraGripsPicked = prevPickedGrips_n < pickedGrips.count();

        return selectedGrip;
    }

    void clearPickedGrips()
    {
        extraGripsPicked = false;

        clearHovered();

        foreach (IGripItem *grip, pickedGrips)
            grip->unhighlight();

        pickedGrips.clear();
        entitiesToUpdate.clear();
    }

    void startDraggingGrips()
    {
        IEditor *editor = IEditor::instance();
        editor->setUndoEnabled(false);
        editor->beginCommand();

        dragState = DraggingGrips;

        foreach (IEntityItem *entity, entitiesToUpdate)
            entity->startDraggingPoints();
    }

    void dragGripsTo(const QPoint &pos)
    {
        ViewManager *vm = ViewManager::instance();
        vm->disableUpdates();

        const QPointF fromScenePos = curGrip->originalPosition();
        const QPointF toScenePos = rootItem->transform().map(q->mapToScene(pos));
        const QPointF sceneOffset = toScenePos - fromScenePos;

        foreach (IGripItem *grip, pickedGrips)
            grip->setPosition(grip->originalPosition() + sceneOffset);

        foreach (IEntityItem *entity, entitiesToUpdate)
            entity->updatePoints();

        vm->enableUpdates();
    }

    void finishDraggingGrips(const QPoint &pos)
    {
        dragGripsTo(pos);

        dragState = 0;
        curGrip = 0;

        foreach (IEntityItem *entity, entitiesToUpdate)
            entity->finishDraggingPoints();

        IEditor *editor = IEditor::instance();
        editor->endCommand();
        editor->setUndoEnabled(true);

        if (!extraGripsPicked)
            clearPickedGrips();
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
        QList<IEntity*> entities;
        foreach (QGraphicsItem *item, items) {
            IUnknown *unknown = variantToUnknown_cast(item->data(0));
            if (unknown) {
                IEntity *entity = query<IEntity>(unknown);
                if (entity && entity->intersects(pickRect)) {
                    ISubEntity *sub_entity = query<ISubEntity>(unknown);
                    if (sub_entity) {
                        IEntity *parent_entity = sub_entity->parentEntity();
                        entities.append(parent_entity);
                        if (pickOne && !(QApplication::keyboardModifiers() & Qt::ShiftModifier))
                            break;
                    }
                }
            }
        }

        QItemSelection ss;
        ss.reserve(entities.count());
        foreach (IEntity *entity, entities) {
            const QModelIndex index = IModel::instance()->indexFromItem(query<IModelItem>(entity));
            ss.select(index, index);
        }

        QItemSelectionModel::SelectionFlags ss_flags = QItemSelectionModel::Clear;
        if (entities.count()) {
            ss_flags = QItemSelectionModel::Select;
            if (QApplication::keyboardModifiers() & Qt::ControlModifier)
                ss_flags = QItemSelectionModel::Deselect;
            if (!(QApplication::keyboardModifiers() & Qt::ShiftModifier))
                ss_flags |= QItemSelectionModel::Clear;
            NoteSelectionModel::instance()->select(ss, ss_flags);
        } else if (pickOne) {
            if (!pickedGrips.isEmpty())
                clearPickedGrips();
            else
                NoteSelectionModel::instance()->clear();
        }

        if (!pickOne)
            pickBox->hide();
        dragState = 0;
    }

    bool entityIsPicked(IEntity *entity)
    {
        ISubEntity *subEntity = query<ISubEntity>(entity);
        IEntity *parentEntity = subEntity ? subEntity->parentEntity() : 0;
        foreach (GraphicsEntityItem *item, pickedEntities) {
            const IEntity *itemEntity = item->entity();
            if (itemEntity == entity || itemEntity == parentEntity)
                return true;
        }
        return false;
    }

    GraphicsEntityItem *findEntityItem(IEntity *entity)
    {
        foreach (GraphicsEntityItem *item, pickedEntities)
            if (item->entity() == entity)
                return item;
        return 0;
    }

    void setPickedEntities(const QList<IEntity*> &entities)
    {
        clearPickedEntities();
        appendPickedEntities(entities);
    }

    void appendPickedEntities(const QList<IEntity*> &entities)
    {
        if (entities.isEmpty())
            return;

        ViewManager *vm = ViewManager::instance();
        vm->disableUpdates();

        foreach (IEntity *entity, entities) {
            if (entity->isVisible() && !entityIsPicked(entity)) {
                GraphicsEntityItem *item = new GraphicsEntityItem(entity);
                pickedEntities.append(item);
                item->setParentItem(rootItem);
                item->highlight();
            }
        }
        vm->enableUpdates();
    }

    void removePickedEntities(const QList<IEntity*> &entities)
    {
        if (entities.isEmpty())
            return;

        ViewManager *vm = ViewManager::instance();
        vm->disableUpdates();

        foreach (IEntity *entity, entities) {
            GraphicsEntityItem *item = findEntityItem(entity);
            if (item) {
                pickedEntities.removeOne(item);
                entitiesToUpdate.removeOne(item);

                for (int i = 0;  i < pickedGrips.count();  ++i) {
                    IGripItem *grip = pickedGrips[i];
                    if (item == grip->parentEntityItem())
                        pickedGrips.removeAt(i--);
                }

                // Unhighlight and remove any hovered grips on the item before
                // deleting it.
                IEntityItem *entity_item = query<IEntityItem>(item);
                for (int i = 0;  i < hoveredGrips.count();  ++i) {
                    IGripItem *grip = hoveredGrips[i];
                    if (entity_item == grip->parentEntityItem()) {
                        grip->unhighlight();
                        hoveredGrips.removeAt(i);
                        --i;
                    }
                }

                item->unhighlight();
                delete item;
            }
        }

        clearPickedGrips();
        vm->enableUpdates();
    }

    void clearPickedEntities()
    {
        ViewManager *vm = ViewManager::instance();
        vm->disableUpdates();

        clearPickedGrips();
        NoteSelectionModel::instance()->clear();

        vm->enableUpdates();
    }

    void resetPickedEntities()
    {
        clearPickedGrips();

        NoteSelectionModel *noteSSModel = NoteSelectionModel::instance();
        QItemSelection ss = noteSSModel->selection();
        noteSSModel->select(ss, QItemSelectionModel::ClearAndSelect);
    }

    void clearPicks()
    {
        if (!pickedGrips.isEmpty())
            clearPickedGrips();
        else {
            clearPickedEntities();
            TrackSelectionModel::instance()->clear();
        }
    }

    void insertPoint(const QPoint &pos)
    {
        const QPointF scenePos = q->sceneTransform().inverted().map(QPointF(pos));

        foreach (GraphicsEntityItem *entityItem, pickedEntities) {
            IEntity *entity = entityItem->entity();
            PointList pts = entity->points();

            Point pt = Point(scenePos);
            if (Qt::ControlModifier & QApplication::keyboardModifiers())
                pt.curveType = Ac::BezierCurve;

            pts.append(pt);
            entity->setPoints(pts);
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

GraphicsView::GraphicsView(QGraphicsScene *scene, QWidget *parent)
    :   MiGraphicsView(scene, parent)
    ,   d(new GraphicsViewPrivate(this))
{
    setInteractive(false);
    setOptimizationFlag(DontAdjustForAntialiasing);
    setOptimizationFlag(DontSavePainterState);
    setTransformationAnchor(NoAnchor);
    setViewportUpdateMode(FullViewportUpdate);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setCursor(normalCrosshair());
    setMouseTracking(true);
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
    return d->rootItem->transform() * viewportTransform();
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
}

void GraphicsView::finishInsertingPoints()
{
    setCursor(normalCrosshair());
    d->insertingPoints = false;
}

bool GraphicsView::pointsAreSelected() const
{
    return 0 < d->pickedGrips.count();
}

void GraphicsView::modelAboutToBeReset()
{
    d->clearPickedEntities();
}

void GraphicsView::dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{
    Q_UNUSED(bottomRight);

    if (DraggingGrips == d->dragState)
        return;

    // If topLeft is an entity (or subentity) and is showing grips, reset the grips.
    IModelItem *item = IModel::instance()->itemFromIndex(topLeft);
    IEntity *entity = query<IEntity>(item);
    if (!entity) {
        ISubEntity *subEntity = query<ISubEntity>(item);
        if (subEntity)
            entity = subEntity->parentEntity();
    }
    if (entity) {
        GraphicsEntityItem *entityItem = d->findEntityItem(entity);
        if (entityItem)
            entityItem->resetGrips();
        else {
            QList<IEntity*> subEntities = entity->subEntities(sceneType());
            foreach (IEntity* subEntity, subEntities) {
                entityItem = d->findEntityItem(subEntity);
                if (entityItem)
                    entityItem->resetGrips();
            }
        }
    }

    // If topLeft is a track, gripped entities might have been hidden.
    // Re-append the selected entities so the hidden ones are filtered out.
    if (Ac::TrackItem == topLeft.data(Mi::ItemTypeRole))
        d->resetPickedEntities();
}

void GraphicsView::noteSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    const IModel *model = IModel::instance();
    const QModelIndexList selectedIndexes = selected.indexes();
    QList<IEntity*> selectedEntities;
    foreach (const QModelIndex &index, selectedIndexes) {
        IEntity *note = query<IEntity>(model->itemFromIndex(index));
        QList<IEntity*> curves = note->subEntities(sceneType());
        selectedEntities.append(curves);
    }
    d->appendPickedEntities(selectedEntities);
    const QModelIndexList deselectedIndexes = deselected.indexes();
    QList<IEntity*> deselectedEntities;
    foreach (const QModelIndex &index, deselectedIndexes) {
        IEntity *note = query<IEntity>(model->itemFromIndex(index));
        QList<IEntity*> curves = note->subEntities(sceneType());
        deselectedEntities.append(curves);
    }
    d->removePickedEntities(deselectedEntities);
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
    foreach (IGripItem *grip, d->pickedGrips) {
        IEntity *entity = grip->parentEntityItem()->entity();
        PointList points = entity->points();
        const int n = points.count();
        for (int i = 0;  i < n;  ++i) {
            if (grip->position() == points.at(i).pos) {
                points.removeAt(i);
                break;
            }
        }
        entity->setPoints(points);
    }
    d->resetPickedEntities();
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
    setCursor(Qt::ClosedHandCursor);
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
        painter.setPen(Qt::DotLine);
        painter.drawLine(d->dragStartPos, d->curPos);
    }
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
    if (Qt::RightButton == event->button()) {
        if (Picking == d->dragState)
            return;
        if (event->modifiers() & Qt::ControlModifier)
            d->startZoom(event->pos());
        else
            d->startPan(event->pos());
    } else if (Qt::LeftButton == event->button()) {
        if (!d->selectGrips(event->pos()))
            if (!d->selectPlayCursor(event->pos()))
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
    if (d->playCursor) {
        d->dragPlayCursorTo(event->pos());
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
    if (Qt::RightButton == event->button()) {
        if (d->insertingPoints)
            ViewManager::instance()->finishInsertingPoints();
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
    } else if (Qt::LeftButton == event->button()) {
        if (d->playCursor) {
            d->finishDraggingPlayCursor(event->pos());
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
                        ((!(QApplication::keyboardModifiers() & Qt::ShiftModifier))
                        && !(QApplication::keyboardModifiers() & Qt::ControlModifier)))
                    d->clearPicks();
            }
        }
        d->curGrip = 0;
    }
    d->hover();
}

void GraphicsView::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (Qt::LeftButton == event->button())
        d->finishDraggingPlayCursor(event->pos());
}

void GraphicsView::wheelEvent(QWheelEvent *event)
{
    if (0 < d->viewState)
        return;
    const QPointF posDC = d->startPosDC(event->pos());
    const QPointF offsetDC = d->centerOffsetDC(posDC);
    const qreal scaleAmount = event->delta() < 0 ? qreal(1.0f) / qreal(1.25f) : qreal(1.25f);
    ViewManager *vm = ViewManager::instance();
    vm->setScale(scaleAmount * vm->scale(scaleRoleX()), scaleRoleX());
    vm->setScale(scaleAmount * vm->scale(scaleRoleY()), scaleRoleY());
    d->recenter(posDC, offsetDC);
    vm->updateViews();
    d->hover();
}

void GraphicsView::keyPressEvent(QKeyEvent *event)
{
    MiGraphicsView::keyPressEvent(event);
    d->hover();
}

void GraphicsView::keyReleaseEvent(QKeyEvent *event)
{
    if (DraggingGrips != d->dragState) {
        if (Qt::Key_Escape == event->key()) {
            if (d->insertingPoints)
                ViewManager::instance()->finishInsertingPoints();
            else
                d->clearPicks();
        } else if (Qt::Key_Return == event->key() || Qt::Key_Enter == event->key()) {
            if (d->insertingPoints)
                ViewManager::instance()->finishInsertingPoints();
        }
    } else
        MiGraphicsView::keyReleaseEvent(event);
    d->hover();
}

void GraphicsView::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    d->clearHovered();
    MiGraphicsView::leaveEvent(event);
}

bool GraphicsView::viewportEvent(QEvent *event)
{
    bool result = MiGraphicsView::viewportEvent(event);
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

qreal GraphicsHView::sceneWidth() const
{
    const ViewManager *vm = ViewManager::instance();
    return vm->scoreLength() / vm->scale(Ac::TimeScaleRole);
}
