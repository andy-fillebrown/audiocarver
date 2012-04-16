/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2012 Andrew Fillebrown.
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

#ifndef MI_DATAOBJECT_H
#define MI_DATAOBJECT_H

#include "mi_aggregator.h"
#include "mi_imodeldata.h"
#include "mi_imodelitem.h"

class DataObjectList;

class MI_CORE_EXPORT DataObject : public Aggregator
{
    Q_IAGGREGATOR_BASE(DataObject)

    QString _name;
    Q_IAGGREGATOR_BASE__ROLECOUNT(1)

    DataObject *_parent;

protected:
    enum { TotalItemCount = 0 };

    DataObject()
        :   _parent(0)
    {}

public:
    const QString &name() const
    {
        return _name;
    }

    bool setName(const QString &name);

    DataObject *parent() const
    {
        return isList()
                ? _parent
                  ? _parent->parent()
                  : 0
                : _parent;
    }

    void setParent(DataObject *parent);

    virtual bool isList() const
    {
        return false;
    }

    inline DataObjectList *list() const;

    virtual void dataAboutToBeChanged(const DataObject *dataObject, int role, Mi::NotificationFlags notificationFlags);
    virtual void dataChanged(const DataObject *dataObject, int role, Mi::NotificationFlags notificationFlags);
    virtual void parentAboutToBeChanged(const DataObject *dataObject, Mi::NotificationFlags notificationFlags);
    virtual void parentChanged(const DataObject *dataObject, Mi::NotificationFlags notificationFlags);

protected:
    // IModelData
    class ModelData : public IModelData
    {
        Q_IMODELDATA_BASE
        Q_IMODELDATA_BASE__ROLE_FUNCTIONS

        QVariant getVariant(int role) const
        {
            switch (role) {
            case Qt::DisplayRole:
            case Mi::NameRole:
                return a()->name();
            default:
                Q_ASSERT(0);
                return QVariant();
            }
        }

        bool setVariant(const QVariant &data, int role)
        {
            switch (role) {
            case Qt::EditRole:
            case Mi::NameRole:
                return a()->setName(qvariant_cast<QString>(data));
            default:
                Q_ASSERT(0);
                return false;
            }
        }
    };

    // IModelItem
    class ModelItem : public IModelItem
    {
        Q_IMODELITEM_BASE
        Q_IMODELITEM_BASE__ITEMTYPE(Mi::UnknownItem)

        int count() const { return 0; }
        int indexOf(const IModelItem *item) const { Q_ASSERT(0); return -1; }
        IModelItem *at(int i) const { Q_ASSERT(0); return 0; }
        IModelItem *findItem(int itemType) const { return 0; }
        IModelList *findList(int listType) const { return 0; }
    };
};

#include <mi_dataobjectlist.h>

inline DataObjectList *DataObject::list() const
{
    return _parent->isList()
            ? cast<DataObjectList>(_parent)
            : 0;
}

#endif // MI_DATAOBJECT_H
