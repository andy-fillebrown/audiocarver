/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2010 Andrew Fillebrown.
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

#include "ac_editorplugin.h"

#include "classes/ac_editorwidget.h"

#include "implementations/ac_mainwindowimpl.h"
#include "implementations/ac_editorimpl.h"
#include "implementations/ac_gleditorimpl.h"

#include <coreplugin/icore.h>
#include <coreplugin/mainwindow.h>

#include <QtCore/QtPlugin>

using namespace AudioCarver;
using namespace AudioCarver::Internal;

EditorPlugin::EditorPlugin()
{
}

EditorPlugin::~EditorPlugin()
{
}

bool EditorPlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorMessage);
    addAutoReleasedObject(new MainWindowImpl);
    addAutoReleasedObject(new EditorImpl);
    addAutoReleasedObject(new GLEditorImpl);
    return true;
}

void EditorPlugin::extensionsInitialized()
{
    // EditorWidget instance must be created with main window as it's parent,
    // otherwise app crashes when run on Windows OS.
    // Encountered this issue on 1/31/11 (Windows 7, 64 bit).
    Core::MainWindow *mw = Core::ICore::instance()->mainWindow();
    EditorWidget *ew = new EditorWidget(mw);
    mw->setCentralWidget(ew);
}

Q_EXPORT_PLUGIN(EditorPlugin)
