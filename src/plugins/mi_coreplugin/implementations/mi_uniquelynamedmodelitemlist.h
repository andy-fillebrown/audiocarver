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

class UniquelyNamedObjectListPrivate;
class UniquelyNamedObjectList : public ObjectList
{
public:
    inline UniquelyNamedObjectList(int listType, QObject *parent = 0);

protected:
    inline UniquelyNamedObjectList(UniquelyNamedObjectListPrivate &dd, QObject *parent);
};

class UniquelyNamedObjectListPrivate : public ObjectListPrivate
{
public:
    class ModelItemList : public ObjectListPrivate::ModelItemList
    {
    public:
        ModelItemList(ObjectList *q)
            :   ObjectListPrivate::ModelItemList(q)
        {}

        void insert(int i, IModelItem *item)
        {
            const QString name = item->name();
            if (!name.isEmpty()) {
                int suffix = 0;
                QString new_name = name;
                while (hasChild(new_name))
                    new_name = QString("%1.%2").arg(name).arg(++suffix);
                if (name != new_name)
                    item->setName(new_name);
            }
            ObjectListPrivate::ModelItemList::insert(i, item);
        }
    };

    UniquelyNamedObjectListPrivate(ObjectList *q, int listType, ModelItemList *modelItemList)
        :   ObjectListPrivate(q, listType, modelItemList)
    {}
};

inline UniquelyNamedObjectList::UniquelyNamedObjectList(int listType, QObject *parent)
    :   ObjectList(*new ObjectListPrivate(this, listType, new UniquelyNamedObjectListPrivate::ModelItemList(this)), parent)
{}

inline UniquelyNamedObjectList::UniquelyNamedObjectList(UniquelyNamedObjectListPrivate &dd, QObject *parent)
    :   ObjectList(dd, parent)
{}

#endif // MI_UNIQUELYNAMEDOBJECTLIST_H
