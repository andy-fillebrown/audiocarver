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

class Item : public QGraphicsItem
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

class RootItem : public Item
{
public:
    RootItem()
    {
        setTransform(QTransform::fromScale(1.0f, -1.0f));
    }
};

class PointItem;

class GripItem : public QGraphicsRectItem
{
    PointItem *pt;

public:
    enum {
        Type = QGraphicsItem::UserType + 1
    };

    GripItem(PointItem *point)
        :   pt(point)
    {
        setFlag(QGraphicsItem::ItemIgnoresTransformations);
        setPen(QPen(Qt::blue));
        setBrush(QBrush(Qt::blue));
        setRect(-3.0f, -3.0f, 6.0f, 6.0f);
        setZValue(1.0f);
    }

    virtual int type() const
    {
        return Type;
    }

    PointItem *point() const
    {
        return pt;
    }
};

class PathItem : public QGraphicsPathItem
{
public:
    PathItem()
    {
        setBoundingRegionGranularity(1.0f);
    }

    QPainterPath shape() const
    {
        return path();
    }
};

class CurveItem : public PathItem
{
public:
    CurveItem()
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

class GuideItem : public PathItem
{
public:
    GuideItem()
    {
        setFlag(QGraphicsItem::ItemStacksBehindParent);
        setPen(QPen(QBrush(Qt::lightGray), 0.0f, Qt::DotLine));
        hide();
    }
};

class Curve;

class PointItem : public Item
{
public:
    enum CurveType {
        NoCurve,
        BezierCurve
    };

    enum StretchType {
        Attack,
        Sustain,
        Release
    };

    PointItem(Curve *curve = 0,
              qreal x = 0.0f,
              qreal y = 0.0f,
              CurveType curveType = NoCurve,
              StretchType stretchType = Sustain
              )
        :   _curve(curve)
        ,   _gripItem(new GripItem(this))
        ,   _curveType(curveType)
        ,   _stretchType(stretchType)
    {
        setPos(x, y);
        _gripItem->setParentItem(this);
        _gripItem->hide();
    }

    Curve *curve() const
    {
        return _curve;
    }

    void setCurve(Curve *curve)
    {
        _curve = curve;
    }

    CurveType curveType() const
    {
        return _curveType;
    }

    void setCurveType(CurveType type)
    {
        _curveType = type;
    }

    StretchType stretchType() const
    {
        return _stretchType;
    }

    void setStretchType(StretchType type)
    {
        _stretchType = type;
    }

    void highlight()
    {
        _gripItem->show();
    }

    void unhighlight()
    {
        _gripItem->hide();
    }

    static bool lessThan(const PointItem *a, const PointItem *b)
    {
        return a->x() == b->x() ? a->y() < b->y() : a->x() < b->x();
    }

private:
    Curve *_curve;
    GripItem *_gripItem;
    CurveType _curveType;
    StretchType _stretchType;
};

typedef QList<PointItem*> PointItems;

class Curve
{
public:
    Curve()
        :   _curveItem(new CurveItem)
        ,   _guideItem(new GuideItem)
    {
        _guideItem->setParentItem(_curveItem);
    }

    ~Curve()
    {
        delete _guideItem;
        delete _curveItem;
    }

    const PointItems &points() const
    {
        return _points;
    }

    void appendPoint(PointItem *point)
    {
        if (_points.contains(point))
            return;
        _points.append(point);
        point->setCurve(this);
        point->setParentItem(_curveItem);
    }

    void removePoint(PointItem *point)
    {
        point->setParentItem(0);
        point->setCurve(0);
        _points.removeOne(point);
    }

    virtual void update()
    {
        if (_points.count() < 2) {
            _curveItem->setPath(QPainterPath());
            _guideItem->setPath(QPainterPath());
            return;
        }
        qSort(_points.begin(), _points.end(), PointItem::lessThan);
        for (int i = 0;  i < _points.count();  ++i) {
            _points[i]->setX(qMax(qreal(0.0f), _points[i]->x()));
            _points[i]->setY(qMax(qreal(0.0f), _points[i]->y()));
        }
        _prevLength = length;
        QPainterPath curvePath(_points[0]->pos());
        QPainterPath guidePath;
        for (int i = 1;  i < _points.count();  ++i) {
            if ((PointItem::NoCurve == _points[i]->curveType())
                    || i == _points.count() - 1)
                curvePath.lineTo(_points[i]->pos());
            else {
                curvePath.quadTo(_points[i]->pos(), _points[i + 1]->pos());
                guidePath.moveTo(_points[i - 1]->pos());
                guidePath.lineTo(_points[i]->pos());
                guidePath.lineTo(_points[i + 1]->pos());
                ++i;
            }

        }
        _curveItem->setPath(curvePath);
        _guideItem->setPath(guidePath);
    }

    QGraphicsItem *item() const
    {
        return _curveItem;
    }

    void highlight()
    {
        foreach (PointItem *pt, _points)
            pt->highlight();
        _curveItem->highlight();
        _guideItem->show();
    }

