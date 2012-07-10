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

#ifndef AC_IFACTORY_H
#define AC_IFACTORY_H

#include <ac_global.h>

#include <QObject>

class IReader;
class IWriter;
class IModelItem;

class AC_CORE_EXPORT IObjectFactory : public QObject
{
    Q_OBJECT

public:
    IObjectFactory();

    static IObjectFactory *instance();

    virtual IModelItem *create(int type) const = 0;

    template <typename T> T *create() { return object_cast<T>(create(T::Type)); }
};

class AC_CORE_EXPORT IFilerFactory : public QObject
{
    Q_OBJECT

public:
    IFilerFactory();

    static IFilerFactory *instance();

    virtual IReader *createReader(int type) const = 0;
    virtual IWriter *createWriter(int type) const = 0;
};

#endif // AC_IFACTORY_H
