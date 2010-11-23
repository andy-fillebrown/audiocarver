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

#include "ide_version.h"

#define STRINGIFY_INTERNAL(x) #x
#define STRINGIFY(x) STRINGIFY_INTERNAL(x)

#define AC_VERSION STRINGIFY(AC_VERSION_MAJOR) \
    "." STRINGIFY(AC_VERSION_MINOR) \
    "." STRINGIFY(AC_VERSION_RELEASE)

const char * const AC_VERSION_LONG      = AC_VERSION;
const char * const AC_AUTHOR            = "Andy Fillebrown";
const char * const AC_YEAR              = "2010";

#ifdef AC_VERSION_DESCRIPTION
const char * const AC_VERSION_DESCRIPTION_STR = STRINGIFY(AC_VERSION_DESCRIPTION);
#else
const char * const AC_VERSION_DESCRIPTION_STR = "";
#endif

#ifdef AC_REVISION
const char * const AC_REVISION_STR      = STRINGIFY(IDE_REVISION);
#else
const char * const AC_REVISION_STR      = "";
#endif

#undef AC_VERSION
#undef STRINGIFY
#undef STRINGIFY_INTERNAL

//modes
//const char * const MODE_WELCOME          = "Welcome";
//const char * const MODE_WELCOME_TYPE     = "Type.Welcome";
//const char * const MODE_EDIT             = "Edit";
//const char * const MODE_EDIT_TYPE        = "Type.Edit";
//const char * const MODE_DESIGN           = "Design";
//const char * const MODE_DESIGN_TYPE      = "Type.Design";
//const int          P_MODE_WELCOME        = 100;
//const int          P_MODE_EDIT           = 90;
//const int          P_MODE_DESIGN         = 89;
//const int          P_MODE_OUTPUT         = 10;

//menubar
const char * const MENU_BAR              = "AudioCarver.MenuBar";

//menus
const char * const M_FILE                = "AudioCarver.Menu.File";
const char * const M_FILE_OPEN           = "AudioCarver.Menu.File.Open";
const char * const M_FILE_NEW            = "AudioCarver.Menu.File.New";
const char * const M_FILE_RECENTFILES    = "AudioCarver.Menu.File.RecentFiles";
const char * const M_EDIT                = "AudioCarver.Menu.Edit";
const char * const M_EDIT_ADVANCED       = "AudioCarver.Menu.Edit.Advanced";
const char * const M_TOOLS               = "AudioCarver.Menu.Tools";
const char * const M_WINDOW              = "AudioCarver.Menu.Window";
const char * const M_WINDOW_PANES        = "AudioCarver.Menu.Window.Panes";
const char * const M_WINDOW_VIEWS        = "AudioCarver.Menu.Window.Views";
const char * const M_HELP                = "AudioCarver.Menu.Help";

//contexts
const char * const C_GLOBAL              = "Global Context";
const char * const C_WELCOME_MODE        = "Core.WelcomeMode";
const char * const C_EDIT_MODE           = "Core.EditMode";
const char * const C_DESIGN_MODE         = "Core.DesignMode";
const char * const C_EDITORMANAGER       = "Core.EditorManager";
const char * const C_NAVIGATION_PANE     = "Core.NavigationPane";
const char * const C_PROBLEM_PANE        = "Core.ProblemPane";

//default editor kind
const char * const K_DEFAULT_TEXT_EDITOR_DISPLAY_NAME = QT_TRANSLATE_NOOP("OpenWith::Editors", "Plain Text Editor");
const char * const K_DEFAULT_TEXT_EDITOR_ID = "Core.PlainTextEditor";
const char * const K_DEFAULT_BINARY_EDITOR_ID = "Core.BinaryEditor";

//actions
const char * const UNDO                  = "AudioCarver.Undo";
const char * const REDO                  = "AudioCarver.Redo";
const char * const COPY                  = "AudioCarver.Copy";
const char * const PASTE                 = "AudioCarver.Paste";
const char * const CUT                   = "AudioCarver.Cut";
const char * const SELECTALL             = "AudioCarver.SelectAll";

const char * const GOTO                  = "AudioCarver.Goto";

const char * const NEW                   = "AudioCarver.New";
const char * const OPEN                  = "AudioCarver.Open";
const char * const OPEN_WITH             = "AudioCarver.OpenWith";
const char * const REVERTTOSAVED         = "AudioCarver.RevertToSaved";
const char * const SAVE                  = "AudioCarver.Save";
const char * const SAVEAS                = "AudioCarver.SaveAs";
const char * const SAVEALL               = "AudioCarver.SaveAll";
const char * const PRINT                 = "AudioCarver.Print";
const char * const EXIT                  = "AudioCarver.Exit";

