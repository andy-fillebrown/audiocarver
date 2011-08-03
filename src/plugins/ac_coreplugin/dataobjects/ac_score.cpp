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

#include "ac_score.h"
#include <ac_gridlinelist.h>
#include <ac_gridsettings.h>
#include <ac_tracklist.h>
#include <ac_viewsettings.h>
#include <mi_fontsettings.h>

AcScorePrivate::AcScorePrivate(AcScoreObject *q)
    :   AcScoreObjectPrivate(q)
    ,   tracks(new AcTrackList(AcScore::TracksIndex))
    ,   timeLines(new AcTimeLineList)
    ,   pitchLines(new AcPitchLineList)
    ,   volumeLines(new AcVolumeLineList)
    ,   settingsObjects(new MiListObject)
    ,   fontSettings(new MiFontSettings)
    ,   gridSettings(new AcGridSettings)
    ,   viewSettings(new AcViewSettings)
{}

void AcScorePrivate::init()
{
    addChild(tracks);
    addChild(timeLines);
    addChild(pitchLines);
    addChild(volumeLines);
    addChild(settingsObjects);
    settingsObjects->addChild(fontSettings);
    settingsObjects->addChild(gridSettings);
    settingsObjects->addChild(viewSettings);
}

static AcScore *instance = 0;

AcScore::AcScore()
    :   AcScoreObject(*(new AcScorePrivate(this)))
{
    Q_D(AcScore);
    d->init();

    ::instance = this;
}

AcScore *AcScore::instance()
{
    return ::instance;
}
