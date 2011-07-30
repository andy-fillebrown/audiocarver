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

#ifndef AC_SCORE_H
#define AC_SCORE_H

#include <ac_scoreobject.h>

class AcGridLineList;
class AcGridSettings;
class AcTrackList;
class AcViewSettings;
class MiListObject;

class AcScorePrivate : public AcScoreObjectPrivate
{
public:
    qreal length;
    AcTrackList *tracks;
    MiListObject *gridLineLists;
    AcGridLineList *timeLines;
    AcGridLineList *pitchLines;
    AcGridLineList *volumeLines;
    MiListObject *settingsObjects;
    AcGridSettings *gridSettings;
    AcViewSettings *viewSettings;

    AcScorePrivate(AcScoreObject *q);

    virtual ~AcScorePrivate()
    {}

    void init();
};

class AcScore : public AcScoreObject
{
    Q_OBJECT
    Q_PROPERTY(qreal length READ length WRITE setLength)
    Q_PROPERTY(AcTrackList* tracks READ tracks)
    Q_PROPERTY(MiListObject* gridLines READ gridLineLists)
    Q_PROPERTY(MiListObject* settings READ settingsList)

public:
    enum PropertyIndex {
        LengthIndex = AcScoreObject::PropertyCount,
        TracksIndex,
        PropertyCount
    };

    AcScore()
        :   AcScoreObject(*(new AcScorePrivate(this)))
    {
        Q_D(AcScore);
        d->init();
    }

    virtual ~AcScore()
    {}

    qreal length() const
    {
        Q_D(const AcScore);
        return d->length;
    }

    void setLength(qreal length)
    {
        Q_D(AcScore);
        if (length < 0.0f)
            length = 0.0f;
        if (length == d->length)
            return;
        changing(LengthIndex);
        d->length = length;
    }

    AcTrackList *tracks() const
    {
        Q_D(const AcScore);
        return d->tracks;
    }

    AcGridLineList *timeLines() const
    {
        Q_D(const AcScore);
        return d->timeLines;
    }

    AcGridLineList *pitchLines() const
    {
        Q_D(const AcScore);
        return d->pitchLines;
    }

    AcGridLineList *volumeLines() const
    {
        Q_D(const AcScore);
        return d->volumeLines;
    }

private:
    Q_DISABLE_COPY(AcScore)
    Q_DECLARE_PRIVATE(AcScore)

    MiListObject *gridLineLists() const
    {
        Q_D(const AcScore);
        return d->gridLineLists;
    }

    MiListObject *settingsList() const
    {
        Q_D(const AcScore);
        return d->settingsObjects;
    }
};

#endif // AC_SCORE_H
