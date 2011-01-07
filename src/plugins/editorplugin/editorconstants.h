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

#ifndef EDITORCONSTANTS_H
#define EDITORCONSTANTS_H

#include <coreplugin/coreconstants.h>

namespace Editor {
namespace Constants {

const char * const G_EDIT           = PRO_NAME_STR".Group.Edit";

const char * const G_FILE_NEW       = PRO_NAME_STR".Group.File.New";
const char * const G_FILE_OPEN      = PRO_NAME_STR".Group.File.Open";
const char * const G_FILE_SAVE      = PRO_NAME_STR".Group.File.Save";

const char * const G_EDIT_UNDOREDO  = PRO_NAME_STR".Group.Edit.UndoRedo";
const char * const G_EDIT_COPYPASTE = PRO_NAME_STR".Group.Edit.CopyPaste";
const char * const G_EDIT_SELECTALL = PRO_NAME_STR".Group.Edit.SelectAll";
const char * const G_EDIT_OTHER     = PRO_NAME_STR".Group.Edit.Other";

const char * const M_EDIT           = PRO_NAME_STR".Menu.Edit";

const char * const NEW              = PRO_NAME_STR".New";
const char * const OPEN             = PRO_NAME_STR".Open";
const char * const SAVE             = PRO_NAME_STR".Save";
const char * const SAVEAS           = PRO_NAME_STR".SaveAs";

const char * const UNDO             = PRO_NAME_STR".Undo";
const char * const REDO             = PRO_NAME_STR".Redo";
const char * const COPY             = PRO_NAME_STR".Copy";
const char * const PASTE            = PRO_NAME_STR".Paste";
const char * const CUT              = PRO_NAME_STR".Cut";
const char * const SELECTALL        = PRO_NAME_STR".SelectAll";

const char * const ICON_NEW         = ":/editor/images/filenew.png";
const char * const ICON_OPEN        = ":/editor/images/fileopen.png";
const char * const ICON_SAVE        = ":/editor/images/filesave.png";

const char * const ICON_UNDO        = ":/editor/images/undo.png";
const char * const ICON_REDO        = ":/editor/images/redo.png";
const char * const ICON_COPY        = ":/editor/images/editcopy.png";
const char * const ICON_PASTE       = ":/editor/images/editpaste.png";
const char * const ICON_CUT         = ":/editor/images/editcut.png";

} // namespace Constants
} // namespace Editor

#endif // EDITORCONSTANTS_H
