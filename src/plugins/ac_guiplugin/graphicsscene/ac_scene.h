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

#ifndef AC_SCENE_H
#define AC_SCENE_H

#include <ac_model.h>

#include <ac_guienums.h>

#include <QGraphicsItem>
#include <QGraphicsScene>

#include <QObject>

class GraphicsItem : public QGraphicsItem
{
public:
    QRectF boundingRect() const
    {
        static QRectF r;
        return r;
    }

    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) {}
};

class GraphicsRootItem : public GraphicsItem
{
public:
    GraphicsRootItem()
    {
        setTransform(QTransform::fromScale(1.0f, -1.0f));
    }
};

class GraphicsGripItem : public QGraphicsRectItem
{
public:
    enum { Type = QGraphicsItem::UserType + 1 };

    GraphicsGripItem()
    {
        setFlag(QGraphicsItem::ItemIgnoresTransformations);
        setPen(QPen(Qt::blue));
        setBrush(QBrush(Qt::blue));
        setRect(-3.0f, -3.0f, 6.0f, 6.0f);
        setZValue(1.0f);
    }

    virtual int type() const { return Type; }
};

class GraphicsPointItem : public GraphicsItem
{
public:
    GraphicsPointItem()
        :   _gripItem(new GraphicsGripItem)
    {
        _gripItem->setParentItem(this);
        _gripItem->hide();
    }

    void highlight()
    {
        _gripItem->show();
    }

    void unhighlight()
    {
        _gripItem->hide();
    }

private:
    GraphicsGripItem *_gripItem;
};

class GraphicsCurvePointItem : public GraphicsPointItem
{
public:
    CurveType curveType() const
    {
        return BezierCurve;
    }
};

typedef QList<GraphicsCurvePointItem*> GraphicsCurvePointItems;

class GraphicsPathItem : public QGraphicsPathItem
{
public:
    GraphicsPathItem()
    {
        setBoundingRegionGranularity(1.0f);
    }

    QPainterPath shape() const { return path(); }
};

class GraphicsGuideItem : public GraphicsPathItem
{
public:
    GraphicsGuideItem()
    {
        setFlag(QGraphicsItem::ItemStacksBehindParent);
        setPen(QPen(QBrush(Qt::lightGray), 0.0f, Qt::DotLine));
        hide();
    }
};

class GraphicsCurveItem : public GraphicsPathItem
{
public:
    GraphicsCurveItem()
        :   _guideItem(new GraphicsGuideItem)
    {
        _guideItem->setParentItem(this);
        unhighlight();
    }

    ~GraphicsCurveItem()
    {
        delete _guideItem;
    }

    const GraphicsCurvePointItems &points() const
    {
        return _points;
    }

    void appendPoint(GraphicsCurvePointItem *point)
    {
        if (_points.contains(point))
            return;
        _points.append(point);
        point->setParentItem(this);
    }

    void removePoint(GraphicsCurvePointItem *point)
    {
        point->setParentItem(0);
        _points.removeOne(point);
    }

