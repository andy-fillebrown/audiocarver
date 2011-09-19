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

#ifndef ACOBJECT_H
#define ACOBJECT_H

#include <accoreglobal.h>
#include <interfaces/acimodelitem.h>

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
        d_ptr->setModel(parent ? parent->model() : 0);
    }

    Model *model() const
    {
        return d_ptr->model;
    }

    // IModelItem

    Ac::ItemType type() const = 0;

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
        return 0;
    }

    IModelItem *findModelItem(Ac::ItemType type) const
    {
        Q_UNUSED(type);
        return 0;
    }

    IModelItem *findModelItemList(Ac::ItemType type) const
    {
        Q_UNUSED(type);
        return 0;
    }

    QVariant data(int role) const;
    bool setData(const QVariant &value, int role)
    {
        Q_UNUSED(value);
        Q_UNUSED(role);
        return false;
    }

    Qt::ItemFlags flags() const
    {
        return Qt::ItemIsSelectable
                | Qt::ItemIsEditable
                | Qt::ItemIsEnabled;
    }

protected:
    Object(ObjectPrivate &dd, QObject *parent = 0)
        :   QObject(parent)
        ,   d_ptr(&dd)
    {}

    ObjectPrivate *d_ptr;

private:
    Q_DISABLE_COPY(Object)
    Q_DECLARE_PRIVATE(Object)
};

#endif // ACOBJECT_H
