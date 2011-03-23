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

#include "displaysettings.h"

#include <QtCore/QSettings>
#include <QtCore/QString>

static const char * const testKey = "Test";

static const char * const groupPostfix = "DisplaySettings";

using namespace GLEditor;

DisplaySettingsData::DisplaySettingsData()
    :   test(true)
{
}

void DisplaySettings::toSettings(const QString &category, QSettings *s) const
{
    QString group = QLatin1String(groupPostfix);
    if (!category.isEmpty())
        group.insert(0, category);

    s->beginGroup(group);
    s->setValue(QLatin1String(testKey), d.test);
    s->endGroup();
}


void DisplaySettings::fromSettings(const QString &category, const QSettings *s)
{
    // Assign defaults.
    d = DisplaySettingsData();

    QString group = QLatin1String(groupPostfix);
    if (!category.isEmpty())
        group.insert(0, category);
    group += QLatin1Char('/');

    d.test = s->value(group + QLatin1String(testKey), d.test).toBool();
}

bool DisplaySettings::equals(const DisplaySettings &ds) const
{
    return d.test == ds.d.test
        ;
}
