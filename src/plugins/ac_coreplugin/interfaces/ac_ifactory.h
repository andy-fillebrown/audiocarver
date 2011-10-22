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

#ifndef AC_IFACTORY_H
#define AC_IFACTORY_H

#include <ac_object.h>

class IFileReader;
class IFileWriter;

class IObjectFactory : public QObject
{
    Q_OBJECT

public:
    IObjectFactory();

    static IObjectFactory *instance();

    virtual Object *create(int type) const = 0;

    template <typename T> T *create() { return qobject_cast<T*>(create(T::Type)); }

private:
    Q_DISABLE_COPY(IObjectFactory)
};

class IFilerFactory : public QObject
{
    Q_OBJECT

public:
    IFilerFactory();

    static IFilerFactory *instance();

    virtual IFileReader *createReader(int type) const = 0;
    virtual IFileWriter *createWriter(int type) const = 0;
};

#endif // AC_IFACTORY_H
