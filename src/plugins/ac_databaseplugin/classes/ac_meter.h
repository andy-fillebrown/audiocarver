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

#ifndef AC_METER_H
#define AC_METER_H

#include <mi_object.h>

#include <ac_database_global.h>

namespace Private {

class AcMeterData;

} // namespace Private

class AC_DATABASE_EXPORT AcMeter : public MiObject
{
    Q_OBJECT
    Q_PROPERTY(int duration READ duration WRITE setDuration)
    Q_PROPERTY(int beatsPerMeasure READ beatsPerMeasure WRITE setBeatsPerMeasure)
    Q_PROPERTY(int denominator READ denominator WRITE setDenominator)

public:
    explicit AcMeter(QObject *parent = 0);
    virtual ~AcMeter();

    int duration() const;
    void setDuration(int duration);

    int beatsPerMeasure() const;
    void setBeatsPerMeasure(int beatsPerMeasure);

    int denominator() const;
    void setDenominator(int denominator);

private:
    Q_DISABLE_COPY(AcMeter)
    Private::AcMeterData *d;
};

#endif // AC_METER_H
