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

    virtual int listCount() const
    {
        return 0;
    }

    virtual SceneItemList *listAt(int i)
    {
        Q_UNUSED(i);
        return 0;
    }

    virtual QGraphicsItem *item(Ac::SceneType type) const
    {
        Q_UNUSED(type);
        return 0;
    }

    virtual QGraphicsItem *unitItem(Ac::SceneType type, Ac::Axis axis) const
    {
        Q_UNUSED(type);
        Q_UNUSED(axis);
        return 0;
    }

    virtual void highlight() {}
    virtual void unhighlight() {}

    virtual void dataChanged(const QModelIndex &index)
    {
        Q_UNUSED(index);
    }
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
        for (int i = 0;  i < Ac::SceneTypeCount;  ++i) {
            Ac::SceneType type = Ac::SceneType(i);
            QGraphicsItem *parentItem = _parent->item(type);
            QGraphicsItem *item = sceneItem->item(type);
            if (parentItem && item)
                item->setParentItem(parentItem);
            parentItem = _parent->unitItem(type, Ac::XAxis);
            item = sceneItem->unitItem(type, Ac::XAxis);
            if (parentItem && item)
                item->setParentItem(parentItem);
            parentItem = _parent->unitItem(type, Ac::YAxis);
            item = sceneItem->unitItem(type, Ac::YAxis);
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
        case Ac::PitchScene:
            return _pitchCurve;
        case Ac::ControlScene:
            return _velocityLine;
        default:
            return 0;
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
        _pitchCurve->setPoints(index.data(PointsRole).value<PointList>());
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

    int listCount() const
    {
        return 1;
    }

    SceneItemList *listAt(int i)
    {
        if (i == 0)
            return notes;
        return 0;
    }

    QGraphicsItem *item(Ac::SceneType type) const
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
        ,   _pitchUnitItemX(new GraphicsItem)
        ,   _pitchUnitItemY(new GraphicsItem)
        ,   _controlUnitItemX(new GraphicsItem)
        ,   _controlUnitItemY(new GraphicsItem)
    {
        for (int i = 0;  i < Ac::SceneTypeCount;  ++i)
            _items.append(new GraphicsRootItem);
        _pitchUnitItemY->setTransform(QTransform::fromScale(1, 127));
        _pitchUnitItemX->setParentItem(_items[Ac::PitchScene]);
        _pitchUnitItemY->setParentItem(_items[Ac::PitchScene]);
        _controlUnitItemX->setParentItem(_items[Ac::ControlScene]);
        _controlUnitItemY->setParentItem(_items[Ac::ControlScene]);
    }

    ~SceneScoreItem()
    {
        delete tracks;
        qDeleteAll(_items);
    }

    int listCount() const
    {
        return 1;
    }

    SceneItemList *listAt(int i)
    {
        if (i == 0)
            return tracks;
        return 0;
    }

    QGraphicsItem *item(Ac::SceneType type) const
    {
        return _items[type];
    }

    QGraphicsItem *unitItem(Ac::SceneType type, Ac::Axis axis) const
    {
        switch (type) {
        case Ac::PitchScene:
            return Ac::XAxis == axis ? _pitchUnitItemX : _pitchUnitItemY;
        case Ac::ControlScene:
            return Ac::XAxis ==  axis ? _controlUnitItemX : _controlUnitItemY;
        default:
            return 0;
        }
    }

    void dataChanged(const QModelIndex &index)
    {
        qreal length = index.data(LengthRole).toReal();
        _pitchUnitItemX->setTransform(QTransform::fromScale(length, 1));
        _controlUnitItemX->setTransform(QTransform::fromScale(length, 1));
    }

public:
    SceneItemList *tracks;

private:
    QList<GraphicsRootItem*> _items;
    GraphicsItem *_pitchUnitItemX;
    GraphicsItem *_pitchUnitItemY;
    GraphicsItem *_controlUnitItemX;
    GraphicsItem *_controlUnitItemY;
};

class SceneGridLineItem : public SceneItem
{
public:
    SceneGridLineItem()
        :   _label(new GraphicsLabelItem)
    {}

    ~SceneGridLineItem()
    {
        delete _label;
    }

    void dataChanged(const QModelIndex &index)
    {
        _label->setText(index.data(LabelRole).toString());
    }

protected:
    GraphicsLabelItem *_label;
};

class SceneTimeLineItem : public SceneGridLineItem
{
public:
    SceneTimeLineItem()
        :   _pitchSceneLine(new QGraphicsLineItem)
        ,   _controlSceneLine(new QGraphicsLineItem)
    {}

    ~SceneTimeLineItem()
    {
        delete _controlSceneLine;
        delete _pitchSceneLine;
    }

    QGraphicsItem *item(Ac::SceneType type) const
    {
        switch (type) {
        case Ac::TimeLabelScene:
            return _label;
        default:
            return 0;
        }
    }

    QGraphicsItem *unitItem(Ac::SceneType type, Ac::Axis axis) const
    {
        if (Ac::YAxis == axis) {
            switch (type) {
            case Ac::PitchScene:
                return _pitchSceneLine;
            case Ac::ControlScene:
                return _controlSceneLine;
            default:
                return 0;
            }
        }
        return 0;
    }

    void dataChanged(const QModelIndex &index)
    {
        qreal location = index.data(LocationRole).toReal();
        _label->setPos(location, -10);
        _pitchSceneLine->setLine(location, 0, location, 1);
        _controlSceneLine->setLine(location, 0, location, 1);
        QColor color = index.data(ColorRole).value<QColor>();
        _pitchSceneLine->setPen(color);
        _controlSceneLine->setPen(color);
        SceneGridLineItem::dataChanged(index);
    }

private:
    QGraphicsLineItem *_pitchSceneLine;
    QGraphicsLineItem *_controlSceneLine;
};

class SceneHGridLineItem : public SceneGridLineItem
{
public:
    SceneHGridLineItem()
        :   _sceneLine(new QGraphicsLineItem)
    {}

    ~SceneHGridLineItem()
    {
        delete _sceneLine;
    }

    void dataChanged(const QModelIndex &index)
    {
        qreal location = index.data(LocationRole).toReal();
        _label->setPos(0, location);
        _sceneLine->setLine(0, location, 1, location);
        SceneGridLineItem::dataChanged(index);
    }

protected:
    QGraphicsLineItem *_sceneLine;
};

class ScenePitchLineItem : public SceneHGridLineItem
{
public:
    QGraphicsItem *item(Ac::SceneType type) const
    {
        if (Ac::PitchLabelScene == type)
            return _label;
        return 0;
    }

    QGraphicsItem *unitItem(Ac::SceneType type, Ac::Axis axis) const
    {
        if (Ac::PitchScene == type && Ac::XAxis == axis)
            return _sceneLine;
        return 0;
    }
};

class SceneControlLineItem : public SceneHGridLineItem
{
public:
    QGraphicsItem *item(Ac::SceneType type) const
    {
        if (Ac::ControlLabelScene == type)
            return _label;
        return 0;
    }

    QGraphicsItem *unitItem(Ac::SceneType type, Ac::Axis axis) const
    {
        if (Ac::ControlScene == type && Ac::XAxis == axis)
            return _sceneLine;
        return 0;
    }
};

#endif // AC_GRAPHICSSCENEITEM_H
