/**************************************************************************
**
** This file is part of Qt Creator
**
** Copyright (c) 2010 Nokia Corporation and/or its subsidiary(-ies).
**
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** Commercial Usage
**
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
**
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at http://qt.nokia.com/contact.
**
**************************************************************************/

#ifndef AC_EDITORCONSTANTS_H
#define AC_EDITORCONSTANTS_H

#include <coreplugin/coreconstants.h>

namespace AudioCarver {
namespace Constants {

const char * const G_VIEW                  = PRO_NAME_STR".Group.View";

const char * const G_VIEW_ALL              = PRO_NAME_STR".Group.View.All";
const char * const G_VIEW_PRESET           = PRO_NAME_STR".Group.View.Preset";
const char * const G_VIEW_CAMERA           = PRO_NAME_STR".Group.View.Camera";
const char * const G_VIEW_PROJECTION       = PRO_NAME_STR".Group.View.Projection";
const char * const G_VIEW_SCALE            = PRO_NAME_STR".Group.View.Scale";
const char * const G_VIEW_TRANSPARENCY     = PRO_NAME_STR".Group.View.Transparency";

const char * const G_HELP_ABOUTAUDIOCARVER = PRO_NAME_STR".Group.Help.AboutAudioCarver";

const char * const M_VIEW                  = PRO_NAME_STR".Menu.View";
const char * const M_VIEW_PROJECTION       = PRO_NAME_STR".Menu.View.Projection";
const char * const M_VIEW_SCALE            = PRO_NAME_STR".Menu.View.Scale";
const char * const M_VIEW_TRANSPARENCY     = PRO_NAME_STR".Menu.View.Transparency";

const char * const VIEWALL                 = PRO_NAME_STR".ViewAll";
const char * const VIEWFRONT               = PRO_NAME_STR".ViewFront";
const char * const VIEWSIDE                = PRO_NAME_STR".ViewSide";
const char * const VIEWBOTTOM              = PRO_NAME_STR".ViewBottom";
const char * const VIEWZOOM                = PRO_NAME_STR".ViewZoom";
const char * const VIEWPAN                 = PRO_NAME_STR".ViewPan";
const char * const VIEWROTATE              = PRO_NAME_STR".ViewRotate";
const char * const VIEWPARALLEL            = PRO_NAME_STR".ViewParallel";
const char * const VIEWPERSPECTIVE         = PRO_NAME_STR".ViewPerspective";
const char * const VIEWSCALEINCREASEX      = PRO_NAME_STR".ViewScaleIncreaseX";
const char * const VIEWSCALEDECREASEX      = PRO_NAME_STR".ViewScaleDecreaseX";
const char * const VIEWSCALEINCREASEZ      = PRO_NAME_STR".ViewScaleIncreaseZ";
const char * const VIEWSCALEDECREASEZ      = PRO_NAME_STR".ViewScaleDecreaseZ";
const char * const VIEWTRANSPARENCYNONE    = PRO_NAME_STR".ViewTransparencyNone";
const char * const VIEWTRANSPARENCYSCREEN  = PRO_NAME_STR".ViewTransparencyScreen";
const char * const VIEWTRANSPARENCYFULL    = PRO_NAME_STR".ViewTransparencyFull";

const char * const ABOUTAUDIOCARVER        = PRO_NAME_STR".About"PRO_NAME_STR;


} // namespace Constants
} // namespace AudioCarver

#endif // AC_EDITORCONSTANTS_H
