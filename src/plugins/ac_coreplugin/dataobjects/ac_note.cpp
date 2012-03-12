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

#include "ac_note.h"

#include <ac_controlcurve.h>
#include <ac_graphicsitem.h>
#include <ac_pitchcurve.h>
#include <ac_track.h>

class VelocityItem : public IEntity
        ,   public ISubEntity
{
    Note *note;
    PointList pts;

public:
    QGraphicsLineItem *graphicsLineItem;

    VelocityItem(Note *note)
        :   note(note)
        ,   graphicsLineItem(new QGraphicsLineItem)
    {
        graphicsLineItem->setData(0, quintptr(this));

        pts.append(Point());
        updatePoints();

        QPen pen;
        pen.setCosmetic(true);
        pen.setCapStyle(Qt::FlatCap);
        graphicsLineItem->setPen(pen);
        unhighlight();
    }

    void updatePoints()
    {
        const PointList &pitchPts = note->pitchCurve()->points();
        const qreal x = pitchPts.count() ? pitchPts.first().pos.x() : 0;
        pts[0].pos.setX(x);
        pts[0].pos.setY(note->volume());
        graphicsLineItem->setLine(x, 0.0f, x, pts[0].pos.y());
    }

    void setColor(const QColor &color)
    {
        QPen pen = graphicsLineItem->pen();
        pen.setColor(color);
        graphicsLineItem->setPen(pen);
    }

    // ISubEntity
    IEntity *parentEntity() const
    {
        return objectToInterface_cast<IEntity>(note);
    }

    int sceneType() const
    {
        return Ac::ControlScene;
    }

    bool isCurve() const
    {
        return false;
    }

    // IEntity
    const PointList &points() const
    {
        return pts;
    }

    void setPoints(const PointList &points, Ac::DragState dragState)
    {
        note->setVolume(points.first().pos.y(), dragState);
    }

    void highlight()
    {
        QPen pen = graphicsLineItem->pen();
        pen.setWidth(5.0f);
        graphicsLineItem->setPen(pen);
    }

    void unhighlight()
    {
        QPen pen = graphicsLineItem->pen();
        pen.setWidth(3.0f);
        graphicsLineItem->setPen(pen);
    }

    bool intersects(const QRectF &rect) const
    {
        QLineF line = graphicsLineItem->line();
        if (rect.contains(line.p1()) && rect.contains(line.p2()))
            return true;
        if (QLineF::BoundedIntersection == line.intersect(QLineF(rect.topLeft(), rect.topRight()), 0))
            return true;
        if (QLineF::BoundedIntersection == line.intersect(QLineF(rect.topRight(), rect.bottomRight()), 0))
            return true;
        if (QLineF::BoundedIntersection == line.intersect(QLineF(rect.bottomRight(), rect.bottomLeft()), 0))
            return true;
        if (QLineF::BoundedIntersection == line.intersect(QLineF(rect.bottomLeft(), rect.topLeft()), 0))
            return true;
        return false;
    }

    bool isVisible() const
    {
        return graphicsLineItem->isVisible();
    }

    QList<IEntity*> subEntities(int sceneType) const
    {
        Q_UNUSED(sceneType);
        return QList<IEntity*>();
    }

    // IUnknown
    void *query(int type) const
    {
        switch (type) {
        case IEntity::Type:
            return objectToInterface_cast<IEntity>(this);
        case ISubEntity::Type:
            return objectToInterface_cast<ISubEntity>(this);
        default:
            return 0;
        }
    }
};

class NotePrivate : public ScoreObjectPrivate
{
    Q_DECLARE_PUBLIC(Note)

public:
    VelocityItem *velocityItem;

    NotePrivate(Note *q)
        :   ScoreObjectPrivate(q)
        ,   velocityItem(0)
    {
        mainGraphicsItems.insert(Ac::PitchScene, new GraphicsItem);
        mainGraphicsItems.insert(Ac::ControlScene, new GraphicsItem);
    }

    void init()
    {
        Q_Q(Note);
        velocityItem = new VelocityItem(q);
        mainGraphicsItems.insert(Ac::ControlScene, velocityItem->graphicsLineItem);
    }

    ~NotePrivate()
    {
        delete velocityItem;
    }

    void updateGraphicsParent()
    {
        ScoreObjectPrivate::updateGraphicsParent();
        Q_Q(Note);
        const Track *track = q->track();
        if (!track)
            return;
        q->setColor(track->color());
    }

    GraphicsParentPrivate *graphicsParent() const
    {
        Q_Q(const Note);
        Track *track = q->track();
        return track ? track->d_func() : 0;
    }
};

Note::Note(QObject *parent)
    :   ScoreObject(*(new NotePrivate(this)), parent)
{
    Q_D(Note);
    d->init();
    setName("Note");
}

Track *Note::track() const
{
    QObject *parent = QObject::parent();
    return parent ? object_cast<Track>(parent->parent()) : 0;
}

void Note::setColor(const QColor &color)
{
    Q_D(Note);
    d->pitchCurve->setColor(color);
    const int n = d->controlCurves->count();
    for (int i = 0;  i < n;  ++i)
        d->controlCurves->at(i)->setColor(color);
    d->velocityItem->setColor(color);
}

qreal Note::length() const
{
    Q_D(const Note);
    const PointList &pts = d->pitchCurve->points();
    return pts.last().pos.x() - pts.first().pos.x();
}

void Note::updatePoints()
{
    Q_D(Note);
    d->velocityItem->updatePoints();
    d->emitPointsChanged();
}

const PointList &Note::points() const
{
    static PointList dummy;
    return dummy;
}

void Note::setPoints(const PointList &points, Ac::DragState dragState)
{
    Q_UNUSED(points);
    Q_UNUSED(dragState);
}

void Note::highlight()
{
    Q_D(Note);
    d->pitchCurve->highlight();
    int n = d->controlCurves->count();
    for (int i = 0;  i < n;  ++i)
        d->controlCurves->at(i)->highlight();
    d->velocityItem->highlight();
}

void Note::unhighlight()
{
    Q_D(Note);
    d->pitchCurve->unhighlight();
    int n = d->controlCurves->count();
    for (int i = 0;  i < n;  ++i)
        d->controlCurves->at(i)->unhighlight();
    d->velocityItem->unhighlight();
}

bool Note::isVisible() const
{
    return track()->isVisible();
}

QList<IEntity*> Note::subEntities(int sceneType) const
{
    QList<IEntity*> sub_ents;
    Q_D(const Note);
    switch(sceneType) {
    case Ac::PitchScene:
        sub_ents.append(objectToInterface_cast<IEntity>(d->pitchCurve));
        break;
    case Ac::ControlScene: {
        const int n = d->controlCurves->count();
        sub_ents.reserve(n + 1);
        for (int i = 0;  i < n;  ++i)
            sub_ents.append(objectToInterface_cast<IEntity>(d->controlCurves->at(i)));
        sub_ents.append(objectToInterface_cast<IEntity>(d->velocityItem));
        break;
    }
    default:
        break;
    }
    return sub_ents;
}
