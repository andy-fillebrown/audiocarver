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

#ifndef MI_UNIQUELYNAMEDMODELITEM_H
#define MI_UNIQUELYNAMEDMODELITEM_H

#include <mi_object.h>

class UniquelyNamedObjectPrivate;
class MI_CORE_EXPORT UniquelyNamedObject : public Object
{
    UniquelyNamedObject()
    {}

    Q_OBJECT

protected:
    inline UniquelyNamedObject(UniquelyNamedObjectPrivate &dd, QObject *parent);
};

class UniquelyNamedObjectPrivate : public ObjectPrivate
{
public:
    class ModelItem : public ObjectPrivate::ModelItem
    {
    public:
        ModelItem(Object *q)
            :   ObjectPrivate::ModelItem(q)
        {}

        void setName(const QString &name)
        {
            if (this->name().toLower() == name.toLower())
                return;
            if (!name.isEmpty()) {
                IModelItem *parent = this->parent();
                if (parent && parent->hasChild(name))
                    return;
            }
            ObjectPrivate::ModelItem::setName(name);
        }
    };

    UniquelyNamedObjectPrivate(UniquelyNamedObject *q, ModelItem *modelItem)
        :   ObjectPrivate(q, modelItem)
    {}
};

inline UniquelyNamedObject::UniquelyNamedObject(UniquelyNamedObjectPrivate &dd, QObject *parent)
    :   Object(dd, parent)
{}

#endif // MI_UNIQUELYNAMEDMODELITEM_H
