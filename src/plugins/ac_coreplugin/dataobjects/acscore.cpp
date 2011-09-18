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

#include "acscore.h"

#include <actrack.h>

class ScorePrivate : public ScoreObjectPrivate
{
public:
    qreal length;
    ObjectList<Track> *tracks;

    ScorePrivate(Score *q)
        :   ScoreObjectPrivate(q)
        ,   length(128.0f)
        ,   tracks(0)
    {}

    void init()
    {
        tracks = new ObjectList<Track>(q);
    }
};

Score::Score(QObject *parent)
    :   ScoreObject(*(new ScorePrivate(this)), parent)
{
    Q_D(Score);
    d->init();
    setObjectName("Score");
}

qreal Score::length() const
{
    Q_D(const Score);
    return d->length;
}

void Score::setLength(qreal length)
{
    Q_D(Score);
    if (d->length == length)
        return;
    d->length = length;
}

ObjectList<Track> *Score::tracks() const
{
    Q_D(const Score);
    return d->tracks;
}

void Score::setModel(Model *model)
{
    d_ptr->setModel(model);
}

int Score::modelItemIndex(IModelItem *item) const
{
    Q_D(const Score);
    if (d->tracks == item)
        return ScoreObject::ModelItemCount;
    return ScoreObject::modelItemIndex(item);
}

IModelItem *Score::modelItemAt(int i) const
{
    switch (i) {
    case ScoreObject::ModelItemCount:
        return tracks();
    default:
        return ScoreObject::modelItemAt(i);
    }
}

IModelItem *Score::findModelItemList(ItemType type) const
{
    switch (type) {
    case TrackItem:
        return tracks();
    default:
        return ScoreObject::findModelItemList(type);
    }
}

bool Score::setData(const QVariant &value, int role)
{
    switch (role) {
    case LengthRole:
        setLength(value.toReal());
        return true;
    default:
        return ScoreObject::setData(value, role);
    }
}
