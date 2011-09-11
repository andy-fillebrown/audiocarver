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

class SceneItemList;

class SceneItem
{
public:
    virtual ~SceneItem() {}

    virtual int listCount() const { return 0; }
    virtual SceneItemList *listAt(int i) { Q_UNUSED(i);  return 0; }

    virtual QGraphicsItem *item(SceneItemType type) const = 0;

    virtual void highlight() {}
    virtual void unhighlight() {}

    virtual void dataChanged(const QModelIndex &index) {}
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

    int count() const
    {
        return _sceneItems.count();
    }

    SceneItem *at(int i) const
    {
        return _sceneItems.at(i);
    }

    void append(SceneItem *sceneItem)
    {
        insert(_sceneItems.count(), sceneItem);
    }

    void insert(int i, SceneItem *sceneItem)
    {
        if (!sceneItem || !_parent || _sceneItems.contains(sceneItem))
            return;
        _sceneItems.insert(i, sceneItem);
        for (int i = 0;  i < SceneItemTypeCount;  ++i) {
            SceneItemType type = SceneItemType(i);
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
        for (int i = 0;  i < SceneItemTypeCount;  ++i) {
            QGraphicsItem *item = sceneItem->item(SceneItemType(i));
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
        for (int i = 0;  i < SceneItemTypeCount;  ++i)
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
        if (i == 0)
            return notes;
        return 0;
    }

    QGraphicsItem *item(SceneItemType type) const
    {
        return _items[type];
    }

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
        for (int i = 0;  i < SceneItemTypeCount;  ++i)
            _items.append(new GraphicsRootItem);
    }

    ~SceneScoreItem()
    {
        qDeleteAll(_items);
    }

    int listCount() const { return 1; }
    SceneItemList *listAt(int i)
    {
        if (i == 0)
            return tracks;
        return 0;
    }

    QGraphicsItem *item(SceneItemType type) const
    {
        return _items[type];
    }

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
        _score = new SceneScoreItem;
        pitchScene->addItem(_score->item(PitchSceneItem));
        controlScene->addItem(_score->item(ControlSceneItem));
        timeLabelScene->addItem(_score->item(TimeLabelSceneItem));
        pitchLabelScene->addItem(_score->item(PitchLabelSceneItem));
        controlLabelScene->addItem(_score->item(ControlLabelSceneItem));
        _itemHash.clear();
        _itemHash.insert(QModelIndex(), _score);
        _listHash.clear();
        addList(_model->index(0, 0), _score->listAt(0));
    }

public slots:
    void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight)
    {
        if (!_model)
            return;
        ItemType type = ItemType(_model->data(topLeft, ItemTypeRole).toInt());
        if (type != ListItem) {
            SceneItem *item = _itemHash.find(topLeft).value();
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
            QModelIndex index = _model->index(start, 0, parent);
            _itemHash.insert(index, item);
            SceneItemList *list = _listHash.value(parent);
            list->append(item);
            for (int i = 0;  i < item->listCount();  ++i)
                addList(_model->index(i, 0, index), item->listAt(i));
            item->dataChanged(index);
        }
    }

    void rowsRemoved(const QModelIndex &parent, int start, int end)
    {
        if (!_model)
            return;
        ItemType type = ItemType(_model->data(parent, ItemTypeRole).toInt());
        if (ListItem == type) {
            QModelIndex index = _model->index(start, 0, parent);
            _itemHash.remove(index);
            SceneItemList *list = _listHash.value(parent);
            SceneItem *item = _itemHash.value(index);
            list->remove(item);
            for (int i = 0;  i < item->listCount();  ++i)
                removeList(_model->index(i, 0, index), item->listAt(i));
        }
    }

private:
    inline void addList(const QModelIndex &listIndex, SceneItemList *list)
    {
        _listHash.insert(listIndex, list);
        for (int i = 0;  i < list->count();  ++i) {
            QModelIndex itemIndex = _model->index(i, 0, listIndex);
            SceneItem *item = list->at(i);
            for (int j = 0;  j < item->listCount();  ++j)
                addList(_model->index(j, 0, itemIndex), item->listAt(j));
        }
    }

    void removeList(const QModelIndex &listIndex, SceneItemList *list)
    {
        _listHash.remove(listIndex);
        for (int i = 0;  i < list->count();  ++i) {
            QModelIndex itemIndex = _model->index(i, 0, listIndex);
            SceneItem *item = list->at(i);
            for (int j = 0;  j < item->listCount();  ++j)
                removeList(_model->index(j, 0, itemIndex), item->listAt(j));
        }
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
    QHash<QPersistentModelIndex, SceneItemList*> _listHash;
    QHash<QPersistentModelIndex, SceneItem*> _itemHash;
};

#endif // AC_SCENE_H
