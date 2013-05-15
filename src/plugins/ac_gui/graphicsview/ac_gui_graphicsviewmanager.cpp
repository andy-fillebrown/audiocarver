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

#include "ac_gui_graphicsviewmanager.h"
#include "ac_gui_graphicscontrolview.h"
#include "ac_gui_graphicscontrollabelview.h"
#include "ac_gui_graphicsscenemanager.h"
#include "ac_gui_namespace.h"
#include "ac_gui_graphicspitchlabelview.h"
#include "ac_gui_graphicspitchview.h"
#include "ac_gui_graphicstimelabelview.h"
#include <ac_core_constants.h>
#include <ac_core_namespace.h>
#include <mi_gui_undo_stack.h>
#include <mi_core_math.h>
#include <icore.h>
#include <idatabase.h>
#include <ieditor.h>
#include <igraphicsgrip.h>
#include <igraphicsitem.h>
#include <imodel.h>
#include <imodelitem.h>
#include <iselectionset.h>
#include <iundomanager.h>
#include <mainwindow.h>
#include <QGraphicsItem>
#include <QMessageBox>
#include <QTimer>
#include <QWidget>
#include <QtGlobal>

using namespace Ac;
using namespace Mi;

static GraphicsViewManager *instance = 0;

static qreal closestGridlineLocation(qreal location, const IModelItem *gridlineListItem)
{
    qreal min_offset = Q_FLOAT_MAX;
    qreal closest_location = location;
    const int n = gridlineListItem->itemCount();
    for (int i = 0;  i < n;  ++i) {
        IModelItem *gridline = gridlineListItem->itemAt(i);
        if (get<bool>(gridline, VisibilityRole)) {
            const qreal current_location = get<qreal>(gridline, LocationRole);
            const qreal current_offset = qAbs(location - current_location);
            if (current_offset < min_offset) {
                min_offset = current_offset;
                closest_location = current_location;
            }
        }
    }
    return closest_location;
}

class GraphicsViewManagerPrivate
{
public:
    GraphicsViewManager *q;
    GraphicsSceneManager *sceneManager;
    GraphicsPitchView *pitchView;
    GraphicsControlView *controlView;
    GraphicsTimeLabelView *timeLabelView;
    GraphicsPitchLabelView *pitchLabelView;
    GraphicsControlLabelView *controlLabelView;
    qreal scoreLength;
    qreal timePos;
    qreal pitchPos;
    qreal controlPos;
    qreal timeScale;
    qreal pitchScale;
    qreal controlScale;
    QTimer *updateViewsTimer;
    uint initialized : 1;
    uint updatingDatabase : 1;
    uint undoingViewSettings : 1;

    GraphicsViewManagerPrivate(GraphicsViewManager *q)
        :   q(q)
        ,   sceneManager(new GraphicsSceneManager(q))
        ,   pitchView(0)
        ,   controlView(0)
        ,   timeLabelView(0)
        ,   pitchLabelView(0)
        ,   controlLabelView(0)
        ,   updateViewsTimer(new QTimer(q))
        ,   initialized(false)
        ,   updatingDatabase(false)
        ,   undoingViewSettings(false)
    {
        updateViewsTimer->setSingleShot(true);
    }

    void init()
    {
        QWidget *widget = qobject_cast<QWidget*>(q->parent());
        pitchView = new GraphicsPitchView(sceneManager->scene(PitchScene), widget);
        controlView = new GraphicsControlView(sceneManager->scene(ControlScene), widget);
        timeLabelView = new GraphicsTimeLabelView(sceneManager->scene(TimeLabelScene), widget);
        pitchLabelView = new GraphicsPitchLabelView(sceneManager->scene(PitchLabelScene), widget);
        controlLabelView = new GraphicsControlLabelView(sceneManager->scene(ControlLabelScene), widget);
        q->connect(q, SIGNAL(viewPositionChanged(int)), pitchView, SLOT(viewPositionChanged(int)));
        q->connect(q, SIGNAL(viewPositionChanged(int)), controlView, SLOT(viewPositionChanged(int)));
        q->connect(q, SIGNAL(viewPositionChanged(int)), timeLabelView, SLOT(viewPositionChanged(int)));
        q->connect(q, SIGNAL(viewPositionChanged(int)), pitchLabelView, SLOT(viewPositionChanged(int)));
        q->connect(q, SIGNAL(viewPositionChanged(int)), controlLabelView, SLOT(viewPositionChanged(int)));
        q->connect(q, SIGNAL(viewScaleChanged(int)), pitchView, SLOT(viewScaleChanged(int)));
        q->connect(q, SIGNAL(viewScaleChanged(int)), controlView, SLOT(viewScaleChanged(int)));
        q->connect(q, SIGNAL(viewScaleChanged(int)), timeLabelView, SLOT(viewScaleChanged(int)));
        q->connect(q, SIGNAL(viewScaleChanged(int)), pitchLabelView, SLOT(viewScaleChanged(int)));
        q->connect(q, SIGNAL(viewScaleChanged(int)), controlLabelView, SLOT(viewScaleChanged(int)));
        q->connect(q, SIGNAL(scoreLengthChanged()), pitchView, SLOT(scoreLengthChanged()));
        q->connect(q, SIGNAL(scoreLengthChanged()), controlView, SLOT(scoreLengthChanged()));
        q->connect(q, SIGNAL(scoreLengthChanged()), timeLabelView, SLOT(scoreLengthChanged()));
        q->connect(q, SIGNAL(scoreLengthChanged()), pitchLabelView, SLOT(scoreLengthChanged()));
        q->connect(q, SIGNAL(scoreLengthChanged()), controlLabelView, SLOT(scoreLengthChanged()));
        updateViewVariables();
        q->updateViews();
        initialized = true;
    }

