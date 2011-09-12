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

#ifndef AC_MODEL_H
#define AC_MODEL_H

#include <ac_core_global.h>

#include <QColor>

#include <QAbstractItemModel>

class Item;
template <typename T> class ItemList;
class Score;

class AC_CORE_EXPORT AbstractItemModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    ~AbstractItemModel() {}

signals:
    void dataAboutToChange(const QModelIndex &topLeft, const QModelIndex &bottomRight);

protected:
    AbstractItemModel(QObject *parent)
        :   QAbstractItemModel(parent)
    {}
};

class AC_CORE_EXPORT Model : public AbstractItemModel
{
    Q_OBJECT

public:
    explicit Model(QObject *parent = 0);
    ~Model();

    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const { return 1; }
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const;

    Score *score() const { return _score; }

protected:
    QModelIndex indexFromItem(Item *item) const;
    Item *itemFromIndex(const QModelIndex &index) const;

    void maybeEmitLayoutAboutToBeChanged()
    {
        if (_layoutAboutToBeChangedEmitted)
            return;
        _layoutAboutToBeChangedEmitted = true;
        emit layoutAboutToBeChanged();
    }

    void maybeEmitLayoutChanged()
    {
        if (!_layoutAboutToBeChangedEmitted)
            return;
        _layoutAboutToBeChangedEmitted = false;
        emit layoutChanged();
    }

private:
    Score *_score;
    QModelIndexList _persistentIndexCache;
    bool _layoutAboutToBeChangedEmitted;

    friend class Item;
    friend class ItemList<class ControlLine>;
    friend class ItemList<class Note>;
    friend class ItemList<class PitchLine>;
    friend class ItemList<class Point>;
    friend class ItemList<class TimeLine>;
    friend class ItemList<class Track>;
};

#endif // AC_MODEL_H
