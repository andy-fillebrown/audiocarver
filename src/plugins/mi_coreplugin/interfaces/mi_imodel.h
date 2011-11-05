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

#ifndef MI_IMODEL_H
#define MI_IMODEL_H

#include <mi_global.h>
#include <mi_namespace.h>

#include <QAbstractItemModel>

class IModelItem;

class MI_CORE_EXPORT IModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    IModel();

    static IModel *instance();

    virtual IModelItem *rootItem() const = 0;
    virtual QModelIndex itemIndex(int type) const = 0;
    virtual QModelIndex listIndex(int type) const = 0;

    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &) const { return 1; }
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const;

    virtual QModelIndex index(int row, const QModelIndex &parent) const
    {
        return index(row, 0, parent);
    }

    virtual IModelItem *itemFromIndex(const QModelIndex &index) const;
    virtual QModelIndex indexFromItem(const IModelItem *item) const;

    virtual bool insertItem(IModelItem *item, int row, const QModelIndex &parent);
    virtual void removeItem(int row, const QModelIndex &parent);
    virtual IModelItem *takeItem(int row, const QModelIndex &parent);

signals:
    void pointsChanged(const QModelIndex &index);
    void dataAboutToBeChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);

private slots:
    void deleteOrphans();

private:
    friend class ObjectPrivate;
};

#endif // MI_IMODEL_H
