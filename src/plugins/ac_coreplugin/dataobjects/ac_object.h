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

#ifndef AC_OBJECT_H
#define AC_OBJECT_H

#include <ac_global.h>
#include <ac_imodelitem.h>

#include <mi_iunknown.h>

#include <QObject>

class Model;
class Object;

class AC_CORE_EXPORT ObjectPrivate
{
public:
    Object *q_ptr;
    Model *model;

    ObjectPrivate(Object *q)
        :   q_ptr(q)
        ,   model(0)
    {}

    virtual ~ObjectPrivate() {}

    void setModel(Model *model);
    void beginChangeData();
    void endChangeData();
    void beginInsertObjects(int first, int last);
    void endInsertObjects();
    void beginRemoveObjects(int first, int last);
    void endRemoveObjects();
};

class AC_CORE_EXPORT Object : public QObject
        ,   public IModelItem
{
    Q_OBJECT

public:
    ~Object()
    {
        delete d_ptr;
    }

    Object *parent() const
    {
        return qobject_cast<Object*>(QObject::parent());
    }

    virtual void setParent(Object *parent)
    {
        QObject::setParent(parent);
    }

    virtual QString name() const { return QString(); }

    // IModelItem
    IModelItem *parentModelItem() const
    {
        return parent();
    }

    int modelItemCount() const
    {
        return 0;
    }

    int modelItemIndex(IModelItem *item) const
    {
        Q_UNUSED(item);
        Q_ASSERT(false);
        return -1;
    }

    IModelItem *modelItemAt(int i) const
    {
        Q_UNUSED(i);
        Q_ASSERT(false);
        return 0;
    }

    IModelItem *findModelItem(Ac::ItemType type) const
    {
        Q_UNUSED(type);
        Q_ASSERT(false);
        return 0;
    }

    IModelItem *findModelItemList(Ac::ItemType type) const
    {
        Q_UNUSED(type);
        Q_ASSERT(false);
        return 0;
    }

    int persistentRoleCount() const
    {
        return metaObject()->propertyCount();
    }

    int persistentRoleAt(int i) const
    {
        if (i == 0)
            return Ac::NameRole;
        Q_ASSERT(false);
        return -1;
    }

    QVariant data(int role) const;
    bool setData(const QVariant &value, int role)
    {
        Q_UNUSED(value);
        Q_UNUSED(role);
        Q_ASSERT(false);
        return false;
    }

    Qt::ItemFlags flags() const
    {
        return Qt::ItemIsEnabled;
    }

    // IUnknown
    void *query(int type) const
    {
        switch (type) {
        case Ac::ModelItemInterface:
            return Q_I(IModelItem);
        default:
            return 0;
        }
    }

protected:
    Object(ObjectPrivate &dd, QObject *parent)
        :   QObject(parent)
        ,   d_ptr(&dd)
    {}

    ObjectPrivate *d_ptr;

private:
    Q_DISABLE_COPY(Object)
    Q_DECLARE_PRIVATE(Object)
};

#endif // ACOBJECT_H
