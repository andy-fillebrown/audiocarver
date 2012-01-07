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

#ifndef MI_UNIQUELYNAMEDOBJECT_H
#define MI_UNIQUELYNAMEDOBJECT_H

#include <mi_object.h>

class MI_CORE_EXPORT UniquelyNamedObject : public Object
{
    Q_OBJECT

public:
    void setParent(Object *parent)
    {
        Object *prev_parent = this->parent();
        Object::setParent(parent);
        if (!this->parent())
            setParent(prev_parent);
    }

    void setName(const QString &name)
    {
        Object *par = parent();
        if (par && par->findChild<Object*>(name))
            return;
        Object::setName(name);
    }

protected:
    UniquelyNamedObject(ObjectPrivate &dd, QObject *parent)
        :   Object(dd, parent)
    {}
};

#endif // MI_UNIQUELYNAMEDOBJECT_H
