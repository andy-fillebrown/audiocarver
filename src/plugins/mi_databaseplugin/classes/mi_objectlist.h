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

#ifndef MI_OBJECTLIST_H
#define MI_OBJECTLIST_H

#include <mi_object.h>

#include <QList>

class MiObjectList
{
public:
    QObject *parent;

    MiObjectList(const QString &propertyName, MiObject *owner, QObject *parent = 0)
        :   parent(parent ? parent : owner)
        ,   propertyName(propertyName)
        ,   owner(owner)
    {}

    virtual bool isConstant() const { return false; }

    int count() const { return list.count(); }
    bool isEmpty() const { return list.isEmpty(); }
    MiObject *at(int i) const { return list.at(i); }
    MiObject *first() const { return list.first(); }
    MiObject *last() const { return list.last(); }
    int indexOf(MiObject *object, int from = 0) const { return list.indexOf(object, from); }
    void append(MiObject *object) { object->setParent(parent);  list.append(object);  emitChanged(); }
    void append(const QList<MiObject*> &objects) { foreach (MiObject *object, objects) object->setParent(parent);  list.append(objects);  emitChanged(); }
    void insert(int i, MiObject *object) { object->setParent(parent);  list.insert(i, object);  emitChanged(); }
    void remove(int i) { list.removeAt(i);  emitChanged(); }
    void clear() { list.clear();  emitChanged(); }
    void deleteAll() { qDeleteAll(list);  clear(); }

    template <typename LessThan> void sort(LessThan lessThan) { qSort(list.begin(), list.end(), lessThan);  emitChanged(); }

private:
    void emitChanged() { owner->emit propertyChanged(propertyName); }

    QString propertyName;
    MiObject *owner;
    QList<MiObject*> list;
};

Q_DECLARE_METATYPE(MiObjectList*);

class MiConstantObjectList : public MiObjectList
{
public:
    MiConstantObjectList(const QString &propertyName, MiObject *owner, QObject *parent = 0)
        :   MiObjectList(propertyName, owner, parent)
    {}

    virtual bool isConstant() const { return true; }
};

#endif // MI_OBJECTLIST_H