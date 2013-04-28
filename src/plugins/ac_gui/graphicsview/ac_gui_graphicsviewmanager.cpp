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
//#include "ac_undo.h"
#include <ac_core_constants.h>
#include <ac_core_namespace.h>
//#include <ac_noteselectionmodel.h>
#include <mi_core_math.h>
#include <icore.h>
#include <idatabase.h>
#include <ieditor.h>
#include <imodel.h>
#include <imodelitem.h>
#include <iselectionset.h>
#include <mainwindow.h>
#include <QMessageBox>
#include <QTimer>
#include <QWidget>
#include <QtGlobal>

using namespace Ac;

static GraphicsViewManager *instance = 0;

//static qreal closestGridlineLocation(qreal location, const IModelItem *gridlineListItem)
//{
//    qreal min_offset = Q_FLOAT_MAX;
//    qreal closest_location = location;

//    const int n = gridlineListItem->modelItemCount();
//    for (int i = 0;  i < n;  ++i) {
//        const IModelItem *gridline = gridlineListItem->modelItemAt(i);
//        if (gridline->data(VisibilityRole).toBool()) {
//            const qreal current_location = gridline->data(LocationRole).toReal();
//            const qreal current_offset = qAbs(location - current_location);
//            if (current_offset < min_offset) {
//                min_offset = current_offset;
//                closest_location = current_location;
//            }
//        }
//    }
//    return closest_location;
//}

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
//    UndoViewSettingsCommand *undoCmd;
    QTimer *updateViewsTimer;
    uint initialized : 1;
    uint updatingDatabase : 1;

    GraphicsViewManagerPrivate(GraphicsViewManager *q)
        :   q(q)
        ,   sceneManager(new GraphicsSceneManager(q))
        ,   pitchView(0)
        ,   controlView(0)
        ,   timeLabelView(0)
        ,   pitchLabelView(0)
        ,   controlLabelView(0)
//        ,   undoCmd(0)
        ,   updateViewsTimer(new QTimer(q))
        ,   initialized(false)
        ,   updatingDatabase(false)
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

//        IDatabase *db = IDatabase::instance();
//        q->connect(db, SIGNAL(databaseAboutToBeRead()), q, SLOT(databaseAboutToBeRead()));
//        q->connect(db, SIGNAL(databaseRead()), q, SLOT(databaseRead()));
//        q->connect(db, SIGNAL(databaseAboutToBeWritten()), q, SLOT(databaseAboutToBeWritten()));

        IModel *model = IModel::instance();
        q->connect(model, SIGNAL(modelAboutToBeReset()), pitchView, SLOT(modelAboutToBeReset()));
        q->connect(model, SIGNAL(modelAboutToBeReset()), controlView, SLOT(modelAboutToBeReset()));
        q->connect(model, SIGNAL(modelAboutToBeReset()), timeLabelView, SLOT(modelAboutToBeReset()));
        q->connect(model, SIGNAL(modelAboutToBeReset()), pitchLabelView, SLOT(modelAboutToBeReset()));
        q->connect(model, SIGNAL(modelAboutToBeReset()), controlLabelView, SLOT(modelAboutToBeReset()));
        q->connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), pitchView, SLOT(dataChanged(QModelIndex,QModelIndex)));
        q->connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), controlView, SLOT(dataChanged(QModelIndex,QModelIndex)));
        q->connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), timeLabelView, SLOT(dataChanged(QModelIndex,QModelIndex)));
        q->connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), pitchLabelView, SLOT(dataChanged(QModelIndex,QModelIndex)));
        q->connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), controlLabelView, SLOT(dataChanged(QModelIndex,QModelIndex)));
//        q->connect(model, SIGNAL(pointsChanged(QModelIndex)), pitchView, SLOT(dataChanged(QModelIndex)));
//        q->connect(model, SIGNAL(pointsChanged(QModelIndex)), controlView, SLOT(dataChanged(QModelIndex)));

//        QItemSelectionModel *noteSSModel = NoteSelectionModel::instance();
//        q->connect(noteSSModel, SIGNAL(selectionChanged(QItemSelection,QItemSelection)), pitchView, SLOT(noteSelectionChanged(QItemSelection,QItemSelection)));
//        q->connect(noteSSModel, SIGNAL(selectionChanged(QItemSelection,QItemSelection)), controlView, SLOT(noteSelectionChanged(QItemSelection,QItemSelection)));

        updateViewVariables();
        q->updateViews();
        initialized = true;
    }

    ~GraphicsViewManagerPrivate()
    {
//        delete undoCmd;
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
        q->setPosition(get<qreal>(view_settings, TimePositionRole), TimePositionRole);
        q->setPosition(get<qreal>(view_settings, PitchPositionRole), PitchPositionRole);
        q->setPosition(get<qreal>(view_settings, ControlPositionRole), ControlPositionRole);
        q->setScale(get<qreal>(view_settings, TimeScaleRole), TimeScaleRole);
        q->setScale(get<qreal>(view_settings, PitchScaleRole), PitchScaleRole);
        q->setScale(get<qreal>(view_settings, ControlScaleRole), ControlScaleRole);
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
//        if (!undoCmd
//                && initialized
//                && !IDatabase::instance()->isReading()
//                && !IEditor::instance()->isInCommand())
//            undoCmd = new UndoViewSettingsCommand;
    }

    void finishUndo()
    {
//        if (undoCmd) {
//            IEditor::instance()->pushCommand(undoCmd);
//            undoCmd = 0;
//        }
    }

    void snapX(QPointF &pos, int role, bool snapToGrid)
    {
//        qreal toX = -1.0f;

//        if (TimePositionRole == role) {
//            if (snapToGrid)
//                toX = ::closestGridlineLocation(pos.x(), IModel::instance()->rootItem()->findModelItem(GridSettingsItem)->findModelItemList(TimeGridLineItem));
//            else
//                toX = IModel::instance()->rootItem()->findModelItem(GridSettingsItem)->data(TimeSnapRole).toReal();
//        }

//        if (snapToGrid)
//            pos.setX(toX);
//        else if (0.0f < toX)
//            pos.setX(Mi::roundToNearest(pos.x(), toX));
    }

    void snapY(QPointF &pos, int role, bool snapToGrid)
    {
//        qreal toY = -1.0f;

//        if (PitchPositionRole == role) {
//            if (snapToGrid)
//                toY = ::closestGridlineLocation(pos.y(), IModel::instance()->rootItem()->findModelItem(GridSettingsItem)->findModelItemList(PitchGridLineItem));
//            else
//                toY = IModel::instance()->rootItem()->findModelItem(GridSettingsItem)->data(PitchSnapRole).toReal();
//        } else if (ControlPositionRole == role) {
//            if (snapToGrid)
//                toY = ::closestGridlineLocation(pos.y(), IModel::instance()->rootItem()->findModelItem(GridSettingsItem)->findModelItemList(ControlGridLineItem));
//            else
//                toY = IModel::instance()->rootItem()->findModelItem(GridSettingsItem)->data(ControlSnapRole).toReal();
//        }

//        if (snapToGrid)
//            pos.setY(toY);
//        else if (0.0f < toY)
//            pos.setY(Mi::roundToNearest(pos.y(), toY));
    }
};

