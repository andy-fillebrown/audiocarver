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

#include <mi_namespace.h>

class Object;
class ObjectPrivate;

class QVariant;

class IUnknown
{
public:
    virtual ~IUnknown() {}

    virtual void *queryInterface(int interface) const = 0;
};

template <class T> inline
T *query(const IUnknown *unknown)
{
    return unknown ? reinterpret_cast<T*>(unknown->queryInterface(T::Type)) : 0;
}

template <> inline
Object *query(const IUnknown *unknown)
{
    return unknown ? reinterpret_cast<Object*>(unknown->queryInterface(Mi::ObjectInterface)) : 0;
}

template <> inline
ObjectPrivate *query(const IUnknown *unknown)
{
    return unknown ? reinterpret_cast<ObjectPrivate*>(unknown->queryInterface(Mi::ObjectPrivateInterface)) : 0;
}

template <typename Interface> inline
Interface *interface_cast(IUnknown *unknown)
{
    return dynamic_cast<Interface*>(unknown);
}

template <typename Interface> inline
Interface *interface_cast(const IUnknown *unknown)
{
    return dynamic_cast<const Interface*>(unknown);
}

template <typename Interface, typename Object> inline
Interface *objectToInterface_cast(Object *object)
{
    return dynamic_cast<Interface*>(object);
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

template <typename Object> inline
Object *interfaceToObject_cast(const IUnknown *interface)
{
    return const_cast<Object*>(dynamic_cast<const Object*>(interface));
}

MI_CORE_EXPORT IUnknown *variantToUnknown_cast(const QVariant &v);

#endif // MI_IUNKOWN_H
