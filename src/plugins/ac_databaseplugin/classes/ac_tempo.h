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

#ifndef AC_TEMPO_H
#define AC_TEMPO_H

#include <mi_object.h>

#include <ac_database_global.h>

namespace Private {

class AcTempoData;

} // namespace Private

class AC_DATABASE_EXPORT AcTempo : public MiObject
{
    Q_OBJECT
    Q_PROPERTY(qreal startTime READ startTime WRITE setStartTime)
    Q_PROPERTY(qreal beatsPerMinute READ beatsPerMinute WRITE setBeatsPerMinute)

public:
    explicit AcTempo(QObject *parent = 0);
    virtual ~AcTempo();

    qreal startTime() const;
    void setStartTime(qreal startTime);

    qreal beatsPerMinute() const;
    void setBeatsPerMinute(qreal beatsPerMinute);

private:
    Q_DISABLE_COPY(AcTempo)
    Private::AcTempoData *d;
};

#endif // AC_TEMPO_H
