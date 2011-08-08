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
class MiFontSettings;
class MiListObject;

class AcScorePrivate : public AcScoreObjectPrivate
{
public:
    qreal length;
    AcTrackList *tracks;
    AcGridLineList *timeLines;
    AcGridLineList *pitchLines;
    AcGridLineList *volumeLines;
    MiListObject *settingsObjects;
    MiFontSettings *fontSettings;
    AcGridSettings *gridSettings;
    AcViewSettings *viewSettings;

    AcScorePrivate(AcScoreObject *q);

    ~AcScorePrivate()
    {}

    void init();
};

class AC_CORE_EXPORT AcScore : public AcScoreObject
{
    Q_OBJECT
    Q_PROPERTY(qreal length READ length WRITE setLength)
    Q_PROPERTY(AcTrackList* tracks READ tracks)
    Q_PROPERTY(AcGridLineList* timeLines READ timeLines)
    Q_PROPERTY(AcGridLineList* pitchLines READ pitchLines)
    Q_PROPERTY(AcGridLineList* volumeLines READ volumeLines)
    Q_PROPERTY(MiListObject* settings READ settingsList)

public:
    enum PropertyIndex {
        LengthIndex = AcScoreObject::PropertyCount,
        TracksIndex,
        TimeLinesIndex,
        PitchLinesIndex,
        VolumeLinesIndex,
        SettingsIndex,
        PropertyCount
    };

    AcScore();

    ~AcScore()
    {}

    static AcScore *instance();

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

    MiFontSettings *fontSettings() const
    {
        Q_D(const AcScore);
        return d->fontSettings;
    }

    AcGridSettings *gridSettings() const
    {
        Q_D(const AcScore);
        return d->gridSettings;
    }

    AcViewSettings *viewSettings() const
    {
        Q_D(const AcScore);
        return d->viewSettings;
    }

private:
    Q_DISABLE_COPY(AcScore)
    Q_DECLARE_PRIVATE(AcScore)

    MiListObject *settingsList() const
    {
        Q_D(const AcScore);
        return d->settingsObjects;
    }
};

#endif // AC_SCORE_H
