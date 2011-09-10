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

#include <QDebug>
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

class SceneItem
{
public:
    SceneItem(const QModelIndex &index)
        :   _index(index)
    {}

    virtual ~SceneItem()
    {}

    virtual QGraphicsItem *item(SceneItemType type) const = 0;

    virtual void highlight() {}
    virtual void unhighlight() {}

protected:
    QPersistentModelIndex _index;
};

class SceneNoteItem : public SceneItem
{
public:
    SceneNoteItem(const QModelIndex &index);
//        :   SceneItem(index)
//        ,   _pitchCurve(new GraphicsCurveItem)
//        ,   _velocityLine(new QGraphicsLineItem)
//    {
//        _pitchCurve->setData(0, quintptr(this));
//        PointList pts = _index.model()->data(_index, PointsRole).value<PointList>();
//        foreach (const Point &pt, pts) {
//            GraphicsCurvePointItem *ptItem = new GraphicsCurvePointItem;
//            ptItem->setPos(pt.pos);
//            _pitchCurve->appendPoint(ptItem);
//        }
//        _pitchCurve->update();
//        _velocityLine->setData(0, quintptr(this));
//    }

    ~SceneNoteItem()
    {
        delete _velocityLine;
        delete _pitchCurve;
    }

    QGraphicsItem *item(SceneItemType type) const
    {
        switch (type) {
        case PitchSceneItem: return _pitchCurve;
        case ControlSceneItem: return _velocityLine;
        default: return 0;
        }
    }

    void highlight()
    {
        _pitchCurve->highlight();
    }

    void unhighlight()
    {
        _pitchCurve->unhighlight();
    }

private:
    GraphicsCurveItem *_pitchCurve;
    QGraphicsLineItem *_velocityLine;
};

class SceneTrackItem : public SceneItem
{
public:
    SceneTrackItem(const QModelIndex &index)
        :   SceneItem(index)
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
    SceneScoreItem(const QModelIndex &index)
        :   SceneItem(index)
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
    {}

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
        ,   pitchScene(new PitchScene(this))
        ,   controlScene(new ControlScene(this))
        ,   timeLabelScene(new TimeLabelScene(this))
        ,   pitchLabelScene(new PitchLabelScene(this))
        ,   controlLabelScene(new ControlLabelScene(this))
        ,   _model(0)
        ,   _score(0)
    {
        pitchScene->setWidth(128.0f);
        controlScene->setWidth(128.0f);
        timeLabelScene->setWidth(128.0f);
    }

    ~SceneManager()
    {
        delete _score;
    }

    AbstractItemModel *model() const { return _model; }
    void setModel(AbstractItemModel *model)
    {
        if (_model == model)
            return;
        if (_model)
            _model->disconnect(this);
        _model = model;
        if (_model) {
            connect(_model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), SLOT(dataChanged(QModelIndex,QModelIndex)));
            connect(_model, SIGNAL(rowsInserted(QModelIndex,int,int)), SLOT(rowsInserted(QModelIndex,int,int)));
            connect(_model, SIGNAL(rowsRemoved(QModelIndex,int,int)), SLOT(rowsRemoved(QModelIndex,int,int)));
        }
        delete _score;
        _score = new SceneScoreItem(_model->index(0, 0));
        pitchScene->addItem(_score->item(PitchSceneItem));
        controlScene->addItem(_score->item(ControlSceneItem));
        timeLabelScene->addItem(_score->item(TimeLabelSceneItem));
        pitchLabelScene->addItem(_score->item(PitchLabelSceneItem));
        controlLabelScene->addItem(_score->item(ControlLabelSceneItem));
    }

public slots:
    void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight)
    {
    }

    void rowsInserted(const QModelIndex &parent, int start, int end)
    ;
//    {
//        if (!_model)
//            return;
//        ItemType type = ItemType(_model->data(parent, ItemTypeRole).toInt());
//        if (ListItem == type) {
//            ItemType listType = ItemType(_model->data(parent, ListTypeRole).toInt());
//            switch (listType) {
//            case TrackItem: {
//                SceneTrackItem *track = new SceneTrackItem(_model->index(start, 0, parent));
//                _score->insertTrack(start, track);
//                break;
//            }
//            case NoteItem: {
//                SceneTrackItem *track = _score->trackAt(_model->parent(parent).row());
//                SceneNoteItem *note = new SceneNoteItem(_model->index(start, 0, parent));
//                track->appendNote(note);
//                break;
//            }
//            default:
//                break;
//            }
//        }
//    }

    void rowsRemoved(const QModelIndex &parent, int start, int end)
    {

    }

public:
    PitchScene *pitchScene;
    ControlScene *controlScene;
    TimeLabelScene *timeLabelScene;
    PitchLabelScene *pitchLabelScene;
    ControlLabelScene *controlLabelScene;

private:
    AbstractItemModel *_model;
    SceneScoreItem *_score;
};

#endif // AC_SCENE_H
