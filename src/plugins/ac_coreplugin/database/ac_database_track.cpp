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

#include "ac_database_track.h"

#include <mi_idatabase.h>
#include <mi_iobjectfactory.h>

#include <mi_scopeddatachange.h>

namespace Database {

IAggregator *Track::init()
{
    _notes = query<IObjectFactory>(IDatabase::instance())->create(Ac::NoteListItem);
    return ScoreObject::init();
}

Track::~Track()
{
    delete _notes;
}

IAggregate *Track::ModelData::init()
{
    return ScoreObject::ModelData::init();
}

IAggregate *Track::ModelItem::init()
{
    return ScoreObject::ModelItem::init();
}

} // namespace Database




//#include <ac_graphicsitem.h>
//#include <ac_note.h>
//#include <ac_score.h>

//TrackPrivate::TrackPrivate(Track *q)
//    :   ScoreObjectPrivate(q)
//    ,   color(127.0f, 0.0f, 0.0f)
//    ,   instrument("sine")
//    ,   notes(0)
//    ,   recording(false)
//{
//    mainGraphicsItems.insert(Ac::PitchScene, new GraphicsItem);
//    mainGraphicsItems.insert(Ac::ControlScene, new GraphicsItem);
//}

//void TrackPrivate::init()
//{
//    notes = new ObjectTList<Note>(q_ptr);
//}

//TrackPrivate::~TrackPrivate()
//{
//    qDeleteAll(notes);
//}

//GraphicsParentPrivate *TrackPrivate::graphicsParent() const
//{
//    Q_Q(const Track);
//    Score *score = q->score();
//    return score ? score->d_func() : 0;
//}

//Track::Track(QObject *parent)
//    :   ScoreObject(*(new TrackPrivate(this)), parent)
//{
//    Q_D(Track);
//    d->init();
//    setName("Track");
//}

//qreal Track::length() const
//{
//    Score *score = this->score();
//    return score ? score->length() : 0.0f;
//}

//const QColor &Track::color() const
//{
//    Q_D(const Track);
//    return d->color;
//}

//void Track::setColor(const QColor &color)
//{
//    Q_D(Track);
//    if (d->color == color)
//        return;
//    d->beginChangeData();
//    d->color = color;
//    const int n = d->notes->count();
//    for (int i = 0;  i < n;  ++i)
//        d->notes->at(i)->setColor(color);
//    d->endChangeData();
//}

//const QString &Track::instrument() const
//{
//    Q_D(const Track);
//    return d->instrument;
//}

//void Track::setInstrument(const QString &instrument)
//{
//    Q_D(Track);
//    if (d->instrument == instrument)
//        return;
//    d->beginChangeData();
//    d->instrument = instrument;
//    d->endChangeData();
//}

//bool Track::isVisible() const
//{
//    Q_D(const Track);
//    return d->mainGraphicsItems[Ac::PitchScene]->isVisible();
//}

//void Track::setVisible(bool visible)
//{
//    Q_D(Track);
//    if (isVisible() == visible)
//        return;
//    d->beginChangeData();
//    foreach (QGraphicsItem *item, d->mainGraphicsItems)
//        item->setVisible(visible);
//    if (!visible)
//        setRecording(false);
//    d->endChangeData();
//}

//bool Track::isRecording() const
//{
//    Q_D(const Track);
//    return d->recording;
//}

//void Track::setRecording(bool recording)
//{
//    Q_D(Track);
//    if (d->recording == recording)
//        return;
//    d->beginChangeData();
//    d->recording = recording;
//    if (recording)
//        setVisible(true);
//    d->endChangeData();
//}

//Score *Track::score() const
//{
//    QObject *parent = QObject::parent();
//    return parent ? object_cast<Score>(parent->parent()) : 0;
//}

//ObjectTList<Note> *Track::notes() const
//{
//    Q_D(const Track);
//    return d->notes;
//}

//void Track::setZValue(qreal z)
//{
//    Q_D(Track);
//    d->mainGraphicsItems[Ac::PitchScene]->setZValue(z);
//    d->mainGraphicsItems[Ac::ControlScene]->setZValue(z);
//}

//int Track::modelItemIndex(const IModelItem *item) const
//{
//    Q_D(const Track);
//    if (d->notes == item)
//        return ScoreObject::ModelItemCount;
//    return ScoreObject::modelItemIndex(item);
//}

//IModelItem *Track::modelItemAt(int i) const
//{
//    switch (i) {
//    case ScoreObject::ModelItemCount:
//        return notes();
//    default:
//        return ScoreObject::modelItemAt(i);
//    }
//}

//IModelItem *Track::findModelItemList(int type) const
//{
//    switch (type) {
//    case Ac::NoteItem:
//        return notes();
//    default:
//        return ScoreObject::findModelItemList(type);
//    }
//}

//QVariant Track::data(int role) const
//{
//    switch (role) {
//    case Ac::ColorRole:
//        return color();
//    case Ac::InstrumentRole:
//        return instrument();
//    case Ac::VisibilityRole:
//        return isVisible();
//    case Ac::RecordingRole:
//        return isRecording();
//    default:
//        return ScoreObject::data(role);
//    }
//}

//bool Track::setData(const QVariant &value, int role)
//{
//    switch (role) {
//    case Ac::ColorRole:
//        setColor(value.value<QColor>());
//        return true;
//    case Ac::InstrumentRole:
//        setInstrument(value.toString());
//        return true;
//    case Ac::VisibilityRole:
//        setVisible(value.toBool());
//        return true;
//    case Ac::RecordingRole:
//        setRecording(value.toBool());
//        return true;
//    default:
//        return ScoreObject::setData(value, role);
//    }
//}
