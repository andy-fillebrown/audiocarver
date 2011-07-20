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

#include <mi_database.h>
#include <ac_dataobjectfactory.h>
#include <ac_gridline.h>
#include <ac_gridsettings.h>
#include <ac_track.h>
#include <ac_viewsettings.h>
#include <mi_fontsettings.h>

typedef MiList<QObject> AcSettingsList;

namespace Private {

class AcScoreData
{
public:
    qreal length;
    AcSettingsList *settings;
    AcTrackList *tracks;
    AcGridLinesList *grid;

    MiFontSettings *fontSettings;
    AcGridSettings *gridSettings;
    AcViewSettings *viewSettings;

    AcGridLineList *timeLines;
    AcGridLineList *pitchLines;
    AcGridLineList *controlLines;

    AcScoreData(QObject *q)
        :   length(0)
        ,   settings(new AcSettingsList(q))
        ,   tracks(new AcTrackList(q))
        ,   grid(new AcGridLinesList(q))
        ,   fontSettings(new MiFontSettings)
        ,   gridSettings(new AcGridSettings)
        ,   viewSettings(new AcViewSettings)
        ,   timeLines(new AcGridLineList)
        ,   pitchLines(new AcGridLineList)
        ,   controlLines(new AcGridLineList)
    {
        QObjectList settingsList;
        settingsList.append(fontSettings);
        settingsList.append(gridSettings);
        settingsList.append(viewSettings);
        settings->append(settingsList);

        QList<AcGridLineList*> gridLinesList;
        gridLinesList.append(timeLines);
        gridLinesList.append(pitchLines);
        gridLinesList.append(controlLines);
        grid->append(gridLinesList);
    }
};

} // namespace Private

class AC_CORE_EXPORT AcScore : public MiDatabase
{
    Q_OBJECT
    Q_DISABLE_COPY(AcScore)
    Q_PROPERTY(qreal length READ length WRITE setLength)
    Q_PROPERTY(AcSettingsList* settings READ settings)
    Q_PROPERTY(AcTrackList* tracks READ tracks)
    Q_PROPERTY(AcGridLinesList* grid READ grid)

public:
    enum Properties {
        Length = MiDatabase::PropertyCount,
        Settings,
        Tracks,
        Grid,
        PropertyCount
    };

    explicit AcScore(QObject *parent = 0)
        :   MiDatabase(new AcDataObjectFactory(this), parent)
        ,   d(new Private::AcScoreData(this))
    {}

    AcScore(AcDataObjectFactory *dataObjectFactory, QObject *parent = 0)
        :   MiDatabase(dataObjectFactory, parent)
        ,   d(new Private::AcScoreData(this))
    {}

    AcScore(MiFilerFactory *filerFactory, QObject *parent = 0)
        :   MiDatabase(new AcDataObjectFactory(this), filerFactory, parent)
        ,   d(new Private::AcScoreData(this))
    {}

    AcScore(AcDataObjectFactory *dataObjectFactory, MiFilerFactory *filerFactory, QObject *parent = 0)
        :   MiDatabase(dataObjectFactory, filerFactory, parent)
        ,   d(new Private::AcScoreData(this))
    {}

    virtual ~AcScore()
    {
        delete d;
    }

    qreal length() const
    {
        return d->length;
    }

    void setLength(qreal length)
    {
        if (length < 1.0f)
            length = 1.0f;
        if (d->length == length)
            return;
        beginChangeProperty(Length);
        d->length = length;
        endChangeProperty(Length);
    }

    AcSettingsList *settings() const
    {
        return d->settings;
    }

    AcTrackList *tracks() const
    {
        return d->tracks;
    }

    AcGridLinesList *grid() const
    {
        return d->grid;
    }

    MiFontSettings *fontSettings() const
    {
        return d->fontSettings;
    }

    AcGridSettings *gridSettings() const
    {
        return d->gridSettings;
    }

    AcViewSettings *viewSettings() const
    {
        return d->viewSettings;
    }

    AcGridLineList *timeLines() const
    {
        return d->timeLines;
    }

    AcGridLineList *pitchLines() const
    {
        return d->pitchLines;
    }

    AcGridLineList *controlLines() const
    {
        return d->controlLines;
    }

    virtual void clear()
    {}

private:
    Private::AcScoreData *d;
};

Q_DECLARE_METATYPE(AcSettingsList*)

#endif // AC_SCORE_H
