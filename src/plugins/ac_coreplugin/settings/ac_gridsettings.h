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

#include <mi_object.h>
#include <ac_core_global.h>

namespace Private {

class AcGridSettingsData;

} // namespace Private

class AC_CORE_EXPORT AcGridSettings : public MiObject
{
    Q_OBJECT
    Q_PROPERTY(bool visible READ visible WRITE setVisible)

public:
    enum PropertyIndex
    {
        Visible = MiObject::PropertyCount,
        PropertyCount
    };

    AcGridSettings(QObject *parent = 0);
    ~AcGridSettings();

    bool visible() const;
    void setVisible(bool visible);

private:
    Q_DISABLE_COPY(AcGridSettings)
    Private::AcGridSettingsData *d;
};

#endif // AC_GRIDSETTINGS_H