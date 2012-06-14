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

#ifndef MI_IUNKOWN_H
#define MI_IUNKOWN_H

#include <mi_corenamespace.h>

class IUnknown
{
public:
    virtual ~IUnknown()
    {}

    virtual int interfaceType() const = 0;
    virtual bool isTypeOfInterface(int interfaceType) const = 0;

    virtual void *queryInterface(int interfaceType)
    {
        if (isTypeOfInterface(interfaceType))
            return this;
        return 0;
    }

    virtual const void *queryInterface(int interfaceType) const
    {
        if (isTypeOfInterface(interfaceType))
            return this;
        return 0;
    }
};

template <class T, class Unknown> inline
T *query(Unknown *unknown)
{
    if (unknown)
        return static_cast<T*>(unknown->queryInterface(T::InterfaceType));
    return 0;
}

template <class T, class Unknown> inline
const T *query(const Unknown *unknown)
{
    if (unknown)
        return static_cast<const T*>(unknown->queryInterface(T::InterfaceType));
    return 0;
}

template <class T, class Unknown> inline
const T *const_query(const Unknown *unknown)
{
    return query<T>(unknown);
}

#endif // MI_IUNKOWN_H
