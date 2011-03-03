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

#ifndef ROOTOBJECT_H
#define ROOTOBJECT_H

#include "object.h"

namespace Database {

class DATABASE_EXPORT RootObject : public Object
{
    Q_OBJECT

public:
    RootObject(QObject *parent = 0);
    virtual ~RootObject();

    virtual bool isRoot() const { return true; }

    virtual QString &normalizeClassName(QString &className) const;
    virtual QString getUniqueId(Object *object, const QString &idHint = QString()) const;

    virtual Object *createObject(const QString &className) const;

    virtual QString variantToString(const QVariant &variant) const;
    virtual QVariant stringToVariant(const QString &string, const QString &type) const;
    QVariant stringToVariant(const QStringRef &stringRef, const QString &type) const { return stringToVariant(stringRef.toString(), type); }
    QVariant stringToVariant(const QVariant &variant, const QString &type) const { Q_ASSERT(variant.type() == QVariant::String);  return stringToVariant(variant.toString(), type); }

private:
    Q_DISABLE_COPY(RootObject)
};

} // namespace Database

#endif // ROOTOBJECT_H
