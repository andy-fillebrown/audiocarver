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

#ifndef MI_DATAOBJECTFACTORY_H
#define MI_DATAOBJECTFACTORY_H

#include <aggregate.h>
#include <mi_core_global.h>
#include <mi_fontsettings.h>
#include <mi_objectlist.h>
#include <mi_propertybag.h>
#include <QObject>

class MI_CORE_EXPORT MiDataObjectFactory : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(MiDataObjectFactory)

public:
    explicit MiDataObjectFactory(QObject *parent = 0)
        :   QObject(parent)
    {}

    ~MiDataObjectFactory()
    {}

    virtual QObject *createObject(const QString &className, QObject *parent = 0)
    {
        if ("MiFontSettings" == className)
            return createFontSettings(parent);
        Q_ASSERT(false);
        return 0;
    }

    virtual MiObjectList *createList(const QString &className, QObject *parent = 0)
    {
        Q_UNUSED(className);
        Q_UNUSED(parent);
        Q_ASSERT(false);
        return 0;
    }

protected:
    virtual MiFontSettings *createFontSettings(QObject *parent)
    {
        MiFontSettings *fontSettings = new MiFontSettings(parent);
        addPropertyBagTo(fontSettings);
        return fontSettings;
    }

    void addPropertyBagTo(QObject *object)
    {
        Aggregation::Aggregate *agg = new Aggregation::Aggregate;
        agg->add(object);
        agg->add(createPropertyBag(object));
    }

    virtual MiPropertyBag *createPropertyBag(QObject *object)
    {
        return new MiPropertyBag(object);
    }
};

#endif // MI_DATAOBJECTFACTORY_H