    virtual void update()
    {
        if (_points.count() < 2) {
            setPath(QPainterPath());
            _guideItem->setPath(QPainterPath());
            return;
        }
        QPainterPath curvePath(_points[0]->pos());
        QPainterPath guidePath;
        for (int i = 1;  i < _points.count();  ++i) {
            if ((NoCurve == _points[i]->curveType())
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
        setPath(curvePath);
        _guideItem->setPath(guidePath);
    }

    void highlight()
    {
        setPen(QPen(QBrush(Qt::red), 4.0f));
        foreach (GraphicsPointItem *pt, _points)
            pt->highlight();
        _guideItem->show();
    }

    void unhighlight()
    {
        _guideItem->hide();
        foreach (GraphicsPointItem *pt, _points)
            pt->unhighlight();
        setPen(QPen(QBrush(Qt::red), 2.0f));
    }

private:
    GraphicsCurvePointItems _points;
    GraphicsGuideItem *_guideItem;
};

class GraphicsControlCurveItem : public GraphicsCurveItem
{
public:
    int controlType() const { return 0; }
};

typedef QList<GraphicsControlCurveItem*> GraphicsControlCurveItems;

class SceneItem
{
public:
    virtual ~SceneItem()
    {}

    virtual QGraphicsItem *item(SceneItemType type) const = 0;

    virtual void highlight() {}
    virtual void unhighlight() {}
};

class SceneNoteItem : public SceneItem
{
public:
    SceneNoteItem()
        :   _pitchCurve(new GraphicsCurveItem)
        ,   _controlCurveRoot(new GraphicsItem)
    {
        _pitchCurve->setData(0, quintptr(this));
        foreach (QGraphicsItem *child, _pitchCurve->children())
            child->setData(0, quintptr(this));
        _controlCurves.append(new GraphicsControlCurveItem);
        foreach (GraphicsControlCurveItem *controlCurve, _controlCurves) {
            controlCurve->setParentItem(_controlCurveRoot);
            controlCurve->setData(0, quintptr(this));
            foreach (QGraphicsItem *child, controlCurve->children())
                child->setData(0, quintptr(this));
        }
    }

    ~SceneNoteItem()
    {
        qDeleteAll(_controlCurves);
        delete _controlCurveRoot;
        delete _pitchCurve;
    }

    QGraphicsItem *item(SceneItemType type) const
    {
        switch (type) {
        case PitchSceneItem: return _pitchCurve;
        case ControlSceneItem: return _controlCurveRoot;
        default: return 0;
        }
    }

    void highlight()
    {
        _pitchCurve->highlight();
        foreach (GraphicsControlCurveItem *controlCurve, _controlCurves)
            controlCurve->highlight();
    }

    void unhighlight()
    {
        foreach (GraphicsControlCurveItem *controlCurve, _controlCurves)
            controlCurve->unhighlight();
        _pitchCurve->unhighlight();
    }

private:
    GraphicsCurveItem *_pitchCurve;
    GraphicsItem *_controlCurveRoot;
    GraphicsControlCurveItems _controlCurves;
};

class SceneTrackItem : public SceneItem
{
public:
    SceneTrackItem()
    {
        for (int i = 0;  i < SceneItemTypeCount;  ++i)
            _items.append(new GraphicsItem);
    }

    ~SceneTrackItem()
    {
        qDeleteAll(_notes);
        qDeleteAll(_items);
    }

    QGraphicsItem *item(SceneItemType type) const
    {
        return _items[type];
    }

    void appendNote(SceneNoteItem *note)
    {
        if (_notes.contains(note))
            return;
        _notes.append(note);
        note->item(PitchSceneItem)->setParentItem(_items[PitchSceneItem]);
        note->item(ControlSceneItem)->setParentItem(_items[ControlSceneItem]);
    }

    void removeNote(SceneNoteItem *note)
    {
        if (!_notes.contains(note))
            return;
        _notes.removeOne(note);
        note->item(PitchSceneItem)->setParentItem(0);
        note->item(ControlSceneItem)->setParentItem(0);
    }

private:
    QList<SceneNoteItem*> _notes;
    QList<GraphicsItem*> _items;
};

class SceneScoreItem : public SceneItem
{
public:
    SceneScoreItem()
    {
        for (int i = 0;  i < SceneItemTypeCount;  ++i)
            _items.append(new GraphicsRootItem);
    }

    ~SceneScoreItem()
    {
        qDeleteAll(_tracks);
        qDeleteAll(_items);
    }

    QGraphicsItem *item(SceneItemType type) const
    {
        return _items[type];
    }

    int trackCount() const
    {
        return _tracks.count();
    }

    SceneTrackItem *trackAt(int i)
    {
        return _tracks.at(i);
    }

    void appendTrack(SceneTrackItem *track)
    {
        insertTrack(_tracks.count(), track);
    }

    void insertTrack(int i, SceneTrackItem *track)
    {
        _tracks.insert(i, track);
        for (int i = 0;  i < SceneItemTypeCount;  ++i)
            track->item(SceneItemType(i))->setParentItem(_items[i]);
    }

    SceneTrackItem *takeTrack(int i)
    {
        SceneTrackItem *track = _tracks.at(i);
        removeTrack(track);
        return track;
    }

    void removeTrack(SceneTrackItem *track)
    {
        _tracks.removeOne(track);
        for (int i = 0;  i < SceneItemTypeCount;  ++i)
            track->item(SceneItemType(i))->setParentItem(0);
    }

private:
    QList<SceneTrackItem*> _tracks;
    QList<GraphicsRootItem*> _items;
};

class HScene : public QGraphicsScene
{
public:
    HScene(QObject *parent = 0)
        :   QGraphicsScene(parent)
    {
        setWidth(0.0f);
    }

    void setWidth(qreal w)
    {
        if (w < 0.0f)
            w = 0.0f;
        if (width() == w)
            return;
        setSceneRect(0.0f, 0.0f, w, height());
    }

    virtual qreal height() const = 0;
};

class PitchScene : public HScene
{
    Q_OBJECT

public:
    PitchScene(QObject *parent = 0)
        :   HScene(parent)
    {}

    qreal height() const { return 127.0f; }
};

class ControlScene : public HScene
{
    Q_OBJECT

public:
    ControlScene(QObject *parent = 0)
        :   HScene(parent)
    {}

    qreal height() const { return 1.0f; }
};

class TimeLabelScene : public HScene
{
    Q_OBJECT

public:
    TimeLabelScene(QObject *parent = 0)
        :   HScene(parent)
    {}

    qreal height() const { return 10.0f; }
};

class PitchLabelScene : public QGraphicsScene
{
    Q_OBJECT

public:
    PitchLabelScene(QObject *parent = 0)
        :   QGraphicsScene(parent)
    {
        setSceneRect(0.0f, 0.0f, 10.0f, 127.0f);
    }
};

class ControlLabelScene : public QGraphicsScene
{
    Q_OBJECT

public:
    ControlLabelScene(QObject *parent = 0)
        :   QGraphicsScene(parent)
    {
        setSceneRect(0.0f, 0.0f, 10.0f, 1.0f);
    }
};

class SceneManager : public QObject
{
    Q_OBJECT

public:
    SceneManager(QObject *parent = 0)
        :   QObject(parent)
        ,   _pitchScene(new PitchScene(this))
        ,   _controlScene(new ControlScene(this))
        ,   _timeLabelScene(new TimeLabelScene(this))
        ,   _pitchLabelScene(new PitchLabelScene(this))
        ,   _controlLabelScene(new ControlLabelScene(this))
    {}

    ~SceneManager() {}

    void setModel(AbstractItemModel *model)
    {
        if (_model == model)
            return;
        _model->disconnect(this);
        _model = model;
        connect(_model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), SLOT(dataChanged(QModelIndex,QModelIndex)));
        connect(_model, SIGNAL(rowsInserted(QModelIndex,int,int)), SLOT(rowsInserted(QModelIndex,int,int)));
        connect(_model, SIGNAL(rowsRemoved(QModelIndex,int,int)), SLOT(rowsRemoved(QModelIndex,int,int)));
    }

public slots:
    void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight)
    {}

    void rowsInserted(const QModelIndex &parent, int start, int end)
    {}

    void rowsRemoved(const QModelIndex &parent, int start, int end)
    {}

private:
    AbstractItemModel *_model;
    PitchScene *_pitchScene;
    ControlScene *_controlScene;
    TimeLabelScene *_timeLabelScene;
    PitchLabelScene *_pitchLabelScene;
    ControlLabelScene *_controlLabelScene;
};

#endif // AC_SCENE_H