GraphicsViewManager::GraphicsViewManager(QWidget *widget)
    :   QObject(widget)
    ,   d(new GraphicsViewManagerPrivate(this))
{
    ::instance = this;
    d->init();
    IModel *model = IModel::instance();
    connect(model, SIGNAL(dataChanged(const IModelItem*,int)), SLOT(dataChanged(const IModelItem*)));
    connect(model, SIGNAL(modelAboutToBeReset()), SLOT(disableUpdates()));
    connect(model, SIGNAL(modelReset()), SLOT(modelReset()));
    connect(d->updateViewsTimer, SIGNAL(timeout()), SLOT(updateViews()));
}

GraphicsViewManager::~GraphicsViewManager()
{
    cancelPointInsertion();
    delete d;
}

GraphicsViewManager *GraphicsViewManager::instance()
{
    return ::instance;
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

void GraphicsViewManager::setPosition(qreal position, int role)
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

void GraphicsViewManager::setScale(qreal scale, int role)
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
//    IModel *model = IModel::instance();
//    const QModelIndex viewSettings = model->itemIndex(ViewSettingsItem);
//    d->updatingDatabase = true;
//    model->setData(viewSettings, d->timePos, TimePositionRole);
//    model->setData(viewSettings, d->pitchPos, PitchPositionRole);
//    model->setData(viewSettings, d->controlPos, ControlPositionRole);
//    model->setData(viewSettings, d->timeScale, TimeScaleRole);
//    model->setData(viewSettings, d->pitchScale, PitchScaleRole);
//    model->setData(viewSettings, d->controlScale, ControlScaleRole);
//    d->updatingDatabase = false;
}

void GraphicsViewManager::clearPickedGrips()
{
    d->pitchView->clearPickedGrips();
    d->controlView->clearPickedGrips();
}

QPointF GraphicsViewManager::snappedScenePos(const QPointF &pos, int sceneType) const
{
//    IModel *model = IModel::instance();
//    IModelItem *gridSettings = model->rootItem()->findModelItem(GridSettingsItem);

//    bool is_snapping = gridSettings->data(SnapEnabledRole).toBool();
//    if (!is_snapping)
//        return pos;

//    bool snap_to_grid = gridSettings->data(GridSnapEnabledRole).toBool();

    QPointF snapped_pos = pos;
//    d->snapX(snapped_pos, TimePositionRole, snap_to_grid);
//    if (PitchScene == sceneType)
//        d->snapY(snapped_pos, PitchPositionRole, snap_to_grid);
//    else if (ControlScene == sceneType)
//        d->snapY(snapped_pos, ControlPositionRole, snap_to_grid);
    return snapped_pos;
}

void GraphicsViewManager::updateSelection(const QList<IGraphicsItem *> &ss)
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

void GraphicsViewManager::dataChanged(const IModelItem *item)
{
    if (!d->updatingDatabase
            && ViewSettingsItem == item->itemType())
        d->updateViewVariables();
}

void GraphicsViewManager::modelReset()
{
    d->updateViewVariables();
    enableUpdates();
}

void GraphicsViewManager::startInsertingPoints()
{
    IEditor *editor = IEditor::instance();
    editor->startCreating();
    if (editor->currentSelection()->items().isEmpty())
        QMessageBox::warning(Core::ICore::instance()->mainWindow(), PRO_NAME_STR, "No notes are selected.");
    else
        d->pitchView->startInsertingPoints();
}

void GraphicsViewManager::finishInsertingPoints()
{
    IEditor::instance()->finishCreating();
    d->pitchView->finishInsertingPoints();
}

void GraphicsViewManager::cancelPointInsertion()
{
    IEditor *editor = IEditor::instance();
    if (!editor)
        return;
    editor->finishCreating();
    d->pitchView->cancelPointInsertion();
}

//void GraphicsViewManager::selectAllGrips()
//{
//    d->pitchView->selectAllGrips();
//}

//void GraphicsViewManager::startGripDrag()
//{
//    d->pitchView->startGripDrag();
//}
