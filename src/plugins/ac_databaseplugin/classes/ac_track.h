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

class AcNote;
template <typename T> class MiList;

namespace Private {

class AcTrackData;

} // namespace Private

class AC_DATABASE_EXPORT AcTrack : public MiObject
{
    Q_OBJECT
    Q_PROPERTY(MiObjectList* notes READ noteObjects)
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible)
    Q_PROPERTY(qreal volume READ volume WRITE setVolume)

public:
    enum PropertyIndex
    {
        Notes = MiObject::PropertyCount,
        Visible,
        Volume,
        PropertyCount
    };

    AcTrack(QObject *parent = 0);
    virtual ~AcTrack();

    MiList<AcNote> &notes() const;
    bool isVisible() const;
    void setVisible(bool visible);
    qreal volume() const;
    void setVolume(qreal volume);

protected:
    virtual MiObject *createObject(const QString &className);

private:
    Q_DISABLE_COPY(AcTrack)
    Private::AcTrackData *d;

    MiObjectList *noteObjects() const;
};

#endif // AC_TRACK_H
