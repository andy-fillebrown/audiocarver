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

#ifndef EDITOR3DCONSTANTS_H
#define EDITOR3DCONSTANTS_H

#include <editorplugin/editorconstants.h>

namespace Editor3D {
namespace Constants {

const char * const G_VIEW                 = PRO_NAME_STR".Group.View";

const char * const G_VIEW_ALL             = PRO_NAME_STR".Group.View.All";
const char * const G_VIEW_CAMERA          = PRO_NAME_STR".Group.View.Camera";
const char * const G_VIEW_PROJECTION      = PRO_NAME_STR".Group.View.Projection";
const char * const G_VIEW_TRANSPARENCY    = PRO_NAME_STR".Group.View.Transparency";

const char * const M_VIEW                 = PRO_NAME_STR".Menu.View";
const char * const M_VIEW_PROJECTION      = PRO_NAME_STR".Menu.View.Projection";
const char * const M_VIEW_TRANSPARENCY    = PRO_NAME_STR".Menu.View.Transparency";

const char * const VIEWALL                = PRO_NAME_STR".ViewAll";
const char * const VIEWZOOM               = PRO_NAME_STR".ViewZoom";
const char * const VIEWPAN                = PRO_NAME_STR".ViewPan";
const char * const VIEWROTATE             = PRO_NAME_STR".ViewRotate";
const char * const VIEWPARALLEL           = PRO_NAME_STR".ViewParallel";
const char * const VIEWPERSPECTIVE        = PRO_NAME_STR".ViewPerspective";
const char * const VIEWTRANSPARENCYNONE   = PRO_NAME_STR".ViewTransparencyNone";
const char * const VIEWTRANSPARENCYSCREEN = PRO_NAME_STR".ViewTransparencyScreen";
const char * const VIEWTRANSPARENCYFULL   = PRO_NAME_STR".ViewTransparencyFull";

} // namespace Constants
} // namespace Editor3D

#endif // EDITOR3DCONSTANTS_H
