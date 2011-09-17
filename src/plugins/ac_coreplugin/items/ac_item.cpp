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

#include "ac_item.h"
#include <ac_model.h>

void ObjectPrivate::setModel(Model *model)
{
    if (this->model == model)
        return;
    this->model = model;
    int n = q->componentCount();
    for (int i = 0;  i < n;  ++i)
        q->componentAt(i)->d_ptr->setModel(model);
}

void ObjectPrivate::beginInsertObjects(int first, int last)
{
    if (model)
        model->beginInsertColumns(model->indexFromItem(q), first, last);
}

void ObjectPrivate::endInsertObjects()
{
    if (model)
        model->endInsertColumns();
}

void ObjectPrivate::beginRemoveObjects(int first, int last)
{
    if (model)
        model->beginRemoveColumns(model->indexFromItem(q), first, last);
}

void ObjectPrivate::endRemoveObjects()
{
    if (model)
        model->endRemoveColumns();
}

class CurvePrivate : public ObjectPrivate
{
public:
    PointList points;

    CurvePrivate(Curve *q)
        :   ObjectPrivate(q)
    {}
};

Curve::Curve(CurvePrivate &dd, QObject *parent)
    :   Object(dd, parent)
{}

const PointList &Curve::points() const
{
    Q_D(const Curve);
    return d->points;
}

void Curve::setPoints(const PointList &points)
{
    Q_D(Curve);
    if (d->points == points)
        return;
    d->points = points;
}

ScoreObject *Curve::parent() const
{
    return qobject_cast<ScoreObject*>(QObject::parent());
}

QVariant Curve::data(int role) const
{
    switch (role) {
    case PointsRole:
        return QVariant::fromValue(points());
    default:
        return Object::data(role);
    }
}

bool Curve::setData(const QVariant &value, int role)
{
    switch (role) {
    case PointsRole:
        setPoints(value.value<PointList>());
        return true;
    default:
        return Object::setData(value, role);
    }
}

class PitchCurvePrivate : public CurvePrivate
{
public:
    PitchCurvePrivate(PitchCurve *q)
        :   CurvePrivate(q)
    {}

    void conformPoints()
    {
    }
};

PitchCurve::PitchCurve(QObject *parent)
    :   Curve(*(new PitchCurvePrivate(this)), parent)
{
    setObjectName("PitchCurve");
}

void PitchCurve::setPoints(const PointList &points)
{
    Q_D(PitchCurve);
    Curve::setPoints(points);
    d->conformPoints();
}

class ControlCurvePrivate : public CurvePrivate
{
public:
    int controlId;

    ControlCurvePrivate(ControlCurve *q)
        :   CurvePrivate(q)
        ,   controlId(0)
    {}

    void conformPoints()
    {
    }
};

ControlCurve::ControlCurve(QObject *parent)
    :   Curve(*(new ControlCurvePrivate(this)), parent)
{
    setObjectName("ControlCurve");
}

int ControlCurve::controlId() const
{
    Q_D(const ControlCurve);
    return d->controlId;
}

void ControlCurve::setControlId(int controlId)
{
    Q_D(ControlCurve);
    if (d->controlId == controlId)
        return;
    d->controlId = controlId;
}

void ControlCurve::setPoints(const PointList &points)
{
    Q_D(ControlCurve);
    Curve::setPoints(points);
    d->conformPoints();
}

QVariant ControlCurve::data(int role) const
{
    switch (role) {
    case ControlIdRole:
        return controlId();
    default:
        return Curve::data(role);
    }
}

bool ControlCurve::setData(const QVariant &value, int role)
{
    switch (role) {
    case ControlIdRole:
        setControlId(value.toInt());
        return true;
    default:
        return Curve::setData(value, role);
    }
}

class ScoreObjectPrivate : public ObjectPrivate
{
public:
    qreal volume;
    PitchCurve *pitchCurve;
    ObjectList<ControlCurve> *controlCurves;

    ScoreObjectPrivate(ScoreObject *q)
        :   ObjectPrivate(q)
        ,   volume(1.0f)
        ,   pitchCurve(0)
        ,   controlCurves(0)
    {}

    void init()
    {
        pitchCurve = new PitchCurve(q);
        controlCurves = new ObjectList<ControlCurve>(q);
    }
};

ScoreObject::ScoreObject(ScoreObjectPrivate &dd, QObject *parent)
    :   Object(dd, parent)
{
    Q_D(ScoreObject);
    d->init();
}

