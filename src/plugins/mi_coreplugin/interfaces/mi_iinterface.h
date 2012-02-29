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

#ifndef MI_IINTERFACE_H
#define MI_IINTERFACE_H

#include <mi_global.h>

class IInterface
{
public:
    virtual ~IInterface() {}

    virtual void *query(int type) const = 0;
};

template <class T> inline
T *query(IInterface *interface)
{
    return unknown ? reinterpret_cast<T*>(interface->query(T::Type)) : 0;
}

#endif // MI_IINTERFACE_H