const char * const OPTIONS               = "AudioCarver.Options";
const char * const TOGGLE_SIDEBAR        = "AudioCarver.ToggleSidebar";
const char * const TOGGLE_FULLSCREEN     = "AudioCarver.ToggleFullScreen";

const char * const MINIMIZE_WINDOW       = "AudioCarver.MinimizeWindow";
const char * const ZOOM_WINDOW           = "AudioCarver.ZoomWindow";

const char * const SPLIT                 = "AudioCarver.Split";
const char * const SPLIT_SIDE_BY_SIDE    = "AudioCarver.SplitSideBySide";
const char * const REMOVE_CURRENT_SPLIT  = "AudioCarver.RemoveCurrentSplit";
const char * const REMOVE_ALL_SPLITS     = "AudioCarver.RemoveAllSplits";
const char * const GOTO_OTHER_SPLIT      = "AudioCarver.GotoOtherSplit";
const char * const SAVEASDEFAULT         = "AudioCarver.SaveAsDefaultLayout";
const char * const RESTOREDEFAULT        = "AudioCarver.RestoreDefaultLayout";
const char * const CLOSE                 = "AudioCarver.Close";
const char * const CLOSE_ALTERNATIVE     = "AudioCarver.Close_Alternative"; // temporary, see QTCREATORBUG-72
const char * const CLOSEALL              = "AudioCarver.CloseAll";
const char * const CLOSEOTHERS           = "AudioCarver.CloseOthers";
const char * const GOTONEXT              = "AudioCarver.GotoNext";
const char * const GOTOPREV              = "AudioCarver.GotoPrevious";
const char * const GOTONEXTINHISTORY     = "AudioCarver.GotoNextInHistory";
const char * const GOTOPREVINHISTORY     = "AudioCarver.GotoPreviousInHistory";
const char * const GO_BACK               = "AudioCarver.GoBack";
const char * const GO_FORWARD            = "AudioCarver.GoForward";
const char * const GOTOPREVIOUSGROUP     = "AudioCarver.GotoPreviousTabGroup";
const char * const GOTONEXTGROUP         = "AudioCarver.GotoNextTabGroup";
const char * const WINDOWSLIST           = "AudioCarver.WindowsList";
const char * const ABOUT_QTCREATOR       = "AudioCarver.AboutQtCreator";
const char * const ABOUT_PLUGINS         = "AudioCarver.AboutPlugins";
const char * const ABOUT_QT              = "AudioCarver.AboutQt";
const char * const S_RETURNTOEDITOR      = "AudioCarver.ReturnToEditor";
const char * const OPEN_IN_EXTERNAL_EDITOR = "AudioCarver.OpenInExternalEditor";

// default groups
const char * const G_DEFAULT_ONE         = "AudioCarver.Group.Default.One";
const char * const G_DEFAULT_TWO         = "AudioCarver.Group.Default.Two";
const char * const G_DEFAULT_THREE       = "AudioCarver.Group.Default.Three";

// main menu bar groups
const char * const G_FILE                = "AudioCarver.Group.File";
const char * const G_EDIT                = "AudioCarver.Group.Edit";
const char * const G_VIEW                = "AudioCarver.Group.View";
const char * const G_TOOLS               = "AudioCarver.Group.Tools";
const char * const G_WINDOW              = "AudioCarver.Group.Window";
const char * const G_HELP                = "AudioCarver.Group.Help";

// file menu groups
const char * const G_FILE_NEW            = "AudioCarver.Group.File.New";
const char * const G_FILE_OPEN           = "AudioCarver.Group.File.Open";
const char * const G_FILE_PROJECT        = "AudioCarver.Group.File.Project";
const char * const G_FILE_SAVE           = "AudioCarver.Group.File.Save";
const char * const G_FILE_CLOSE          = "AudioCarver.Group.File.Close";
const char * const G_FILE_PRINT          = "AudioCarver.Group.File.Print";
const char * const G_FILE_OTHER          = "AudioCarver.Group.File.Other";

// edit menu groups
const char * const G_EDIT_UNDOREDO       = "AudioCarver.Group.Edit.UndoRedo";
const char * const G_EDIT_COPYPASTE      = "AudioCarver.Group.Edit.CopyPaste";
const char * const G_EDIT_SELECTALL      = "AudioCarver.Group.Edit.SelectAll";
const char * const G_EDIT_ADVANCED       = "AudioCarver.Group.Edit.Advanced";

