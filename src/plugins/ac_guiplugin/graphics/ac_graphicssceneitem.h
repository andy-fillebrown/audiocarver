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

#ifndef AC_GRAPHICSSCENEITEM_H
#define AC_GRAPHICSSCENEITEM_H

#include <ac_graphicsitem.h>
#include <ac_guienums.h>

#include <QGraphicsItem>

#include <QAbstractItemModel>

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
        _pitchCurve->setPoints(index.model()->data(index, PointsRole).value<PointList>());
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

#endif // AC_GRAPHICSSCENEITEM_H
