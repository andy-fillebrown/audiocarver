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

class ModelPrivate
{
public:
    Score *score;

    ModelPrivate(Model *q)
        :   score(new Score(q))
    {}
};

Model::Model()
    :   d(new ModelPrivate(this))
{
    connect(d->score, SIGNAL(aboutToBeReset()), SIGNAL(modelAboutToBeReset()));
    connect(d->score, SIGNAL(reset()), SIGNAL(modelReset()));
}

Model::~Model()
{
    delete d;
}

QGraphicsItem *Model::sceneItem(int type) const
{
    return d->score ? d->score->sceneItem(type) : 0;
}

IModelItem *Model::rootItem() const
{
    return objectToInterface_cast<IModelItem>(d->score);
}

QModelIndex Model::itemIndex(int type) const
{
    switch (type) {
    case Ac::ViewSettingsItem:
        return indexFromItem(d->score->viewSettings());
    default:
        return QModelIndex();
    }
}

QModelIndex Model::listIndex(int type) const
{
    switch (type) {
    case Ac::TrackItem:
        return indexFromItem(d->score->tracks());
    case Ac::TimeGridLineItem:
        return indexFromItem(d->score->gridSettings()->timeGridLines());
    case Ac::PitchGridLineItem:
        return indexFromItem(d->score->gridSettings()->pitchGridLines());
    case Ac::ControlGridLineItem:
        return indexFromItem(d->score->gridSettings()->controlGridLines());
    default:
        return QModelIndex();
    }
}
