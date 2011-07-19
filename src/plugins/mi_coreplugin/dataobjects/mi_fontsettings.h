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

#ifndef MI_FONTSETTINGS_H
#define MI_FONTSETTINGS_H

#include <mi_object.h>

namespace Private {

class MiFontSettingsPrivate : public MiObjectPrivate
{
public:
    QString family;
    int pointSize;

    MiFontSettingsPrivate(MiObject *q)
        :   MiObjectPrivate(q)
        ,   family("Arial")
        ,   pointSize(8)
    {}

    virtual ~MiFontSettingsPrivate()
    {}
};

} // namespace Private

class MI_CORE_EXPORT MiFontSettings : public MiObject
{
    Q_OBJECT
    Q_DISABLE_COPY(MiFontSettings)
    Q_DECLARE_PRIVATE(Private::MiFontSettings)
    Q_PROPERTY(QString family READ family WRITE setFamily)
    Q_PROPERTY(int pointSize READ pointSize WRITE setPointSize)

public:
    enum {
        Family = MiObject::PropertyCount,
        PointSize,
        PropertyCount
    };

    explicit MiFontSettings(QObject *parent = 0)
        :   MiObject(*(new Private::MiFontSettingsPrivate(this)), parent)
    {}

    virtual ~MiFontSettings()
    {}

    const QString &family() const
    {
        Q_D(const Private::MiFontSettings);
        return d->family;
    }

    void setFamily(const QString &family)
    {
        Q_D(Private::MiFontSettings);
        if (d->family == family)
            return;
        beginChangeProperty(Family);
        d->family = family;
        endChangeProperty(Family);
    }

    int pointSize() const
    {
        Q_D(const Private::MiFontSettings);
        return d->pointSize;
    }

    void setPointSize(int pointSize)
    {
        Q_D(Private::MiFontSettings);
        if (pointSize < 1)
            pointSize = 1;
        if (d->pointSize == pointSize)
            return;
        beginChangeProperty(PointSize);
        d->pointSize = pointSize;
        endChangeProperty(PointSize);
    }
};

#endif // MI_FONT_H
