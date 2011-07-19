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

#ifndef MI_PROPERTYBAG_H
#define MI_PROPERTYBAG_H

#include <mi_ipropertybag.h>

namespace Private {

class MiPropertyBagData
{
public:
    QObject *object;

    MiPropertyBagData(QObject *object)
        :   object(object)
    {}
};

} // namespace Private

class MI_CORE_EXPORT MiPropertyBag : public IPropertyBag
{
    Q_OBJECT

public:
    MiPropertyBag(QObject *object)
        :   d(new Private::MiPropertyBagData(object))
    {}

    virtual ~MiPropertyBag()
    {
        delete d;
    }

    void setObject(QObject *object)
    {
        d->object = object;
    }

    virtual QString className() const;
    virtual int propertyCount() const;
    virtual int propertyIndex(const QString &name) const;
    virtual QString propertyName(int i) const;
    virtual QString propertyType(int i) const;
    virtual bool isPropertyWritable(int i) const;
    virtual QVariant propertyValue(int i) const;
    virtual void setPropertyValue(int i, const QVariant &value);

private:
    Q_DISABLE_COPY(MiPropertyBag)
    Private::MiPropertyBagData *d;
};

#endif // MI_PROPERTYBAG_H
