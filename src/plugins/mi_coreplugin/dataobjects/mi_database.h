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

#ifndef MI_DATABASE_H
#define MI_DATABASE_H

#include <mi_object.h>

class MI_CORE_EXPORT MiDatabase : public MiObject
{
    Q_OBJECT
    Q_DISABLE_COPY(MiDatabase)

public:
    MiDatabase(QObject *parent = 0)
        :   MiObject(parent)
    {}

    ~MiDatabase()
    {}

    virtual bool isDatabase() const
    {
        return true;
    }

    virtual void clear()
    {}

//    virtual QString &normalizeClassName(QString &className) const
//    {
//        return className;
//    }

//    virtual QString getUniqueId(MiObject *object, const QString &idHint = QString()) const;
//    virtual QString variantToString(const QVariant &variant) const;
//    virtual QVariant stringToVariant(const QString &string, const QString &type) const;

//    QVariant stringToVariant(const QStringRef &stringRef, const QString &type) const
//    {
//        return stringToVariant(stringRef.toString(), type);
//    }

//    QVariant stringToVariant(const QVariant &variant, const QString &type) const
//    {
//        Q_ASSERT(variant.type() == QVariant::String);
//        return stringToVariant(variant.toString(), type);
//    }
};

#endif // MI_DATABASE_H