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

#ifndef AC_VIEWSETTINGS_H
#define AC_VIEWSETTINGS_H

#include <mi_object.h>
#include <ac_database_global.h>

namespace Private {

class AcViewSettingsData;

} // namespace Private

class AC_DATABASE_EXPORT AcViewSettings : public MiObject
{
    Q_OBJECT
    Q_PROPERTY(qreal positionX READ positionX WRITE setPositionX)
    Q_PROPERTY(qreal positionY READ positionY WRITE setPositionY)
    Q_PROPERTY(qreal scaleX READ scaleX WRITE setScaleX)
    Q_PROPERTY(qreal scaleY READ scaleY WRITE setScaleY)

public:
    AcViewSettings(QObject *parent = 0);
    ~AcViewSettings();

    qreal positionX() const;
    void setPositionX(qreal positionX);
    qreal positionY() const;
    void setPositionY(qreal positionY);
    qreal scaleX() const;
    void setScaleX(qreal scaleX);
    qreal scaleY() const;
    void setScaleY(qreal scaleY);

private:
    Q_DISABLE_COPY(AcViewSettings)
    Private::AcViewSettingsData *d;
};

#endif // AC_VIEWSETTINGS_H