    ~GraphicsViewManagerPrivate()
    {
        delete controlLabelView;
        delete pitchLabelView;
        delete timeLabelView;
        delete controlView;
        delete pitchView;
    }

    void updateViewVariables()
    {
        IModelItem *score = IDatabase::instance()->rootItem();
        const qreal score_length = get<qreal>(score, LengthRole);
        if (scoreLength != score_length) {
            scoreLength = score_length;
            emit q->scoreLengthChanged();
            updateViewsTimer->start();
        }
        IModelItem *view_settings = score->findItem(ViewSettingsItem);
        q->setPosition(TimePositionRole, get<qreal>(view_settings, TimePositionRole));
        q->setPosition(PitchPositionRole, get<qreal>(view_settings, PitchPositionRole));
        q->setPosition(ControlPositionRole, get<qreal>(view_settings, ControlPositionRole));
        q->setScale(TimeScaleRole, get<qreal>(view_settings, TimeScaleRole));
        q->setScale(PitchScaleRole, get<qreal>(view_settings, PitchScaleRole));
        q->setScale(ControlScaleRole, get<qreal>(view_settings, ControlScaleRole));
    }

    void emitAllViewSettingsChanged()
    {
        emit q->viewPositionChanged(TimePositionRole);
        emit q->viewPositionChanged(PitchPositionRole);
        emit q->viewPositionChanged(ControlPositionRole);
        emit q->viewScaleChanged(TimeScaleRole);
        emit q->viewScaleChanged(PitchScaleRole);
        emit q->viewScaleChanged(ControlScaleRole);
    }

    void startUndo()
    {
        if (initialized && !undoingViewSettings && !IDatabase::instance()->isReading()) {
            IUndoManager *undo_manager = IUndoManager::instance();
            if (!undo_manager->isUndoing() && !undo_manager->isInCommand())
                undoingViewSettings = true;
        }
    }

    void finishUndo()
    {
        if (undoingViewSettings) {
            IUndoManager::instance()->pushCommand(ViewSettingsCommandId);
            undoingViewSettings = false;
        }
    }

    IGraphicsGrip *snapGrip(int sceneType, const QPoint &pos)
    {
        QGraphicsView *view = q->view(sceneType);
        QList<QGraphicsItem*> items = view->items(GraphicsView::pickOneRect(pos));
        foreach (QGraphicsItem *item, items) {
            IUnknown *unknown = reinterpret_cast<IUnknown*>(qvariant_cast<quintptr>(item->data(0)));
            if (unknown) {
                IGraphicsGrip *grip = query<IGraphicsGrip>(unknown);
                if (grip && FullHighlight != grip->highlightType()) {
                    return grip;
                }
            }
        }
        return 0;
    }

    void snapX(int role, QPointF &pos, bool snapToGrid)
    {
        qreal toX = -1.0f;
        IModelItem *score = IDatabase::instance()->rootItem();
        if (TimePositionRole == role) {
            if (snapToGrid)
                toX = closestGridlineLocation(pos.x(), score->findItem(GridSettingsItem)->findItem(TimeGridLineListItem));
            else
                toX = get<qreal>(score->findItem(GridSettingsItem), TimeSnapRole);
        }
        if (snapToGrid)
            pos.setX(toX);
        else if (0.0f < toX)
            pos.setX(roundToNearest(pos.x(), toX));
    }

