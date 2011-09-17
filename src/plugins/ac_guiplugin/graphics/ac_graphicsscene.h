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

#ifndef AC_GRAPHICSSCENE_H
#define AC_GRAPHICSSCENE_H

#include <ac_graphicssceneitem.h>
#include <ac_guienums.h>

#include <QGraphicsScene>

#include <QAbstractItemModel>

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

    qreal height() const
    {
        return 127.0f;
    }
};

class ControlScene : public HScene
{
    Q_OBJECT

public:
    ControlScene(QObject *parent = 0)
        :   HScene(parent)
    {}

    qreal height() const
    {
        return 1.0f;
    }
};

class TimeLabelScene : public HScene
{
    Q_OBJECT

public:
    TimeLabelScene(QObject *parent = 0)
        :   HScene(parent)
    {}

    qreal height() const
    {
        return 10.0f;
    }
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
        ,   _timeLines(0)
        ,   _pitchLines(0)
        ,   _controlLines(0)
        ,   _pitchScene(new PitchScene(this))
        ,   _controlScene(new ControlScene(this))
        ,   _timeLabelScene(new TimeLabelScene(this))
        ,   _pitchLabelScene(new PitchLabelScene(this))
        ,   _controlLabelScene(new ControlLabelScene(this))
    {}

    ~SceneManager()
    {
        delete _controlLines;
        delete _pitchLines;
        delete _timeLines;
        delete _score;
    }

    QAbstractItemModel *model() const { return _model; }
    void setModel(QAbstractItemModel *model)
    {
//        if (_model == model)
//            return;
//        if (_model)
//            _model->disconnect(this);
//        _model = model;
//        if (_model) {
//            connect(_model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), SLOT(dataChanged(QModelIndex,QModelIndex)));
//            connect(_model, SIGNAL(rowsInserted(QModelIndex,int,int)), SLOT(rowsInserted(QModelIndex,int,int)));
//            connect(_model, SIGNAL(rowsRemoved(QModelIndex,int,int)), SLOT(rowsRemoved(QModelIndex,int,int)));
//        }
//        _reset();
    }

    QGraphicsScene *scene(Ac::SceneType type)
    {
        switch (type) {
        case Ac::PitchScene:
            return _pitchScene;
        case Ac::ControlScene:
            return _controlScene;
        case Ac::TimeLabelScene:
            return _timeLabelScene;
        case Ac::PitchLabelScene:
            return _pitchLabelScene;
        case Ac::ControlLabelScene:
            return _controlLabelScene;
        default:
            return 0;
        }
    }

public slots:
    void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight)
    {
//        if (!_model)
//            return;
//        ItemType type = ItemType(_model->data(topLeft, ItemTypeRole).toInt());
//        if (type != ListItem) {
//            SceneItem *item = _indexToItem.value(topLeft);
//            Q_ASSERT(item);
//            item->dataChanged(topLeft);
//        }
    }

    void rowsInserted(const QModelIndex &parent, int start, int end)
    {
//        if (!_model)
//            return;
//        ItemType type = ItemType(parent.data(ItemTypeRole).toInt());
//        if (ListItem == type) {
//            SceneItem *item = 0;
//            ItemType listType = ItemType(parent.data(ListTypeRole).toInt());
//            switch (listType) {
//            case TrackItem:
//                item = new SceneTrackItem;
//                break;
//            case NoteItem:
//                item = new SceneNoteItem;
//                break;
//            case TimeLineItem:
//                item = new SceneTimeLineItem;
//                break;
//            case PitchLineItem:
//                item = new ScenePitchLineItem;
//                break;
//            case ControlLineItem:
//                item = new SceneControlLineItem;
//                break;
//            default: break;
//            }
//            _addItem(_model->index(start, 0, parent), item, _indexToList.value(parent));
//        }
    }

    void rowsRemoved(const QModelIndex &parent, int start, int end)
    {
//        if (!_model)
//            return;
//        ItemType parentType = ItemType(parent.data(ItemTypeRole).toInt());
//        if (ListItem == parentType)
//            _removeItem(_model->index(start, 0, parent), _indexToList.value(parent));
    }

private:
    void _addItem(const QModelIndex &itemIndex, SceneItem *item, SceneItemList *list)
    {
        _indexToItem.insert(itemIndex, item);
        _itemToIndex.insert(item, itemIndex);
        for (int i = 0;  i < item->listCount();  ++i)
            _addList(_model->index(i, 0, itemIndex), item->listAt(i));
        list->append(item);
        item->dataChanged(itemIndex);
    }

    void _removeItem(const QModelIndex &itemIndex, SceneItemList *list)
    {
        SceneItem *item = _indexToItem.value(itemIndex);
        _indexToItem.remove(itemIndex);
        _itemToIndex.remove(item);
        for (int i = 0;  i < item->listCount();  ++i)
            _removeList(_model->index(i, 0, itemIndex));
        list->remove(item);
    }

    void _addList(const QModelIndex &listIndex, SceneItemList *list)
    {
        _indexToList.insert(listIndex, list);
        _listToIndex.insert(list, listIndex);
        for (int i = 0;  i < list->count();  ++i) {
            QModelIndex itemIndex = _model->index(i, 0, listIndex);
            SceneItem *item = list->at(i);
            for (int j = 0;  j < item->listCount();  ++j)
                _addList(_model->index(j, 0, itemIndex), item->listAt(j));
        }
    }

    void _removeList(const QModelIndex &listIndex)
    {
        SceneItemList *list = _indexToList.value(listIndex);
        _indexToList.remove(listIndex);
        _listToIndex.remove(list);
        for (int i = 0;  i < list->count();  ++i) {
            QModelIndex itemIndex = _model->index(i, 0, listIndex);
            SceneItem *item = list->at(i);
            for (int j = 0;  j < item->listCount();  ++j)
                _removeList(_model->index(j, 0, itemIndex));
        }
    }

    void _reset()
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
            _addList(_model->index(i, 0), _score->listAt(i));
        delete _timeLines;
        delete _pitchLines;
        delete _controlLines;
        _timeLines = new SceneItemList(_score);
        _pitchLines = new SceneItemList(_score);
        _controlLines = new SceneItemList(_score);
        QModelIndex gridSettingsIndex = _model->index(1, 0);
        _addList(_model->index(0, 0, gridSettingsIndex), _timeLines);
        _addList(_model->index(1, 0, gridSettingsIndex), _pitchLines);
        _addList(_model->index(2, 0, gridSettingsIndex), _controlLines);
    }

private:
    QAbstractItemModel *_model;
    SceneScoreItem *_score;
    SceneItemList *_timeLines;
    SceneItemList *_pitchLines;
    SceneItemList *_controlLines;
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

#endif // AC_GRAPHICSSCENE_H
