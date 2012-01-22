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

#ifndef MI_UNIQUELYNAMEDOBJECTLIST_H
#define MI_UNIQUELYNAMEDOBJECTLIST_H

#include <mi_objectlist.h>

template <class T> class UniquelyNamedObjectTList : public ObjectTList<T>
{
public:
    UniquelyNamedObjectTList(QObject *parent = 0)
        :   ObjectTList<T>(parent)
    {}

    void insert(int i, Object *object)
    {
        const QString name = object->name();
        int suffix = 0;
        QString new_name = name;
        while (this->hasChild(new_name))
            new_name = QString("%1.%2").arg(name).arg(++suffix);
        if (name != new_name)
            object->setName(new_name);
        ObjectTList<T>::insert(i, object);
    }

protected:
    UniquelyNamedObjectTList(ObjectTListPrivate<T> &dd, QObject *parent)
        :   ObjectTList<T>(dd, parent)
    {}
};

#endif // MI_UNIQUELYNAMEDOBJECTLIST_H
