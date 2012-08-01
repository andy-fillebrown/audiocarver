/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2012 Andrew Fillebrown.
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

#ifndef AC_CORE_CONSTANTS_H
#define AC_CORE_CONSTANTS_H

#include <qglobal.h>

const qreal DEFAULT_SCOREOBJECT_VOLUME = 0.75f;

const qreal DEFAULT_SCORE_LENGTH = 60.0f;
const qreal DEFAULT_SCORE_STARTTIME = 0.0f;

const bool DEFAULT_GRIDSETTINGS_SNAPENABLED = true;
const bool DEFAULT_GRIDSETTINGS_GRIDSNAPENABLED = true;
const qreal DEFAULT_GRIDSETTINGS_TIMESNAP = 0.125f;
const qreal DEFAULT_GRIDSETTINGS_PITCHSNAP = 1.0f;
const qreal DEFAULT_GRIDSETTINGS_CONTROLSNAP = 0.125f;

const qreal DEFAULT_PROJECTSETTINGS_SAMPLERATE = 48000;
const qreal DEFAULT_PROJECTSETTINGS_CONTROLRATE = 4800;
const qreal DEFAULT_PROJECTSETTINGS_CURVERATE = 48;

const qreal DEFAULT_VIEWSETTINGS_TIMEPOSITION = DEFAULT_SCORE_LENGTH / 2.0f;
const qreal DEFAULT_VIEWSETTINGS_PITCHPOSITION = 63.5f;
const qreal DEFAULT_VIEWSETTINGS_CONTROLPOSITION = 0.5f;

const qreal VIEWSCALE_MIN = 0.75f;
const qreal VIEWSCALE_MAX = 1000.0f;

#endif
