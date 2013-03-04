/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2013 Andrew Fillebrown.
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

#ifndef IUNKOWN_H
#define IUNKOWN_H

#define QUERY(InterfaceType, Unknown) query<InterfaceType>(Unknown)

class IUnknown
{
public:
    virtual ~IUnknown() {}
    virtual int interfaceType() const = 0;
    virtual bool isTypeOfInterface(int interfaceType) const = 0;
    virtual void *queryInterface(int interfaceType) const = 0;
};

template <class T, class Unknown> inline
T *query(const Unknown *unknown)
{
    if (!unknown)
        return 0;
    return static_cast<T*>(unknown->queryInterface(T::InterfaceType));
}

#endif
