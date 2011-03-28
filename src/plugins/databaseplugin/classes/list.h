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

#include <databaseplugin/classes/object.h>

#include <QtCore/QList>

namespace Database {

class List
{
public:
    List(Object *owner, int propertyIndex)
        :   owner(owner)
        ,   propertyIndex(propertyIndex)
    {}

public:
    virtual bool isConstant() const { return false; }

    int count() const { return list.count(); }
    bool isEmpty() const { return list.isEmpty(); }
    Object *at(int i) const { return list.at(i); }
    Object *first() const { return list.first(); }
    Object *last() const { return list.last(); }
    int indexOf(Object *object, int from = 0) const { return list.indexOf(object, from); }
    void append(Object *object) { list.append(object);  emitChanged(); }
    void insert(int i, Object *object) { list.insert(i, object);  emitChanged(); }
    void remove(int i) { list.removeAt(i);  emitChanged(); }
    void clear() { list.clear();  emitChanged(); }
    void deleteAll() { qDeleteAll(list);  clear(); }

    template <typename T> T *at(int i) const { return qobject_cast<T*>(at(i)); }
    template <typename T> T *first() const { return qobject_cast<T*>(first()); }
    template <typename T> T *last() const { return qobject_cast<T*>(last()); }

private:
    void emitChanged() { owner->emit propertyChanged(propertyIndex); }

private:
    Object *owner;
    int propertyIndex;
    QList<Object*> list;
};

class ConstantList : public List
{
public:
    ConstantList(Object *owner, int propertyIndex)
        :   List(owner, propertyIndex)
    {}

    bool isConstant() const { return true; }
};

} // namespace Database

Q_DECLARE_METATYPE(Database::List*);

#endif // LIST_H
