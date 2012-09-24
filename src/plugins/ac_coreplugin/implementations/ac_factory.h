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

#ifndef AC_FACTORY_H
#define AC_FACTORY_H

#include <ac_ifactory.h>

class ObjectFactory : public IObjectFactory
{
    Q_OBJECT

public:
    ObjectFactory();

    IModelItem *create(int type) const;
};

class FilerFactory : public IFilerFactory
{
    Q_OBJECT

public:
    FilerFactory();

    IReader *createReader(int type) const;
    IWriter *createWriter(int type) const;
};

#endif // AC_FACTORY_H
