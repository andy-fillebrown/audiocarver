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

#ifndef MI_IPROPERTYBAG_H
#define MI_IPROPERTYBAG_H

#include <QObject>
#include <mi_core_global.h>

class MI_CORE_EXPORT IPropertyBag : public QObject
{
    Q_OBJECT

public:
    IPropertyBag() {}
    virtual ~IPropertyBag() {}

    virtual QString className() const = 0;
    virtual int propertyCount() const = 0;
    virtual int propertyIndex(const QString &name) const = 0;
    virtual QString propertyName(int i) const = 0;
    virtual QString propertyType(int i) const = 0;
    virtual bool isPropertyWritable(int i) const = 0;
    virtual QVariant propertyValue(int i) const = 0;
    virtual void setPropertyValue(int i, const QVariant &value) = 0;

private:
    Q_DISABLE_COPY(IPropertyBag)
};

#endif // MI_IPROPERTYBAG_H
