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

#include <ac_coreenums.h>
#include <ac_model.h>
#include <ac_point.h>

#include <ac_guienums.h>

#include <QGraphicsItem>
#include <QGraphicsScene>

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

    const GraphicsCurvePointItems &points() const { return _points; }

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

class SceneItemList;

class SceneItem
{
public:
    virtual ~SceneItem() {}

    virtual int listCount() const { return 0; }
    virtual SceneItemList *listAt(int i) { Q_UNUSED(i);  return 0; }

    virtual QGraphicsItem *item(Ac::SceneType type) const = 0;

    virtual void highlight() {}
    virtual void unhighlight() {}

    virtual void dataChanged(const QModelIndex &index) { Q_UNUSED(index); }
};

class SceneItemList
{
public:
    SceneItemList(SceneItem *parent)
        :   _parent(parent)
    {}

    ~SceneItemList()
    {
        qDeleteAll(_sceneItems);
    }

    int count() const { return _sceneItems.count(); }
    SceneItem *at(int i) const { return _sceneItems.at(i); }

    void append(SceneItem *sceneItem)
    {
        insert(_sceneItems.count(), sceneItem);
    }

    void insert(int i, SceneItem *sceneItem)
    {
        if (!sceneItem || !_parent || _sceneItems.contains(sceneItem))
            return;
        _sceneItems.insert(i, sceneItem);
        for (int i = 0;  i < Ac::SceneTypeCount;  ++i) {
            Ac::SceneType type = Ac::SceneType(i);
            QGraphicsItem *parentItem = _parent->item(type);
            QGraphicsItem *item = sceneItem->item(type);
            if (parentItem && item)
                item->setParentItem(parentItem);
        }
    }

    void remove(int i)
    {
        remove(_sceneItems.at(i));
    }

    void remove(SceneItem *sceneItem)
    {
        if (!sceneItem || !_sceneItems.contains(sceneItem))
            return;
        _sceneItems.removeOne(sceneItem);
        for (int i = 0;  i < Ac::SceneTypeCount;  ++i) {
            QGraphicsItem *item = sceneItem->item(Ac::SceneType(i));
            if (item)
                item->setParentItem(0);
        }
    }

private:
    SceneItem *_parent;
    QList<SceneItem*> _sceneItems;
};

class SceneNoteItem : public SceneItem
{
public:
    SceneNoteItem()
        :   _pitchCurve(new GraphicsCurveItem)
        ,   _velocityLine(new QGraphicsLineItem)
    {
        _pitchCurve->setData(0, quintptr(this));
        _velocityLine->setData(0, quintptr(this));
    }

    ~SceneNoteItem()
    {
        delete _velocityLine;
        delete _pitchCurve;
    }

    QGraphicsItem *item(Ac::SceneType type) const
    {
        switch (type) {
        case Ac::PitchScene: return _pitchCurve;
        case Ac::ControlScene: return _velocityLine;
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

    void dataChanged(const QModelIndex &index)
    {
        PointList pts = index.model()->data(index, PointsRole).value<PointList>();
        foreach (const Point &pt, pts) {
            GraphicsCurvePointItem *ptItem = new GraphicsCurvePointItem;
            ptItem->setPos(pt.pos);
            _pitchCurve->appendPoint(ptItem);
        }
        _pitchCurve->update();
    }

private:
    GraphicsCurveItem *_pitchCurve;
    QGraphicsLineItem *_velocityLine;
};

class SceneTrackItem : public SceneItem
{
public:
    SceneTrackItem()
        :   notes(new SceneItemList(this))
    {
        for (int i = 0;  i < Ac::SceneTypeCount;  ++i)
            _items.append(new GraphicsItem);
    }

    ~SceneTrackItem()
    {
        delete notes;
        qDeleteAll(_items);
    }

    int listCount() const { return 1; }

    SceneItemList *listAt(int i)
    {
        if (i == 0) return notes;
        return 0;
    }

    QGraphicsItem *item(Ac::SceneType type) const { return _items[type]; }

public:
    SceneItemList *notes;

private:
    QList<GraphicsItem*> _items;
};

class SceneScoreItem : public SceneItem
{
public:
    SceneScoreItem()
        :   tracks(new SceneItemList(this))
    {
        for (int i = 0;  i < Ac::SceneTypeCount;  ++i)
            _items.append(new GraphicsRootItem);
    }

    ~SceneScoreItem()
    {
        qDeleteAll(_items);
    }

    int listCount() const { return 1; }

    SceneItemList *listAt(int i)
    {
        if (i == 0) return tracks;
        return 0;
    }

    QGraphicsItem *item(Ac::SceneType type) const { return _items[type]; }

public:
    SceneItemList *tracks;

private:
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
        ,   _model(0)
        ,   _score(0)
        ,   _pitchScene(new PitchScene(this))
        ,   _controlScene(new ControlScene(this))
        ,   _timeLabelScene(new TimeLabelScene(this))
        ,   _pitchLabelScene(new PitchLabelScene(this))
        ,   _controlLabelScene(new ControlLabelScene(this))
    {}

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
        reset();
    }

    QGraphicsScene *scene(Ac::SceneType type)
    {
        switch (type) {
        case Ac::PitchScene: return _pitchScene;
        case Ac::ControlScene: return _controlScene;
        case Ac::TimeLabelScene: return _timeLabelScene;
        case Ac::PitchLabelScene: return _pitchLabelScene;
        case Ac::ControlLabelScene: return _controlLabelScene;
        default: return 0;
        }
    }

public slots:
    void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight)
    {
        if (!_model)
            return;
        ItemType type = ItemType(_model->data(topLeft, ItemTypeRole).toInt());
        if (type != ListItem) {
            SceneItem *item = _indexToItem.value(topLeft);
            Q_ASSERT(item);
            item->dataChanged(topLeft);
        }
    }

