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

#ifndef GLEDITORCONSTANTS_H
#define GLEDITORCONSTANTS_H

#include <editorplugin/editorconstants.h>

namespace GLEditor {
namespace Constants {

const char * const G_VIEW                    = PRO_NAME_STR".Group.View";

const char * const G_VIEW_ALL                = PRO_NAME_STR".Group.View.All";
const char * const G_VIEW_CAMERA             = PRO_NAME_STR".Group.View.Camera";
const char * const G_VIEW_PROJECTION         = PRO_NAME_STR".Group.View.Projection";
const char * const G_VIEW_TRANSPARENCY       = PRO_NAME_STR".Group.View.Transparency";

const char * const G_WINDOW_SPLIT            = PRO_NAME_STR".Group.Window.Split";

const char * const M_VIEW                    = PRO_NAME_STR".Menu.View";
const char * const M_VIEW_PROJECTION         = PRO_NAME_STR".Menu.View.Projection";
const char * const M_VIEW_TRANSPARENCY       = PRO_NAME_STR".Menu.View.Transparency";

const char * const VIEWALL                   = PRO_NAME_STR".ViewAll";
const char * const VIEWZOOM                  = PRO_NAME_STR".ViewZoom";
const char * const VIEWPAN                   = PRO_NAME_STR".ViewPan";
const char * const VIEWROTATE                = PRO_NAME_STR".ViewRotate";
const char * const VIEWPARALLEL              = PRO_NAME_STR".ViewParallel";
const char * const VIEWPERSPECTIVE           = PRO_NAME_STR".ViewPerspective";
const char * const VIEWTRANSPARENCYNONE      = PRO_NAME_STR".ViewTransparencyNone";
const char * const VIEWTRANSPARENCYSCREEN    = PRO_NAME_STR".ViewTransparencyScreen";
const char * const VIEWTRANSPARENCYFULL      = PRO_NAME_STR".ViewTransparencyFull";

const char * const WINDOWSPLITHORIZONTAL     = PRO_NAME_STR".WindowSplit";
const char * const WINDOWSPLITVERTICAL       = PRO_NAME_STR".WindowSplitSideBySide";
const char * const WINDOWREMOVECURRENTSPLIT  = PRO_NAME_STR".WindowRemoveCurrentSplit";
const char * const WINDOWREMOVEALLSPLITS     = PRO_NAME_STR".WindowRemoveAllSplits";

const char * const SETTINGS_CATEGORY_3D      = "A.GLEditor";
const char * const SETTINGS_CATEGORY_3D_ICON = ":/gleditor/images/3d-box.png";
const char * const SETTINGS_TR_CATERGORY_3D  = QT_TRANSLATE_NOOP("GLEditor", "3D");
const char * const SETTINGS_ID_3D            = "A.3D";

} // namespace Constants
} // namespace GLEditor

#endif // GLEDITORCONSTANTS_H
