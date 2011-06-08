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

#ifndef MI_LIST_H
#define MI_LIST_H

#include <mi_object.h>

#include <QList>

class MiList
{
public:
    MiList(MiObject *owner, int propertyIndex)
        :   owner(owner)
        ,   propertyIndex(propertyIndex)
    {}

    virtual bool isConstant() const { return false; }

    int count() const { return list.count(); }
    bool isEmpty() const { return list.isEmpty(); }
    MiObject *at(int i) const { return list.at(i); }
    MiObject *first() const { return list.first(); }
    MiObject *last() const { return list.last(); }
    int indexOf(MiObject *object, int from = 0) const { return list.indexOf(object, from); }
    void append(MiObject *object) { list.append(object);  emitChanged(); }
    void append(const QList<MiObject*> &objects) { list.append(objects);  emitChanged(); }
    void insert(int i, MiObject *object) { list.insert(i, object);  emitChanged(); }
    void remove(int i) { list.removeAt(i);  emitChanged(); }
    void clear() { list.clear();  emitChanged(); }
    void deleteAll() { qDeleteAll(list);  clear(); }

    template <typename T> T *at(int i) const { return qobject_cast<T*>(at(i)); }
    template <typename T> T *first() const { return qobject_cast<T*>(first()); }
    template <typename T> T *last() const { return qobject_cast<T*>(last()); }

    template <typename LessThan> void sort(LessThan lessThan) { qSort(list.begin(), list.end(), lessThan);  emitChanged(); }

private:
    void emitChanged() { owner->emit propertyChanged(propertyIndex); }

    MiObject *owner;
    int propertyIndex;
    QList<MiObject*> list;
};

Q_DECLARE_METATYPE(MiList*);

class MiConstantList : public MiList
{
public:
    MiConstantList(MiObject *owner, int propertyIndex)
        :   MiList(owner, propertyIndex)
    {}

    virtual bool isConstant() const { return true; }
};

#endif // MI_LIST_H