qreal ScoreObject::volume() const
{
    Q_D(const ScoreObject);
    return d->volume;
}

void ScoreObject::setVolume(qreal volume)
{
    Q_D(ScoreObject);
    if (d->volume == volume)
        return;
    d->volume = volume;
}

PitchCurve *ScoreObject::pitchCurve() const
{
    Q_D(const ScoreObject);
    return d->pitchCurve;
}

ObjectList<ControlCurve> *ScoreObject::controlCurves() const
{
    Q_D(const ScoreObject);
    return d->controlCurves;
}

QVariant ScoreObject::data(int role) const
{
    switch (role) {
    case LengthRole:
        return length();
    case VolumeRole:
        return volume();
    default:
        return Object::data(role);
    }
}

bool ScoreObject::setData(const QVariant &value, int role)
{
    switch (role) {
    case VolumeRole:
        setVolume(value.toReal());
        return true;
    default:
        return Object::setData(value, role);
    }
}

int ScoreObject::componentIndex(Object *component) const
{
    Q_D(const ScoreObject);
    if (d->pitchCurve == component)
        return 0;
    if (d->controlCurves == component)
        return 1;
    return Object::componentIndex(component);
}

Object *ScoreObject::componentAt(int i) const
{
    switch (i) {
    case 0:
        return pitchCurve();
    case 1:
        return controlCurves();
    default:
        return 0;
    }
}

Object *ScoreObject::findComponent(ItemType type) const
{
    switch (type) {
    case PitchCurveItem:
        return pitchCurve();
    default:
        return 0;
    }
}

Object *ScoreObject::findComponentList(ItemType type) const
{
    switch (type) {
    case ControlCurveItem:
        return controlCurves();
    default:
        return 0;
    }
}

class NotePrivate : public ScoreObjectPrivate
{
public:
    qreal length;

    NotePrivate(Note *q)
        :   ScoreObjectPrivate(q)
        ,   length(0.0f)
    {}
};

Note::Note(QObject *parent)
    :   ScoreObject(*(new NotePrivate(this)), parent)
{
    setObjectName("Note");
}

qreal Note::length() const
{
    Q_D(const Note);
    return d->length;
}

void Note::setLength(qreal length)
{
    Q_D(Note);
    if (d->length == length)
        return;
    d->length = length;
}

Track *Note::parent() const
{
    return qobject_cast<Track*>(QObject::parent());
}

bool Note::setData(const QVariant &value, int role)
{
    switch (role) {
    case LengthRole:
        setLength(value.toReal());
        return true;
    default:
        return ScoreObject::setData(value, role);
    }
}

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
        notes = new ObjectList<Note>(q);
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
    Score *score = parent();
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
    d->color = color;
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
    d->instrument = instrument;
}

Score *Track::parent() const
{
    return qobject_cast<Score*>(QObject::parent());
}

ObjectList<Note> *Track::notes() const
{
    Q_D(const Track);
    return d->notes;
}

int Track::componentIndex(Object *component) const
{
    Q_D(const Track);
    if (d->notes == component)
        return ScoreObject::ComponentCount;
    return ScoreObject::componentIndex(component);
}

Object *Track::componentAt(int i) const
{
    switch (i) {
    case ScoreObject::ComponentCount:
        return notes();
    default:
        return ScoreObject::componentAt(i);
    }
}

Object *Track::findComponentList(ItemType type) const
{
    switch (type) {
    case NoteItem:
        return notes();
    default:
        return ScoreObject::findComponentList(type);
    }
}

QVariant Track::data(int role) const
{
    switch (role) {
    case ColorRole:
        return color();
    case InstrumentRole:
        return instrument();
    default:
        return ScoreObject::data(role);
    }
}

bool Track::setData(const QVariant &value, int role)
{
    switch (role) {
    case ColorRole:
        setColor(value.value<QColor>());
        return true;
    case InstrumentRole:
        setInstrument(value.toString());
        return true;
    default:
        return ScoreObject::setData(value, role);
    }
}

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

int Score::componentIndex(Object *component) const
{
    Q_D(const Score);
    if (d->tracks == component)
        return ScoreObject::ComponentCount;
    return ScoreObject::componentIndex(component);
}

Object *Score::componentAt(int i) const
{
    switch (i) {
    case ScoreObject::ComponentCount:
        return tracks();
    default:
        return ScoreObject::componentAt(i);
    }
}

Object *Score::findComponentList(ItemType type) const
{
    switch (type) {
    case TrackItem:
        return tracks();
    default:
        return ScoreObject::findComponentList(type);
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
