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
    Q_PROPERTY(qreal timePosition READ timePosition WRITE setTimePosition)
    Q_PROPERTY(qreal pitchPosition READ pitchPosition WRITE setPitchPosition)
    Q_PROPERTY(qreal valuePosition READ valuePosition WRITE setValuePosition)
    Q_PROPERTY(qreal timeScale READ timeScale WRITE setTimeScale)
    Q_PROPERTY(qreal pitchScale READ pitchScale WRITE setPitchScale)
    Q_PROPERTY(qreal valueScale READ valueScale WRITE setValueScale)

public:
    AcViewSettings(QObject *parent = 0);
    ~AcViewSettings();

    qreal timePosition() const;
    void setTimePosition(qreal position);
    qreal pitchPosition() const;
    void setPitchPosition(qreal position);
    qreal valuePosition() const;
    void setValuePosition(qreal position);
    qreal timeScale() const;
    void setTimeScale(qreal scale);
    qreal pitchScale() const;
    void setPitchScale(qreal scale);
    qreal valueScale() const;
    void setValueScale(qreal scale);

private:
    Q_DISABLE_COPY(AcViewSettings)
    Private::AcViewSettingsData *d;
};

#endif // AC_VIEWSETTINGS_H
