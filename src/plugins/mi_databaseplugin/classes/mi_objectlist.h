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
    MiObjectList(const QString &propertyName, MiObject *parent = 0)
        :   _propertyName(propertyName)
        ,   _parent(parent)
    {}

    QObject *parent() const { return _parent; }

    virtual bool isConstant() const { return false; }

    int count() const { return _list.count(); }
    bool isEmpty() const { return _list.isEmpty(); }
    MiObject *at(int i) const { return _list.at(i); }
    MiObject *first() const { return _list.first(); }
    MiObject *last() const { return _list.last(); }
    int indexOf(MiObject *object, int from = 0) const { return _list.indexOf(object, from); }
    void append(MiObject *object) { object->setParent(_parent);  _list.append(object);  emitChanged(); }
    void append(const QList<MiObject*> &objects) { foreach (MiObject *object, objects) object->setParent(_parent);  _list.append(objects);  emitChanged(); }
    void insert(int i, MiObject *object) { object->setParent(_parent);  _list.insert(i, object);  emitChanged(); }
    void remove(int i) { _list.removeAt(i);  emitChanged(); }
    void clear() { _list.clear();  emitChanged(); }
    void deleteAll() { qDeleteAll(_list);  clear(); }

    template <typename LessThan> void sort(LessThan lessThan) { qSort(_list.begin(), _list.end(), lessThan);  emitChanged(); }

    QList<MiObject*> *list() { return &_list; }

private:
    void emitChanged() { _parent->emit propertyChanged(_propertyName); }

    QString _propertyName;
    MiObject *_parent;
    QList<MiObject*> _list;
};

Q_DECLARE_METATYPE(MiObjectList*);

class MiConstantObjectList : public MiObjectList
{
public:
    MiConstantObjectList(const QString &propertyName, MiObject *parent = 0)
        :   MiObjectList(propertyName, parent)
    {}

    virtual bool isConstant() const { return true; }
};

#endif // MI_OBJECTLIST_H
