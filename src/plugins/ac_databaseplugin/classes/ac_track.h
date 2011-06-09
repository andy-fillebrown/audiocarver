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

#ifndef AC_TRACK_H
#define AC_TRACK_H

#include <mi_object.h>
#include <ac_database_global.h>

namespace Private {

class AcTrackData;

} // namespace Private

class AC_DATABASE_EXPORT AcTrack : public MiObject
{
    Q_OBJECT
    Q_PROPERTY(MiObjectList* notes READ notes)
    Q_PROPERTY(bool visible READ isVisible WRITE setVisibility)
    Q_PROPERTY(qreal volume READ volume WRITE setVolume)

public:
    AcTrack(QObject *parent = 0);
    virtual ~AcTrack();

    MiObjectList *notes() const;
    bool isVisible() const;
    void setVisibility(bool visible);
    qreal volume() const;
    void setVolume(qreal volume);

protected:
    virtual MiObject *createObject(const QString &className);
    virtual MiObject *findObject(const QString &className) const;

private:
    Q_DISABLE_COPY(AcTrack)
    Private::AcTrackData *d;
};

#endif // AC_TRACK_H
