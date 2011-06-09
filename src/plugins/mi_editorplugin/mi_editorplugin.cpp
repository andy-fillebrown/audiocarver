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

#include "mi_editorplugin.h"
#include <mi_mainwindowimpl.h>
#include <icore.h>
#include <mainwindow.h>
#include <QtPlugin>

using namespace Private;

bool MiEditorPlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorMessage);
    addAutoReleasedObject(new MiMainWindowImpl);
    return true;
}

void MiEditorPlugin::extensionsInitialized()
{
    Core::MainWindow *mw = Core::ICore::instance()->mainWindow();
    mw->registerContainers();
    mw->registerActions();
}

Q_EXPORT_PLUGIN(MiEditorPlugin)
