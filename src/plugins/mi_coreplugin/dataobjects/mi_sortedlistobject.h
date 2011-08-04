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

#ifndef MI_SORTEDLISTOBJECT_H
#define MI_SORTEDLISTOBJECT_H

#include <mi_listobject.h>

class MI_CORE_EXPORT MiSortedListObject : public MiListObject
{
    Q_OBJECT

public:
    typedef MiListObject::PropertyIndex PropertyIndex;

    virtual ~MiSortedListObject()
    {}

    virtual bool isSorted() const = 0;
    virtual void sort() = 0;

protected:
    MiSortedListObject(MiListObjectPrivate &dd)
        :   MiListObject(dd)
    {}

private:
    Q_DISABLE_COPY(MiSortedListObject)
};

class MiSortedListObjectPrivate : public MiListObjectPrivate
{
    Q_DECLARE_PUBLIC(MiSortedListObject)

public:
    MiSortedListObjectPrivate(MiSortedListObject *q, int propertyIndex)
        :   MiListObjectPrivate(q, propertyIndex)
    {}

    virtual ~MiSortedListObjectPrivate()
    {}

    template <typename T>
    bool isSorted() const
    {
        const QList<T*> &children = this->children<T>();
        for (int i = 1;  i < children.count();  ++i)
            if (children[i]->isLessThan(children[i - 1]))
                return false;
        return true;
    }

    template <typename T>
    void sort()
    {
        if (isSorted<T>())
            return;
        qSort(children<T>(), lessThan<T>);
    }

    template <typename T>
    static bool lessThan(const T *a, const T *b)
    {
        return a->isLessThan(b);
    }

    virtual void endChange(int i)
    {
        if (isSortProperty(i)) {
            Q_Q(MiSortedListObject);
            if (!q->isSorted())
                q->sort();
        }
    }

    virtual bool isSortProperty(int i) const
    {
        Q_UNUSED(i);
        return true;
    }
};

#endif // MI_SORTEDLISTOBJECT_H
