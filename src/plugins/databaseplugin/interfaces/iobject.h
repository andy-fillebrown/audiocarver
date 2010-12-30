/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2010 Andrew Fillebrown.
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

#ifndef IOBJECT_H
#define IOBJECT_H

#include <QtCore/QObject>

namespace Database {

class IDataObject;
class IReader;
class IRootObject;
class IWriter;

class IObject : public QObject
{
    Q_OBJECT

public:
    IObject() {}
    virtual ~IObject() {}

    virtual IRootObject *root() const = 0;
    virtual IDataObject *parent() const = 0;

    virtual int childCount() const = 0;
    virtual IObject *childAt(int i) = 0;

    virtual int propertyCount() const = 0;
    virtual QString propertyName(int propertyIndex) const = 0;
    virtual QVariant propertyValue(const QString &propertyName) const = 0;
    virtual void setPropertyValue(const QString &propertyName, const QVariant &value) = 0;

    virtual void read(IReader *in) = 0;
    virtual void write(IWriter *out) = 0;
};

} // namespace Database

#endif // IOBJECT_H