    void unhighlight()
    {
        _guideItem->hide();
        _curveItem->unhighlight();
        foreach (PointItem *pt, _points)
            pt->unhighlight();
    }

protected:
    PointItems _points;

private:
    CurveItem *_curveItem;
    GuideItem *_guideItem;
};

class PitchCurve : public Curve
{
public:
    void update()
    {
        for (int i = 0;  i < _points.count();  ++i)
            _points[i]->setY(qMin(_points[i]->y(), qreal(127.0f)));
        Curve::update();
    }
};

class VolumeCurve : public Curve
{
public:
    void update()
    {
        for (int i = 0;  i < _points.count();  ++i)
            _points[i]->setY(qMin(_points[i]->y(), qreal(1.0f)));
        Curve::update();
    }
};

class Object
{
public:
    virtual ~Object()
    {}

    virtual QGraphicsItem *item(SceneType type) const = 0;
};

class Entity : public Object
{
public:
    virtual void highlight() = 0;
    virtual void unhighlight() = 0;
};

class Note : public Entity
{
public:
    Note()
        :   _pitchCurve(new PitchCurve)
        ,   _volumeCurve(new VolumeCurve)
    {
        QGraphicsItem *pitchItem = _pitchCurve->item();
        pitchItem->setData(0, quintptr(this));
        foreach (QGraphicsItem *child, pitchItem->children())
            child->setData(0, quintptr(this));
        QGraphicsItem *volumeItem = _volumeCurve->item();
        volumeItem->setData(0, quintptr(this));
        foreach (QGraphicsItem *child, volumeItem->children())
            child->setData(0, quintptr(this));
    }

    ~Note()
    {
        delete _volumeCurve;
        delete _pitchCurve;
    }

    Curve *pitchCurve() const
    {
        return _pitchCurve;
    }

    Curve *volumeCurve() const
    {
        return _volumeCurve;
    }

    QGraphicsItem *item(SceneType type) const
    {
        switch (type) {
        case Pitch:
            return _pitchCurve->item();
        case Volume:
            return _volumeCurve->item();
        default:
            return 0;
        }
    }

    void highlight()
    {
        _pitchCurve->highlight();
        _volumeCurve->highlight();
    }

    void unhighlight()
    {
        _volumeCurve->unhighlight();
        _pitchCurve->unhighlight();
    }

    static bool lessThan(const Note *a, const Note *b)
    {
        const PointItems &ptsA = a->_pitchCurve->points();
        const PointItems &ptsB = b->_pitchCurve->points();
        if (ptsB.isEmpty())
            return true;
        if (ptsA.isEmpty())
            return false;
        return PointItem::lessThan(ptsA.first(), ptsB.first());
    }

private:
    PitchCurve *_pitchCurve;
    VolumeCurve *_volumeCurve;
};

class Track : public Object
{
public:
    Track()
    {
        for (int i = 0;  i < SceneTypeCount;  ++i)
            _items.append(new Item);
    }

    ~Track()
    {
        qDeleteAll(_notes);
        qDeleteAll(_items);
    }

    QGraphicsItem *item(SceneType type) const
    {
        return _items[type];
    }

    void appendNote(Note *note)
    {
        if (_notes.contains(note))
            return;
        _notes.append(note);
        note->item(Pitch)->setParentItem(_items[Pitch]);
        note->item(Volume)->setParentItem(_items[Volume]);
    }

    void removeNote(Note *note)
    {
        if (!_notes.contains(note))
            return;
        _notes.removeOne(note);
        note->item(Pitch)->setParentItem(0);
        note->item(Volume)->setParentItem(0);
    }

    void sortNotes()
    {
        qSort(_notes.begin(), _notes.end(), Note::lessThan);
    }

private:
    QList<Note*> _notes;
    QList<Item*> _items;
};

class Score : public Object
{
public:
    Score()
    {
        for (int i = 0;  i < SceneTypeCount;  ++i)
            _items.append(new RootItem);
    }

    ~Score()
    {
        qDeleteAll(_tracks);
        qDeleteAll(_items);
    }

    QGraphicsItem *item(SceneType type) const
    {
        return _items[type];
    }

    int trackCount() const
    {
        return _tracks.count();
    }

    Track *trackAt(int i)
    {
        return _tracks.at(i);
    }

    void appendTrack(Track *track)
    {
        insertTrack(_tracks.count(), track);
    }

    void insertTrack(int i, Track *track)
    {
        _tracks.insert(i, track);
        for (int i = 0;  i < SceneTypeCount;  ++i)
            track->item(SceneType(i))->setParentItem(_items[i]);
    }

    Track *takeTrack(int i)
    {
        Track *track = _tracks.at(i);
        removeTrack(track);
        return track;
    }

    void removeTrack(Track *track)
    {
        _tracks.removeOne(track);
        for (int i = 0;  i < SceneTypeCount;  ++i)
            track->item(SceneType(i))->setParentItem(0);
    }

private:
    QList<Track*> _tracks;
    QList<RootItem*> _items;
};

#endif // AC_ITEM_H
