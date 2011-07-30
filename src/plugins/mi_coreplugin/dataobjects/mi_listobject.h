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

#ifndef MI_LISTOBJECT_H
#define MI_LISTOBJECT_H

#include <mi_object.h>

#define MiListObjectPrivate MiObjectPrivate

class MI_CORE_EXPORT MiListObject : public MiObject
{
    Q_OBJECT

public:
    typedef MiObject::PropertyIndex PropertyIndex;

    MiListObject()
        :   MiObject(*(new MiListObjectPrivate(this)))
    {}

    virtual ~MiListObject()
    {}

    const QList<MiObject*> &children() const
    {
        return d_ptr->children<MiObject>();
    }

    virtual void addChild(MiObject *child)
    {
        d_ptr->addChild(child);
    }

    virtual void removeChild(MiObject *child)
    {
        d_ptr->removeChild(child);
    }

    bool isChildChanged() const
    {
        foreach (const MiObject *child, children())
            if (child->isChanged())
                return true;
        return false;
    }

protected:
    MiListObject(MiListObjectPrivate &dd)
        :   MiObject(dd)
    {}

private:
    Q_DECLARE_PRIVATE(MiListObject)
    Q_DISABLE_COPY(MiListObject)
};

#endif // MI_LISTOBJECT_H
