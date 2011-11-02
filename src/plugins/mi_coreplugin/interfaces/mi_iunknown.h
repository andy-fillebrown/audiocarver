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

#ifndef MIIUNKOWN_H
#define MIIUNKOWN_H

#include <mi_global.h>

class QVariant;

class IUnknown
{
public:
    virtual ~IUnknown() {}

    virtual void *query(int type) const = 0;
};

template <class T> inline
T *query(IUnknown *unknown)
{
    return unknown ? reinterpret_cast<T*>(unknown->query(T::Type)) : 0;
}

template <typename Interface, typename Object> inline
Interface *objectToInterface_cast(const Object *object)
{
    return const_cast<Interface*>(dynamic_cast<const Interface*>(object));
}

template <typename Object> inline
Object *interfaceToObject_cast(IUnknown *interface)
{
    return dynamic_cast<Object*>(interface);
}

MI_CORE_EXPORT IUnknown *variantToUnknown_cast(const QVariant &v);

#endif // MIIUNKOWN_H
