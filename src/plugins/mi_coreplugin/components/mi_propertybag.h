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

#include <QObject>
#include <mi_core_global.h>

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

class MI_CORE_EXPORT MiPropertyBag : public QObject
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

    QString className() const;
    int propertyCount() const;
    int propertyIndex(const QString &name) const;
    QString propertyName(int i) const;
    QString propertyType(int i) const;
    bool isPropertyWritable(int i) const;
    QVariant propertyValue(int i) const;
    void setPropertyValue(int i, const QVariant &value);

signals:
    friend class MiObject;
    void propertyAboutToBeChanged(const QVariant &value, int propertyIndex);
    void propertyChanged(const QVariant &value, int propertyIndex);

private:
    Q_DISABLE_COPY(MiPropertyBag)
    Private::MiPropertyBagData *d;
};

#endif // MI_PROPERTYBAG_H
