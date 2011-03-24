/**************************************************************************
**
** This file is part of Qt Creator
**
** Copyright (c) 2011 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef CORECONSTANTS_H
#define CORECONSTANTS_H

#include <QtCore/QtGlobal>

namespace Core {
namespace Constants {

#include "pro_version.h"

#define STRINGIFY_INTERNAL(x) #x
#define STRINGIFY(x) STRINGIFY_INTERNAL(x)

#define PRO_VERSION STRINGIFY(PRO_VERSION_MAJOR) \
    "." STRINGIFY(PRO_VERSION_MINOR) \
    "." STRINGIFY(PRO_VERSION_RELEASE)

const char * const PRO_VERSION_LONG                    = PRO_VERSION;
const char * const PRO_AUTHOR                          = PRO_AUTHOR_NOSPACE_STR;
const char * const PRO_YEAR                            = PRO_YEAR_STR;

#ifdef PRO_VERSION_DESCRIPTION
const char * const PROVERSION_DESCRIPTION_STR          = STRINGIFY(PRO_VERSION_DESCRIPTION);
#else
const char * const PRO_VERSION_DESCRIPTION_STR         = "";
#endif

#ifdef PRO_REVISION
const char * const PRO_REVISION_STR                    = STRINGIFY(PRO_REVISION);
#else
const char * const PRO_REVISION_STR                    = "";
#endif

#undef PRO_VERSION
#undef STRINGIFY
#undef STRINGIFY_INTERNAL

const char * const C_GLOBAL                            = "Global Context";

const char * const MENU_BAR                            = PRO_NAME_STR".MenuBar";

const char * const G_FILE                              = PRO_NAME_STR".Group.File";
const char * const G_TOOLS                             = PRO_NAME_STR".Group.Tools";
const char * const G_WINDOW                            = PRO_NAME_STR".Group.Window";
const char * const G_HELP                              = PRO_NAME_STR".Group.Help";

const char * const G_DEFAULT_ONE                       = PRO_NAME_STR".Group.Default.One";
const char * const G_DEFAULT_TWO                       = PRO_NAME_STR".Group.Default.Two";
const char * const G_DEFAULT_THREE                     = PRO_NAME_STR".Group.Default.Three";

const char * const G_FILE_OTHER                        = PRO_NAME_STR".Group.File.Other";

const char * const G_WINDOW_SIZE                       = PRO_NAME_STR".Group.Window.Size";
const char * const G_WINDOW_OTHER                      = PRO_NAME_STR".Group.Window.Other";

const char * const G_HELP_ABOUTPLUGINS                 = PRO_NAME_STR".Group.Help.AboutPlugins";

const char * const M_FILE                              = PRO_NAME_STR".Menu.File";
const char * const M_TOOLS                             = PRO_NAME_STR".Menu.Tools";
const char * const M_WINDOW                            = PRO_NAME_STR".Menu.Window";
const char * const M_HELP                              = PRO_NAME_STR".Menu.Help";

const char * const EXIT                                = PRO_NAME_STR".Exit";

const char * const OPTIONS                             = PRO_NAME_STR".Options";
const char * const TOGGLE_FULLSCREEN                   = PRO_NAME_STR".ToggleFullScreen";

const char * const MINIMIZE_WINDOW                     = PRO_NAME_STR".MinimizeWindow";
const char * const ZOOM_WINDOW                         = PRO_NAME_STR".ZoomWindow";

const char * const ABOUTPLUGINS                        = PRO_NAME_STR".AboutPlugins";

const char * const ICON_PROLOGO_32                     = ":/core/images/project_logo_32.png";
const char * const ICON_PROLOGO_128                    = ":/core/images/project_logo_128.png";
const char * const ICON_RESET                          = ":/core/images/reset.png";

const char * const SETTINGS_CATEGORY_ENVIRONMENT       = "A.Environment";
const char * const SETTINGS_CATEGORY_ENVIRONMENT_ICON  = ":/core/images/category_environment.png";

const char * const SETTINGS_TR_CATEGORY_ENVIRONMENT    = QT_TRANSLATE_NOOP("Core", "Environment");
const char * const SETTINGS_ID_ENVIRONMENT_GENERAL     = "A.Environment.General";
const char * const SETTINGS_ID_ENVIRONMENT_KEYBOARD    = "B.Environment.Keyboard";

const char * const ALL_FILES_FILTER                    = QT_TRANSLATE_NOOP("Core", "All Files (*)");

const int TARGET_ICON_SIZE                             = 32;

} // namespace Constants
} // namespace Core

#endif // CORECONSTANTS_H
