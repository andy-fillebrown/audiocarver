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

#include "editorplugin3d.h"

#include "classes/centralwidget3d.h"

#include "implementations/editor3dmainwindowimpl.h"

#include <coreplugin/icore.h>
#include <coreplugin/mainwindow.h>

#include <QtCore/QtPlugin>

using namespace Editor3D;
using namespace Editor3D::Internal;

EditorPlugin3D::EditorPlugin3D()
{
}

EditorPlugin3D::~EditorPlugin3D()
{
}

bool EditorPlugin3D::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorMessage);
    addAutoReleasedObject(new MainWindowImpl);
    return true;
}

void EditorPlugin3D::extensionsInitialized()
{
    QGLFormat fmt;
    fmt.setSwapInterval(1);
    Core::MainWindow *mw = Core::ICore::instance()->mainWindow();
    mw->setCentralWidget(new CentralWidget3D(fmt, mw));
}

Q_EXPORT_PLUGIN(EditorPlugin3D)
