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

#include "ac_gridsettings.h"

using namespace Private;

namespace Private {

class AcGridSettingsData
{
public:
    bool visible;

    AcGridSettingsData()
        :   visible(false)
    {}
};

} // namespace Private

AcGridSettings::AcGridSettings(QObject *parent)
    :   MiObject(parent)
    ,   d(new AcGridSettingsData)
{}

AcGridSettings::~AcGridSettings()
{
    delete d;
}

bool AcGridSettings::visible() const
{
    return d->visible;
}

void AcGridSettings::setVisible(bool visible)
{
    if (d->visible == visible)
        return;
    d->visible = visible;
    emit propertyChanged(propertyIndex("visible"));
}
