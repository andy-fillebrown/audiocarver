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

#include "actrack.h"

#include <acgraphicsitem.h>
#include <acnote.h>
#include <acscore.h>

class TrackPrivate : public ScoreObjectPrivate
{
public:
    QColor color;
    QString instrument;
    ObjectList<Note> *notes;

    TrackPrivate(Track *q)
        :   ScoreObjectPrivate(q)
        ,   color(127.0f, 0.0f, 0.0f)
        ,   notes(0)
    {}

    void init()
    {
        notes = new ObjectList<Note>(q_ptr);
        mainGraphicsItems.insert(Ac::PitchScene, new GraphicsItem);
        mainGraphicsItems.insert(Ac::ControlScene, new GraphicsItem);
        ScoreObjectPrivate::init();
    }

    ~TrackPrivate()
    {
        qDeleteAll(notes);
    }
};

Track::Track(QObject *parent)
    :   ScoreObject(*(new TrackPrivate(this)), parent)
{
    Q_D(Track);
    d->init();
    setObjectName("Track");
}

qreal Track::length() const
{
    Score *score = this->score();
    return score ? score->length() : 0.0f;
}

const QColor &Track::color() const
{
    Q_D(const Track);
    return d->color;
}

void Track::setColor(const QColor &color)
{
    Q_D(Track);
    if (d->color == color)
        return;
    d->beginChangeData();
    d->color = color;
    d->endChangeData();
}

const QString &Track::instrument() const
{
    Q_D(const Track);
    return d->instrument;
}

void Track::setInstrument(const QString &instrument)
{
    Q_D(Track);
    if (d->instrument == instrument)
        return;
    d->beginChangeData();
    d->instrument = instrument;
    d->endChangeData();
}

bool Track::isVisible() const
{
    Q_D(const Track);
    return d->mainGraphicsItems[Ac::PitchScene]->isVisible();
}

void Track::setVisibility(bool visible)
{
    Q_D(Track);
    if (isVisible() == visible)
        return;
    d->beginChangeData();
    foreach (QGraphicsItem *item, d->mainGraphicsItems)
        item->setVisible(visible);
    d->endChangeData();
}

Score *Track::score() const
{
    QObject *parent = QObject::parent();
    return parent ? qobject_cast<Score*>(parent->parent()) : 0;
}

ObjectList<Note> *Track::notes() const
{
    Q_D(const Track);
    return d->notes;
}

ScoreObject *Track::graphicsParent() const
{
    return score();
}

int Track::modelItemIndex(IModelItem *item) const
{
    Q_D(const Track);
    if (d->notes == item)
        return ScoreObject::ModelItemCount;
    return ScoreObject::modelItemIndex(item);
}

IModelItem *Track::modelItemAt(int i) const
{
    switch (i) {
    case ScoreObject::ModelItemCount:
        return notes();
    default:
        return ScoreObject::modelItemAt(i);
    }
}

IModelItem *Track::findModelItemList(Ac::ItemType type) const
{
    switch (type) {
    case Ac::NoteItem:
        return notes();
    default:
        return ScoreObject::findModelItemList(type);
    }
}

QVariant Track::data(int role) const
{
    switch (role) {
    case Ac::ColorRole:
        return color();
    case Ac::InstrumentRole:
        return instrument();
    default:
        return ScoreObject::data(role);
    }
}

bool Track::setData(const QVariant &value, int role)
{
    switch (role) {
    case Ac::ColorRole:
        setColor(value.value<QColor>());
        return true;
    case Ac::InstrumentRole:
        setInstrument(value.toString());
        return true;
    default:
        return ScoreObject::setData(value, role);
    }
}
