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

class UniquelyNamedObjectList : public ObjectList
{
public:
    UniquelyNamedObjectList(int listType, QObject *parent = 0)
        :   ObjectList(*new ObjectListPrivate(this, listType, new ModelItemList(this)), parent)
    {}

protected:
   UniquelyNamedObjectList(ObjectListPrivate &dd, QObject *parent)
       :   ObjectList(dd, parent)
   {}

    class ModelItemList : public ObjectList::ModelItemList
    {
    public:
        ModelItemList(ObjectList *q)
            :   ObjectList::ModelItemList(q)
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
            ObjectList::ModelItemList::insert(i, item);
        }
    };
};

#endif // MI_UNIQUELYNAMEDOBJECTLIST_H
