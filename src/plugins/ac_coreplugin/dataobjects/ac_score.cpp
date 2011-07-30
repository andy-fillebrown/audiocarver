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

AcScorePrivate::AcScorePrivate(AcScoreObject *q)
    :   AcScoreObjectPrivate(q)
    ,   tracks(new AcTrackList)
    ,   gridLineLists(new MiListObject)
    ,   timeLines(new AcTimeLineList)
    ,   pitchLines(new AcPitchLineList)
    ,   volumeLines(new AcVolumeLineList)
    ,   settingsObjects(new MiListObject)
    ,   gridSettings(new AcGridSettings)
    ,   viewSettings(new AcViewSettings)
{}

void AcScorePrivate::init()
{
    addChild(tracks);
    addChild(gridLineLists);
    gridLineLists->addChild(timeLines);
    gridLineLists->addChild(pitchLines);
    gridLineLists->addChild(volumeLines);
    addChild(settingsObjects);
    settingsObjects->addChild(gridSettings);
    settingsObjects->addChild(viewSettings);
}
