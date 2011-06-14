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

#include <mi_objectlist.h>

template <typename T> class MiList
{
    static bool lessThan(MiObject *a, MiObject *b);

public:
    MiList(const QString &propertyName, MiObject *owner, QObject *parent = 0)
        :   list(new MiObjectList(propertyName, owner, parent))
    {}

    ~MiList() { delete list; }

    bool isConstant() const { return list->isConstant(); }

    int count() const { return list->count(); }
    bool isEmpty() const { return list->isEmpty(); }
    T *at(int i) const { return qobject_cast<T*>(list->at(i)); }
    T *first() const { return qobject_cast<T*>(list->first()); }
    T *last() const { return qobject_cast<T*>(list->last()); }
    QList<T*> toList() const { QList<T*> objs;  for (int i=0; i<count(); ++i) objs.append(at(i));  return objs; }
    int indexOf(T *object, int from = 0) const { return list->indexOf(object, from); }
    T *add() { T* object = new T(list->parent);  append(object);  return object; }
    void append(T *object) { list->append(object); }
    void append(const QList<T*> &objects) { QList<MiObject*> objs;  foreach (MiObject *object, objects) objs.append(object);  list->append(objs); }
    void insert(int i, T *object) { list->insert(i, object); }
    void remove(int i) { list->remove(i); }
    T *take(int i) { T *object = at(i);  remove(i);  return object; }
    void erase(int i) { at(i)->erase(); }
    void eraseAndRemove(int i) { erase(i);  remove(i); }
    T *eraseAndTake(int i) { erase(i);  return take(i); }
    void clear() { list->clear(); }
    void deleteAll() { list->deleteAll(); }
    void sort() { list->sort(lessThan); }
    MiObjectList *objects() { return list; }

protected:
    MiList(MiObjectList *list)
        :   list(list)
    {}

    MiObjectList *list;
};

template <typename T> class MiConstantList : MiList<T>
{
public:
    MiConstantList(const QString &propertyName, MiObject *owner, QObject *parent = 0)
        :   MiList<T>(new MiConstantObjectList(propertyName, owner, parent))
    {}
};

#endif // MI_LIST_H
