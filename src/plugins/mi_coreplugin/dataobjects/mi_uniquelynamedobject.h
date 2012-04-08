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

#ifndef MI_UNIQUELYNAMEDOBJECT_H
#define MI_UNIQUELYNAMEDOBJECT_H

#include <mi_object.h>

class MI_CORE_EXPORT UniquelyNamedObject : public Object
{
    Q_OBJECT

protected:
    UniquelyNamedObject(ObjectPrivate &dd, QObject *parent)
        :   Object(dd, parent)
    {}

private:
    UniquelyNamedObject()
    {}

public:
    class ModelItem : Object::ModelItem
    {
    public:
        ModelItem(Object *q)
            :   Object::ModelItem(q)
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
            Object::ModelItem::setName(name);
        }
    };
};

#endif // MI_UNIQUELYNAMEDOBJECT_H
