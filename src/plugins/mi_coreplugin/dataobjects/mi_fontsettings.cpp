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

#include "mi_fontsettings.h"
#include <QFont>

using namespace Private;

namespace Private {

class MiFontSettingsPrivate : public MiObjectPrivate
{
public:
    QFont font;

    MiFontSettingsPrivate(MiFontSettings *q)
        :   MiObjectPrivate(q)
        ,   font("Arial", 8)
    {}

    virtual ~MiFontSettingsPrivate()
    {}
};

} // namespace Private

MiFontSettings::MiFontSettings(QObject *parent)
    :   MiObject(*(new MiFontSettingsPrivate(this)), parent)
{}

MiFontSettings::~MiFontSettings()
{}

QString MiFontSettings::family() const
{
    Q_D(const Private::MiFontSettings);
    return d->font.family();
}

void MiFontSettings::setFamily(const QString &family)
{
    Q_D(MiFontSettings);
    if (d->font.family() == family)
        return;
    beginChangeProperty(Family);
    d->font.setFamily(family);
    endChangeProperty(Family);
}

int MiFontSettings::pointSize() const
{
    Q_D(const Private::MiFontSettings);
    return d->font.pointSize();
}

void MiFontSettings::setPointSize(int size)
{
    Q_D(MiFontSettings);
    if (d->font.pointSize() == size)
        return;
    beginChangeProperty(PointSize);
    d->font.setPointSize(size);
    endChangeProperty(PointSize);
}

const QFont &MiFontSettings::font() const
{
    Q_D(const Private::MiFontSettings);
    return d->font;
}
