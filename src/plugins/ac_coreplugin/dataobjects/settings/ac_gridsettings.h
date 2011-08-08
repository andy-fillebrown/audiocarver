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

#ifndef AC_GRIDSETTINGS_H
#define AC_GRIDSETTINGS_H

#include <ac_core_global.h>
#include <mi_scopedchange.h>

class AcGridSettingsPrivate : public MiObjectPrivate
{
public:
    bool visible;

    AcGridSettingsPrivate(MiObject *q)
        :   MiObjectPrivate(q)
        ,   visible(true)
    {}

    ~AcGridSettingsPrivate()
    {}
};

class AC_CORE_EXPORT AcGridSettings : public MiObject
{
    Q_OBJECT
    Q_PROPERTY(bool visible READ visible WRITE setVisible)

public:
    enum PropertyIndex {
        VisibleIndex = MiObject::PropertyCount,
        PropertyCount
    };

    AcGridSettings()
        :   MiObject(*(new AcGridSettingsPrivate(this)))
    {}

    ~AcGridSettings()
    {}

    bool visible() const
    {
        Q_D(const AcGridSettings);
        return d->visible;
    }

    void setVisible(bool visible)
    {
        Q_D(AcGridSettings);
        if (d->visible == visible)
            return;
        changing(VisibleIndex);
        d->visible = visible;
    }

private:
    Q_DISABLE_COPY(AcGridSettings)
    Q_DECLARE_PRIVATE(AcGridSettings)
};

#endif // AC_GRIDSETTINGS_H
