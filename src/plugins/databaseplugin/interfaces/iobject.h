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

QT_BEGIN_NAMESPACE
class QXmlStreamReader;
QT_END_NAMESPACE

namespace Database {

class IRootObject;

class IObject : public QObject
{
    Q_OBJECT

public:
    IObject();
    virtual ~IObject();

    virtual void read(QXmlStreamReader &in) = 0;
    virtual void write(QXmlStreamReader &out) = 0;

    virtual IRootObject *rootObject() const = 0;
};

} // namespace Database

#endif // IOBJECT_H
