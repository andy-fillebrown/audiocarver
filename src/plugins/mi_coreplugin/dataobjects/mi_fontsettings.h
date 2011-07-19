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

class QFont;

namespace Private {

class MiFontSettingsPrivate;

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

    MiFontSettings(QObject *parent = 0);
    virtual ~MiFontSettings();

    QString family() const;
    void setFamily(const QString &family);
    int pointSize() const;
    void setPointSize(int size);

    const QFont &toQFont() const;
};

#endif // MI_FONT_H
