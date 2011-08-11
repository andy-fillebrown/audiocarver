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

#ifndef AC_ITEM_H
#define AC_ITEM_H

#include <QGraphicsPathItem>
#include <QPen>

#include <QList>
#include <QPointF>

enum SceneType {
    Pitch,
    Volume,
    TimeLabel,
    PitchLabel,
    VolumeLabel,
    SceneTypeCount
};

class GraphicsItem : public QGraphicsItem
{
public:
    QRectF boundingRect() const
    {
        static QRectF r;
        return r;
    }

    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*)
    {}
};

class GraphicsRootItem : public GraphicsItem
{
public:
    GraphicsRootItem()
    {
        setTransform(QTransform::fromScale(1.0f, -1.0f));
    }
};

class GraphicsPathItem : public QGraphicsPathItem
{
public:
    GraphicsPathItem()
    {
        setBoundingRegionGranularity(1.0f);
    }

    QPainterPath shape() const
    {
        return path();
    }
};

class CurvePathItem : public GraphicsPathItem
{
public:
    CurvePathItem()
    {
        unhighlight();
    }

    void highlight()
    {
        setPen(QPen(QBrush(Qt::red), 4.0f));
    }

    void unhighlight()
    {
        setPen(QPen(QBrush(Qt::red), 2.0f));
    }
};

class GuidePathItem : public GraphicsPathItem
{
public:
    GuidePathItem()
    {
        setFlag(QGraphicsItem::ItemStacksBehindParent);
        setPen(QPen(QBrush(Qt::lightGray), 1.0f, Qt::DotLine));
        hide();
    }
};

class CurvePoint
{
public:
    enum CurveType {
        NoCurve,
        BezierCurve
    };

    qreal x;
    qreal y;
    CurveType curveType;

    CurvePoint(qreal x = 0.0f,
               qreal y = 0.0f,
               CurveType curveType = NoCurve)
        :   x(x)
        ,   y(y)
        ,   curveType(curveType)
    {}

    operator QPointF() const
    {
        return QPointF(x, y);
    }

    bool operator<(const CurvePoint &cp) const
    {
        return x == cp.x ? y < cp.y : x < cp.x;
    }
};

typedef QList<CurvePoint> CurvePoints;

class Curve
{
    CurvePathItem *curveItem;
    GuidePathItem *guideItem;

protected:
    CurvePoints pts;

public:
    Curve()
        :   curveItem(new CurvePathItem)
        ,   guideItem(new GuidePathItem)
    {
        guideItem->setParentItem(curveItem);
    }

    ~Curve()
    {
        delete guideItem;
        delete curveItem;
    }

    const CurvePoints &points() const
    {
        return pts;
    }

    void setPoints(const CurvePoints &pts)
    {
        this->pts = pts;
        update();
    }

    virtual void update()
    {
        if (pts.count() < 2) {
            curveItem->setPath(QPainterPath());
            guideItem->setPath(QPainterPath());
            return;
        }
        for (int i = 0;  i < pts.count();  ++i) {
            pts[i].x = qMax(qreal(0.0f), pts[i].x);
            pts[i].y = qMax(qreal(0.0f), pts[i].y);
        }
        qSort(pts);
        QPainterPath curvePath(pts[0]);
        QPainterPath guidePath;
        for (int i = 1;  i < pts.count();  ++i) {
            if ((CurvePoint::NoCurve == pts[i].curveType)
                    || i == pts.count() - 1)
                curvePath.lineTo(pts[i]);
            else {
                curvePath.quadTo(pts[i], pts[i + 1]);
                guidePath.moveTo(pts[i - 1]);
                guidePath.lineTo(pts[i]);
                guidePath.lineTo(pts[i + 1]);
                ++i;
            }

        }
        curveItem->setPath(curvePath);
        guideItem->setPath(guidePath);
    }

    QGraphicsItem *graphicsItem() const
    {
        return curveItem;
    }

    void highlight()
    {
        curveItem->highlight();
        guideItem->show();
    }

    void unhighlight()
    {
        guideItem->hide();
        curveItem->unhighlight();
    }
};