    void rowsInserted(const QModelIndex &parent, int start, int end)
    {
        if (!_model)
            return;
        ItemType type = ItemType(_model->data(parent, ItemTypeRole).toInt());
        if (ListItem == type) {
            SceneItem *item = 0;
            ItemType listType = ItemType(_model->data(parent, ListTypeRole).toInt());
            switch (listType) {
            case TrackItem: item = new SceneTrackItem;  break;
            case NoteItem: item = new SceneNoteItem;  break;
            default: break;
            }
            addItem(_model->index(start, 0, parent), item, _indexToList.value(parent));
        }
    }

    void rowsRemoved(const QModelIndex &parent, int start, int end)
    {
        if (!_model)
            return;
        ItemType parentType = ItemType(_model->data(parent, ItemTypeRole).toInt());
        if (ListItem == parentType) {
            QModelIndex index = _model->index(start, 0, parent);
            removeItem(_model->index(start, 0, parent), _indexToList.value(parent));
        }
    }

private:
    void addItem(const QModelIndex &itemIndex, SceneItem *item, SceneItemList *list)
    {
        _indexToItem.insert(itemIndex, item);
        _itemToIndex.insert(item, itemIndex);
        for (int i = 0;  i < item->listCount();  ++i)
            addList(_model->index(i, 0, itemIndex), item->listAt(i));
        list->append(item);
        item->dataChanged(itemIndex);
    }

    void removeItem(const QModelIndex &itemIndex, SceneItemList *list)
    {
        SceneItem *item = _indexToItem.value(itemIndex);
        _indexToItem.remove(itemIndex);
        _itemToIndex.remove(item);
        for (int i = 0;  i < item->listCount();  ++i)
            removeList(_model->index(i, 0, itemIndex));
        list->remove(item);
    }

    void addList(const QModelIndex &listIndex, SceneItemList *list)
    {
        _indexToList.insert(listIndex, list);
        _listToIndex.insert(list, listIndex);
        for (int i = 0;  i < list->count();  ++i) {
            QModelIndex itemIndex = _model->index(i, 0, listIndex);
            SceneItem *item = list->at(i);
            for (int j = 0;  j < item->listCount();  ++j)
                addList(_model->index(j, 0, itemIndex), item->listAt(j));
        }
    }

    void removeList(const QModelIndex &listIndex)
    {
        SceneItemList *list = _indexToList.value(listIndex);
        _indexToList.remove(listIndex);
        _listToIndex.remove(list);
        for (int i = 0;  i < list->count();  ++i) {
            QModelIndex itemIndex = _model->index(i, 0, listIndex);
            SceneItem *item = list->at(i);
            for (int j = 0;  j < item->listCount();  ++j)
                removeList(_model->index(j, 0, itemIndex));
        }
    }

    void reset()
    {
        delete _score;
        _score = new SceneScoreItem;
        for (int i = 0;  i < Ac::SceneTypeCount;  ++i) {
            Ac::SceneType type = Ac::SceneType(i);
            scene(type)->addItem(_score->item(type));
        }
        _indexToItem.clear();
        _itemToIndex.clear();
        _indexToList.clear();
        _listToIndex.clear();
        _indexToItem.insert(QModelIndex(), _score);
        _itemToIndex.insert(_score, QModelIndex());
        for (int i = 0;  i < _score->listCount();  ++i)
            addList(_model->index(i, 0), _score->listAt(i));
    }

private:
    AbstractItemModel *_model;
    SceneScoreItem *_score;
    QHash<QPersistentModelIndex, SceneItem*> _indexToItem;
    QHash<SceneItem*, QPersistentModelIndex> _itemToIndex;
    QHash<QPersistentModelIndex, SceneItemList*> _indexToList;
    QHash<SceneItemList*, QPersistentModelIndex> _listToIndex;
    PitchScene *_pitchScene;
    ControlScene *_controlScene;
    TimeLabelScene *_timeLabelScene;
    PitchLabelScene *_pitchLabelScene;
    ControlLabelScene *_controlLabelScene;
};

#endif // AC_SCENE_H