    void snapY(int role, QPointF &pos, bool snapToGrid)
    {
        qreal toY = -1.0f;
        IModelItem *score = IDatabase::instance()->rootItem();
        if (PitchPositionRole == role) {
            if (snapToGrid)
                toY = closestGridlineLocation(pos.y(), score->findItem(GridSettingsItem)->findItem(PitchGridLineListItem));
            else
                toY = get<qreal>(score->findItem(GridSettingsItem), PitchSnapRole);
        } else if (ControlPositionRole == role) {
            if (snapToGrid)
                toY = closestGridlineLocation(pos.y(), score->findItem(GridSettingsItem)->findItem(ControlGridLineListItem));
            else
                toY = get<qreal>(score->findItem(GridSettingsItem), ControlSnapRole);
        }
        if (snapToGrid)
            pos.setY(toY);
        else if (0.0f < toY)
            pos.setY(roundToNearest(pos.y(), toY));
    }
};

GraphicsViewManager *GraphicsViewManager::instance()
{
    return ::instance;
}

GraphicsViewManager::GraphicsViewManager(QWidget *widget)
    :   QObject(widget)
    ,   d(new GraphicsViewManagerPrivate(this))
{
    ::instance = this;
    d->init();
    IModel *model = IModel::instance();
    connect(model, SIGNAL(dataChanged(IModelItem*,int)), SLOT(dataChanged(IModelItem*,int)));
    connect(model, SIGNAL(modelAboutToBeReset()), SLOT(disableUpdates()));
    connect(model, SIGNAL(modelReset()), SLOT(modelReset()));
    connect(d->updateViewsTimer, SIGNAL(timeout()), SLOT(updateViews()));
}

GraphicsViewManager::~GraphicsViewManager()
{
    cancelPointInsertion();
    delete d;
}

QGraphicsView *GraphicsViewManager::view(int type) const
{
    switch (type) {
    case PitchScene: return d->pitchView;
    case ControlScene: return d->controlView;
    case TimeLabelScene: return d->timeLabelView;
    case PitchLabelScene: return d->pitchLabelView;
    case ControlLabelScene: return d->controlLabelView;
    default: return 0;
    }
}

qreal GraphicsViewManager::scoreLength() const
{
    return d->scoreLength;
}

qreal GraphicsViewManager::position(int role) const
{
    switch (role) {
    case TimePositionRole:
        return d->timePos;
    case PitchPositionRole:
        return d->pitchPos;
    case ControlPositionRole:
        return d->controlPos;
    default:
        return 0.0f;
    }
}

void GraphicsViewManager::setPosition(int role, qreal position)
{
    switch (role) {
    case TimePositionRole:
        position = qBound(qreal(0.0f), position, d->scoreLength);
        if (qFuzzyCompare(d->timePos, position))
            return;
        d->startUndo();
        d->timePos = position;
        emit viewPositionChanged(TimePositionRole);
        break;
    case PitchPositionRole:
        position = qBound(qreal(0.0f), position, qreal(127.0f));
        if (qFuzzyCompare(d->pitchPos, position))
            return;
        d->startUndo();
        d->pitchPos = position;
        emit viewPositionChanged(PitchPositionRole);
        break;
    case ControlPositionRole:
        position = qBound(qreal(0.0f), position, qreal(1.0f));
        if (qFuzzyCompare(d->controlPos, position))
            return;
        d->startUndo();
        d->controlPos = position;
        emit viewPositionChanged(ControlPositionRole);
    default:
        break;
    }
}

qreal GraphicsViewManager::scale(int role) const
{
    switch (role) {
    case TimeScaleRole:
        return d->timeScale;
    case PitchScaleRole:
        return d->pitchScale;
    case ControlScaleRole:
        return d->controlScale;
    default:
        return 1.0f;
    }
}

void GraphicsViewManager::setScale(int role, qreal scale)
{
    if (scale < VIEWSCALE_MIN)
        scale = VIEWSCALE_MIN;
    if (VIEWSCALE_MAX < scale)
        scale = VIEWSCALE_MAX;
    if (qFuzzyCompare(this->scale(role), scale))
        return;
    switch (role) {
    case TimeScaleRole:
        d->startUndo();
        d->timeScale = scale;
        emit viewScaleChanged(TimeScaleRole);
        break;
    case PitchScaleRole:
        d->startUndo();
        d->pitchScale = scale;
        emit viewScaleChanged(PitchScaleRole);
        break;
    case ControlScaleRole:
        d->startUndo();
        d->controlScale = scale;
        emit viewScaleChanged(ControlScaleRole);
    default:
        break;
    }
}

void GraphicsViewManager::updateDatabase()
{
    d->updatingDatabase = true;
    IModelItem *view_settings = IDatabase::instance()->rootItem()->findItem(ViewSettingsItem);
    view_settings->set(TimePositionRole, d->timePos);
    view_settings->set(PitchPositionRole, d->pitchPos);
    view_settings->set(ControlPositionRole, d->controlPos);
    view_settings->set(TimeScaleRole, d->timeScale);
    view_settings->set(PitchScaleRole, d->pitchScale);
    view_settings->set(ControlScaleRole, d->controlScale);
    d->updatingDatabase = false;
}

