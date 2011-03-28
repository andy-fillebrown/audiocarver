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

#include "editorplugin.h"

#include <editorplugin/classes/graphicsview.h>
#include <editorplugin/implementations/mainwindowimpl.h>
#include <sceneplugin/interfaces/iscene.h>
#include <coreplugin/icore.h>
#include <coreplugin/mainwindow.h>

#include <QtCore/QtPlugin>

using namespace Editor;
using namespace Editor::Internal;

bool EditorPlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorMessage);
    addAutoReleasedObject(new MainWindowImpl);
    return true;
}

void EditorPlugin::extensionsInitialized()
{
    Core::MainWindow *mw = Core::ICore::instance()->mainWindow();
    mw->registerContainers();
    mw->registerActions();

    GraphicsView *view = new GraphicsView(mw);
    view->setScene(Scene::IScene::instance()->scene());
    mw->setCentralWidget(view);
}

Q_EXPORT_PLUGIN(EditorPlugin)
