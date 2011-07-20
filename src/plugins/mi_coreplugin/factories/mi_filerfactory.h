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

#ifndef MI_FILERFACTORY_H
#define MI_FILERFACTORY_H

#include <mi_core_global.h>
#include <QObject>

class MI_CORE_EXPORT MiFilerFactory : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(MiFilerFactory)

public:
    explicit MiFilerFactory(QObject *parent = 0)
        :   QObject(parent)
    {}

    ~MiFilerFactory()
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

#endif // MI_FILERFACTORY_H
