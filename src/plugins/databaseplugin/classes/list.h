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

#ifndef LIST_H
#define LIST_H

#include "object.h"

#include <QtCore/QList>

namespace Database {

class List
{
public:
    List(Object *owner, int propertyIndex)
        :   owner(owner)
        ,   propertyIndex(propertyIndex)
    {
    }

    ~List()
    {
    }

    int count() const { return list.count(); }
    const Object *at(int i) const { return list.at(i); }
    int indexOf(Object *object, int from = 0) const { return list.indexOf(object, from); }
    void append(Object *object) { list.append(object);  emitChanged(); }
    void insert(int i, Object *object) { list.insert(i, object);  emitChanged(); }
    void remove(int i) { list.removeAt(i);  emitChanged(); }
    void clear() { list.clear();  emitChanged(); }

    void deleteAll() { qDeleteAll(list);  clear(); }


private:
    void emitChanged() { owner->emit propertyChanged(propertyIndex, owner); }

    Object *owner;
    int propertyIndex;
    QList<Object*> list;
};

} // namespace Database

Q_DECLARE_METATYPE(Database::List*);

#endif // LIST_H
