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

class IUnknown
{
public:
    virtual ~IUnknown() {}

    template <class T> T *query()
    {
        return dynamic_cast<T*>(this);
    }

    template <class T> const T *query() const
    {
        return dynamic_cast<const T*>(this);
    }
};

#endif // MIIUNKOWN_H