const char * const G_EDIT_FIND           = "AudioCarver.Group.Edit.Find";
const char * const G_EDIT_OTHER          = "AudioCarver.Group.Edit.Other";

// advanced edit menu groups

const char * const G_EDIT_FORMAT         = "AudioCarver.Group.Edit.Format";
const char * const G_EDIT_COLLAPSING     = "AudioCarver.Group.Edit.Collapsing";
const char * const G_EDIT_BLOCKS         = "AudioCarver.Group.Edit.Blocks";
const char * const G_EDIT_FONT           = "AudioCarver.Group.Edit.Font";
const char * const G_EDIT_EDITOR         = "AudioCarver.Group.Edit.Editor";

// window menu groups
const char * const G_WINDOW_SIZE         = "AudioCarver.Group.Window.Size";
const char * const G_WINDOW_PANES        = "AudioCarver.Group.Window.Panes";
const char * const G_WINDOW_VIEWS        = "AudioCarver.Group.Window.Views";
const char * const G_WINDOW_SPLIT        = "AudioCarver.Group.Window.Split";
const char * const G_WINDOW_NAVIGATE     = "AudioCarver.Group.Window.Navigate";
const char * const G_WINDOW_OTHER        = "AudioCarver.Group.Window.Other";

// help groups (global)
const char * const G_HELP_HELP           = "AudioCarver.Group.Help.Help";
const char * const G_HELP_ABOUT          = "AudioCarver.Group.Help.About";

const char * const ICON_MINUS            = ":/core/images/minus.png";
const char * const ICON_PLUS             = ":/core/images/plus.png";
const char * const ICON_NEWFILE          = ":/core/images/filenew.png";
const char * const ICON_OPENFILE         = ":/core/images/fileopen.png";
const char * const ICON_SAVEFILE         = ":/core/images/filesave.png";
const char * const ICON_UNDO             = ":/core/images/undo.png";
const char * const ICON_REDO             = ":/core/images/redo.png";
const char * const ICON_COPY             = ":/core/images/editcopy.png";
const char * const ICON_PASTE            = ":/core/images/editpaste.png";
const char * const ICON_CUT              = ":/core/images/editcut.png";
const char * const ICON_NEXT             = ":/core/images/next.png";
const char * const ICON_PREV             = ":/core/images/prev.png";
const char * const ICON_DIR              = ":/core/images/dir.png";
const char * const ICON_CLEAN_PANE       = ":/core/images/clean_pane_small.png";
const char * const ICON_CLEAR            = ":/core/images/clear.png";
const char * const ICON_FIND             = ":/core/images/find.png";
const char * const ICON_FINDNEXT         = ":/core/images/findnext.png";
const char * const ICON_REPLACE          = ":/core/images/replace.png";
const char * const ICON_RESET            = ":/core/images/reset.png";
const char * const ICON_MAGNIFIER        = ":/core/images/magnifier.png";
const char * const ICON_TOGGLE_SIDEBAR   = ":/core/images/sidebaricon.png";
const char * const ICON_CLOSE            = ":/core/images/closebutton.png";
const char * const ICON_CLOSE_DARK       = ":/core/images/darkclosebutton.png";
const char * const ICON_SPLIT_HORIZONTAL = ":/core/images/splitbutton_horizontal.png";
const char * const ICON_FILTER           = ":/core/images/filtericon.png";
const char * const ICON_LINK             = ":/core/images/linkicon.png";
const char * const ICON_QTLOGO_32        = ":/core/images/qtcreator_logo_32.png";
const char * const ICON_QTLOGO_128       = ":/core/images/qtcreator_logo_128.png";

const char * const WIZARD_CATEGORY_QT = "R.Qt";
const char * const WIZARD_TR_CATEGORY_QT = QT_TRANSLATE_NOOP("Core", "Qt");

const char * const SETTINGS_CATEGORY_CORE = "A.Core";
const char * const SETTINGS_CATEGORY_CORE_ICON = ":/core/images/category_core.png";
const char * const SETTINGS_TR_CATEGORY_CORE = QT_TRANSLATE_NOOP("Core", "Environment");
const char * const SETTINGS_ID_ENVIRONMENT = "A.General";

const char * const SETTINGS_DEFAULTTEXTENCODING = "General/DefaultFileEncoding";

const char * const ALL_FILES_FILTER      = QT_TRANSLATE_NOOP("Core", "All Files (*)");

const int TARGET_ICON_SIZE = 32;

} // namespace Constants
} // namespace Core

#endif // CORECONSTANTS_H
