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

#include <ac_note.h>

namespace Private {

class AcTrackData
{
public:
    AcNoteList *notes;
    bool visible;
    qreal volume;

    AcTrackData(QObject *q)
        :   notes(new AcNoteList(q))
        ,   visible(true)
        ,   volume(1.0f)
    {}
};

} // namespace Private

class AC_CORE_EXPORT AcTrack : public MiObject
{
    Q_OBJECT
    Q_DISABLE_COPY(AcTrack)
    Q_PROPERTY(MiObjectList* notes READ notes)
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible)
    Q_PROPERTY(qreal volume READ volume WRITE setVolume)

public:
    enum Properties {
        Notes = MiObject::PropertyCount,
        Visible,
        Volume,
        PropertyCount
    };

    explicit AcTrack(QObject *parent = 0)
        :   MiObject(parent)
        ,   d(new Private::AcTrackData(this))
    {}

    virtual ~AcTrack()
    {
        delete d;
    }

    AcNoteList *notes() const
    {
        return d->notes;
    }

    bool isVisible() const
    {
        return d->visible;
    }

    void setVisible(bool visible)
    {
        if (d->visible == visible)
            return;
        beginChangeProperty(Visible);
        d->visible = visible;
        endChangeProperty(Visible);
    }

    qreal volume() const
    {
        return d->volume;
    }

    void setVolume(qreal volume)
    {
        if (volume < 0.0f)
            volume = 0.0f;
        else if (1.0f < volume)
            volume = 1.0f;
        if (d->volume == volume)
            return;
        beginChangeProperty(Volume);
        d->volume = volume;
        endChangeProperty(Volume);
    }

private:
    Private::AcTrackData *d;
};

typedef MiList<AcTrack> AcTrackList;

Q_DECLARE_METATYPE(AcTrackList*)

#endif // AC_TRACK_H
