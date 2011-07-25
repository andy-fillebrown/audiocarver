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

#ifndef MI_IPARENT_H
#define MI_IPARENT_H

#include <icomponent.h>

namespace Database {

class Object;

class IParent : protected IComponent
{
    Q_OBJECT

public:
    IParent(Object *root);

    virtual QString isIdUsed(const QString &id) const { return ""; }
    virtual QString uniquifyId(const QString &id) const { return ""; }

    int childCount() const
    {
        return children().count();
    }

    virtual bool addChild(Object *child)
    {
        return false;
    }

    void removeChild(Object *child)
    {}

private:
    Q_DISABLE_COPY(IParent)
    Q_ENABLE_QUERY(IParent)
};

} // namespace Database

#endif // MI_IPARENT_H