class PitchCurve : public Curve
{
public:
    void update()
    {
        for (int i = 0;  i < pts.count();  ++i)
            pts[i].y = qMin(pts[i].y, qreal(127.0f));
        Curve::update();
    }
};

class VolumeCurve : public Curve
{
public:
    void update()
    {
        for (int i = 0;  i < pts.count();  ++i)
            pts[i].y = qMin(pts[i].y, qreal(1.0f));
        Curve::update();
    }
};

class Item
{
public:
    virtual ~Item()
    {}

    virtual QGraphicsItem *graphicsItem(SceneType type) const = 0;

    virtual void highlight() {}
    virtual void unhighlight() {}
};

class Note : public Item
{
public:
    PitchCurve *pitchCurve;
    VolumeCurve *volumeCurve;

    Note()
        :   pitchCurve(new PitchCurve)
        ,   volumeCurve(new VolumeCurve)
    {
        QGraphicsItem *pitchCurveItem = pitchCurve->graphicsItem();
        pitchCurveItem->setData(0, quintptr(this));
        foreach (QGraphicsItem *child, pitchCurveItem->children())
            child->setData(0, quintptr(this));
        QGraphicsItem *volumeCurveItem = volumeCurve->graphicsItem();
        volumeCurveItem->setData(0, quintptr(this));
        foreach (QGraphicsItem *child, volumeCurveItem->children())
            child->setData(0, quintptr(this));
    }

    ~Note()
    {
        delete volumeCurve;
        delete pitchCurve;
    }

    QGraphicsItem *graphicsItem(SceneType type) const
    {
        switch (type) {
        case Pitch:
            return pitchCurve->graphicsItem();
        case Volume:
            return volumeCurve->graphicsItem();
        default:
            return 0;
        }
    }

    void highlight()
    {
        pitchCurve->highlight();
        volumeCurve->highlight();
    }

    void unhighlight()
    {
        volumeCurve->unhighlight();
        pitchCurve->unhighlight();
    }

    static bool lessThan(const Note *a, const Note *b)
    {
        const CurvePoints &ptsA = a->pitchCurve->points();
        const CurvePoints &ptsB = b->pitchCurve->points();
        if (ptsB.isEmpty())
            return true;
        if (ptsA.isEmpty())
            return false;
        return ptsA[0] < ptsB[0];
    }
};

class Track : public Item
{
    QList<Note*> notes;
    QList<GraphicsItem*> items;

public:
    Track()
    {
        for (int i = 0;  i < SceneTypeCount;  ++i)
            items.append(new GraphicsItem);
    }

    ~Track()
    {
        qDeleteAll(notes);
        qDeleteAll(items);
    }

    QGraphicsItem *graphicsItem(SceneType type) const
    {
        return items[type];
    }

    void addNote(Note *note)
    {
        notes.append(note);
        note->graphicsItem(Pitch)->setParentItem(items[Pitch]);
        note->graphicsItem(Volume)->setParentItem(items[Volume]);
        qSort(notes.begin(), notes.end(), Note::lessThan);
    }

    void removeNote(Note *note)
    {
        notes.removeOne(note);
        note->graphicsItem(Pitch)->setParentItem(0);
        note->graphicsItem(Volume)->setParentItem(0);
    }
};

class Score : public Item
{
    QList<Track*> tracks;
    QList<GraphicsRootItem*> items;

public:
    Score()
    {
        for (int i = 0;  i < SceneTypeCount;  ++i)
            items.append(new GraphicsRootItem);
    }

    ~Score()
    {
        qDeleteAll(tracks);
        qDeleteAll(items);
    }

    QGraphicsItem *graphicsItem(SceneType type) const
    {
        return items[type];
    }

    void addTrack(Track *track)
    {
        tracks.append(track);
        for (int i = 0;  i < SceneTypeCount;  ++i)
            track->graphicsItem(SceneType(i))->setParentItem(items[i]);
    }

    void removeTrack(Track *track)
    {
        tracks.removeOne(track);
        for (int i = 0;  i < SceneTypeCount;  ++i)
            track->graphicsItem(SceneType(i))->setParentItem(0);
    }
};

#endif // AC_ITEM_H
