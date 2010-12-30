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

const char * const PRO_VERSION_LONG      = PRO_VERSION;
const char * const PRO_AUTHOR            = PRO_AUTHOR_NOSPACE_STR;
const char * const PRO_YEAR              = PRO_YEAR_STR;

#ifdef PRO_VERSION_DESCRIPTION
const char * const PROVERSION_DESCRIPTION_STR = STRINGIFY(PRO_VERSION_DESCRIPTION);
#else
const char * const PRO_VERSION_DESCRIPTION_STR = "";
#endif

#ifdef PRO_REVISION
const char * const PRO_REVISION_STR      = STRINGIFY(PRO_REVISION);
#else
const char * const PRO_REVISION_STR      = "";
#endif

#undef PRO_VERSION
#undef STRINGIFY
#undef STRINGIFY_INTERNAL

//menubar
const char * const MENU_BAR              = PRO_NAME_STR".MenuBar";

//menus
const char * const M_FILE                = PRO_NAME_STR".Menu.File";
const char * const M_EDIT                = PRO_NAME_STR".Menu.Edit";
const char * const M_EDIT_ADVANCED       = PRO_NAME_STR".Menu.Edit.Advanced";
const char * const M_TOOLS               = PRO_NAME_STR".Menu.Tools";
const char * const M_WINDOW              = PRO_NAME_STR".Menu.Window";
const char * const M_WINDOW_PANES        = PRO_NAME_STR".Menu.Window.Panes";
const char * const M_WINDOW_VIEWS        = PRO_NAME_STR".Menu.Window.Views";
const char * const M_HELP                = PRO_NAME_STR".Menu.Help";

//contexts
const char * const C_GLOBAL              = "Global Context";

//actions
const char * const UNDO                  = PRO_NAME_STR".Undo";
const char * const REDO                  = PRO_NAME_STR".Redo";
const char * const COPY                  = PRO_NAME_STR".Copy";
const char * const PASTE                 = PRO_NAME_STR".Paste";
const char * const CUT                   = PRO_NAME_STR".Cut";
const char * const SELECTALL             = PRO_NAME_STR".SelectAll";

const char * const EXIT                  = PRO_NAME_STR".Exit";

const char * const OPTIONS               = PRO_NAME_STR".Options";
const char * const TOGGLE_FULLSCREEN     = PRO_NAME_STR".ToggleFullScreen";

const char * const MINIMIZE_WINDOW       = PRO_NAME_STR".MinimizeWindow";
const char * const ZOOM_WINDOW           = PRO_NAME_STR".ZoomWindow";

const char * const ABOUT_PROJECT         = PRO_NAME_STR".About"PRO_NAME_STR;
const char * const ABOUT_PLUGINS         = PRO_NAME_STR".AboutPlugins";

// default groups
const char * const G_DEFAULT_ONE         = PRO_NAME_STR".Group.Default.One";
const char * const G_DEFAULT_TWO         = PRO_NAME_STR".Group.Default.Two";
const char * const G_DEFAULT_THREE       = PRO_NAME_STR".Group.Default.Three";

// main menu bar groups
const char * const G_FILE                = PRO_NAME_STR".Group.File";
const char * const G_EDIT                = PRO_NAME_STR".Group.Edit";
const char * const G_VIEW                = PRO_NAME_STR".Group.View";
const char * const G_TOOLS               = PRO_NAME_STR".Group.Tools";
const char * const G_WINDOW              = PRO_NAME_STR".Group.Window";
const char * const G_HELP                = PRO_NAME_STR".Group.Help";

// file menu groups
const char * const G_FILE_OTHER          = PRO_NAME_STR".Group.File.Other";

// edit menu groups
const char * const G_EDIT_UNDOREDO       = PRO_NAME_STR".Group.Edit.UndoRedo";
const char * const G_EDIT_COPYPASTE      = PRO_NAME_STR".Group.Edit.CopyPaste";
const char * const G_EDIT_SELECTALL      = PRO_NAME_STR".Group.Edit.SelectAll";
const char * const G_EDIT_OTHER          = PRO_NAME_STR".Group.Edit.Other";

// window menu groups
const char * const G_WINDOW_SIZE         = PRO_NAME_STR".Group.Window.Size";
const char * const G_WINDOW_OTHER        = PRO_NAME_STR".Group.Window.Other";

// help groups (global)
const char * const G_HELP_ABOUT          = PRO_NAME_STR".Group.Help.About";

const char * const ICON_UNDO             = ":/core/images/undo.png";
const char * const ICON_REDO             = ":/core/images/redo.png";
const char * const ICON_COPY             = ":/core/images/editcopy.png";
const char * const ICON_PASTE            = ":/core/images/editpaste.png";
const char * const ICON_CUT              = ":/core/images/editcut.png";
const char * const ICON_PROLOGO_32       = ":/core/images/project_logo_32.png";
const char * const ICON_PROLOGO_128      = ":/core/images/project_logo_128.png";
const char * const ICON_RESET            = ":/core/images/reset.png";

const char * const SETTINGS_CATEGORY_CORE      = "A.Core";
const char * const SETTINGS_CATEGORY_CORE_ICON = ":/core/images/category_core.png";
const char * const SETTINGS_TR_CATEGORY_CORE   = QT_TRANSLATE_NOOP("Core", "Environment");
const char * const SETTINGS_ID_ENVIRONMENT     = "A.General";

const char * const ALL_FILES_FILTER      = QT_TRANSLATE_NOOP("Core", "All Files (*)");

const int TARGET_ICON_SIZE = 32;

} // namespace Constants
} // namespace Core

#endif // CORECONSTANTS_H