void GraphicsViewManager::clearPickedGrips()
{
    d->pitchView->clearPickedGrips();
    d->controlView->clearPickedGrips();
}

QPointF GraphicsViewManager::snappedScenePos(int sceneType, const QPoint &pos) const
{
    IGraphicsGrip *snap_grip = d->snapGrip(sceneType, pos);
    if (snap_grip)
        return snap_grip->position();
    QPointF scene_pos = qobject_cast<GraphicsView*>(view(sceneType))->sceneTransform().inverted().map(QPointF(pos));
    IModelItem *grid_settings = IDatabase::instance()->rootItem()->findItem(GridSettingsItem);
    bool is_snapping = get<bool>(grid_settings, SnapEnabledRole);
    if (!is_snapping)
        return scene_pos;
    bool snap_to_grid = get<qreal>(grid_settings, GridSnapEnabledRole);
    QPointF snapped_pos = scene_pos;
    d->snapX(TimePositionRole, snapped_pos, snap_to_grid);
    if (PitchScene == sceneType)
        d->snapY(PitchPositionRole, snapped_pos, snap_to_grid);
    else if (ControlScene == sceneType)
        d->snapY(ControlPositionRole, snapped_pos, snap_to_grid);
    return snapped_pos;
}

void GraphicsViewManager::updateSelection(const QList<IGraphicsItem*> &ss)
{
    d->pitchView->updateSelection(ss);
    d->controlView->updateSelection(ss);
}

void GraphicsViewManager::updateViews()
{
    if (d->pitchView->isDirty())
        d->pitchView->updateView();
    if (d->controlView->isDirty())
        d->controlView->updateView();
    if (d->timeLabelView->isDirty())
        d->timeLabelView->updateView();
    if (d->pitchLabelView->isDirty())
        d->pitchLabelView->updateView();
    if (d->controlLabelView->isDirty())
        d->controlLabelView->updateView();
    d->finishUndo();
}

void GraphicsViewManager::databaseAboutToBeRead()
{
    disableUpdates();
}

void GraphicsViewManager::databaseRead()
{
    d->updateViewVariables();
    d->emitAllViewSettingsChanged();
    enableUpdates();
    updateViews();
}

void GraphicsViewManager::databaseAboutToBeWritten()
{
    updateDatabase();
}

void GraphicsViewManager::disableUpdates()
{
    for (int i = 0;  i < SceneTypeCount;  ++i)
        view(i)->setUpdatesEnabled(false);
}

void GraphicsViewManager::enableUpdates()
{
    for (int i = 0;  i < SceneTypeCount;  ++i)
        view(i)->setUpdatesEnabled(true);
}

void GraphicsViewManager::dataChanged(IModelItem *item, int role)
{
    if (ViewSettingsItem == item->itemType() && !d->updatingDatabase)
        d->updateViewVariables();
    if (IDatabase::instance()->rootItem() == item && LengthRole == role && !d->updatingDatabase)
        d->updateViewVariables();

    // Remove notes from selection set when their track is turned off.
    if (TrackItem == item->itemType() && VisibilityRole == role) {
        if (!get<bool>(item, role)) {
            IGraphicsItem *track_graphics = query<IGraphicsItem>(item);
            ISelectionSet *ss = IEditor::instance()->currentSelection();
            QList<IGraphicsItem*> ss_items = ss->items();
            foreach (IGraphicsItem *ss_item, ss_items)
                if (track_graphics == ss_item->parent())
                    ss->remove(ss_item);
        }
    }
}

void GraphicsViewManager::modelReset()
{
    IEditor *editor = IEditor::instance();
    editor->currentSelection()->clear();
    editor->currentSelection(NoteItem)->clear();
    editor->currentSelection(TrackItem)->clear();
    d->updateViewVariables();
    enableUpdates();
}

void GraphicsViewManager::startInsertingPoints()
{
    IUndoManager::instance()->pause();
    if (IEditor::instance()->currentSelection(NoteItem)->items().isEmpty())
        QMessageBox::warning(Core::ICore::instance()->mainWindow(), PRO_NAME_STR, "No notes are selected.");
    else
        d->pitchView->startInsertingPoints();
}

void GraphicsViewManager::finishInsertingPoints()
{
    IUndoManager::instance()->resume();
    d->pitchView->finishInsertingPoints();
}

void GraphicsViewManager::cancelPointInsertion()
{
    IUndoManager *undo_manager = IUndoManager::instance();
    if (undo_manager)
        undo_manager->resume();
    d->pitchView->cancelPointInsertion();
}
