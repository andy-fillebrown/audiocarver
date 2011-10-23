/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2011 Andrew Fillebrown.
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

#include "ac_model.h"

#include <ac_gridsettings.h>
#include <ac_score.h>
#include <ac_viewsettings.h>

void ModelPrivate::init()
{
    score = new Score(q);
    score->setModel(q);
}

ModelPrivate::~ModelPrivate()
{
    delete score;
}

QModelIndex ModelPrivate::indexFromItem(IModelItem *item) const
{
    if (!item)
        return QModelIndex();
    IModelItem *parentItem = item->parentModelItem();
    if (!parentItem)
        return QModelIndex();
    return q->createIndex(parentItem->modelItemIndex(item), 0, parentItem);
}

IModelItem *ModelPrivate::itemFromIndex(const QModelIndex &index) const
{
    if ((index.row() < 0)
            || (index.column() < 0)
            || (index.model() != q))
        return 0;
    IModelItem *parentItem = static_cast<IModelItem*>(index.internalPointer());
    if (!parentItem)
        return 0;
    return parentItem->modelItemAt(index.row());
}

Model::Model(QObject *parent)
    :   QAbstractItemModel(parent)
    ,   d(new ModelPrivate(this))
{
    d->init();
    connect(d->score, SIGNAL(aboutToBeReset()), SIGNAL(modelAboutToBeReset()));
    connect(d->score, SIGNAL(reset()), SIGNAL(modelReset()));
}

Model::~Model()
{
    delete d;
}

Score *Model::score() const
{
    return d->score;
}

QGraphicsItem *Model::sceneItem(Ac::SceneType type) const
{
    return d->score ? d->score->sceneItem(type) : 0;
}

QModelIndex Model::index(int row, int column, const QModelIndex &parent) const
{
    IModelItem *parentItem = parent.isValid() ? d->itemFromIndex(parent) : d->score;
    if (!parentItem
            || row < 0
            || column < 0
            || parentItem->modelItemCount() <= row
            || 1 <= column)
        return QModelIndex();
    return createIndex(row, column, parentItem);
}

QModelIndex Model::parent(const QModelIndex &child) const
{
    if (child.row() < 0
            || child.column() < 0
            || child.model() != this)
        return QModelIndex();
    return d->indexFromItem(static_cast<IModelItem*>(child.internalPointer()));
}

int Model::rowCount(const QModelIndex &parent) const
{
    IModelItem *parentItem = parent.isValid() ? d->itemFromIndex(parent) : d->score;
    return parentItem ? parentItem->modelItemCount() : 0;
}

QVariant Model::data(const QModelIndex &index, int role) const
{
    IModelItem *item = index.isValid() ? d->itemFromIndex(index) : d->score;
    return item ? item->data(role) : QVariant();
}

bool Model::setData(const QModelIndex &index, const QVariant &value, int role)
{
    IModelItem *item = index.isValid() ? d->itemFromIndex(index) : d->score;
    return item ? item->setData(value, role) : false;
}

Qt::ItemFlags Model::flags(const QModelIndex &index) const
{
    IModelItem *item = index.isValid() ? d->itemFromIndex(index) : d->score;
    return item ? item->flags() : Qt::NoItemFlags;
}

QModelIndex Model::viewSettingsIndex() const
{
    return d->indexFromItem(d->score->viewSettings());
}

QModelIndex Model::timeGridLineListIndex() const
{
    return d->indexFromItem(d->score->gridSettings()->timeGridLines());
}

QModelIndex Model::pitchGridLineListIndex() const
{
    return d->indexFromItem(d->score->gridSettings()->pitchGridLines());
}

QModelIndex Model::controlGridLineListIndex() const
{
    return d->indexFromItem(d->score->gridSettings()->controlGridLines());
}
