/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2013 Andrew Fillebrown.
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

#include "ac_gui_plugin.h"
#include "ac_gui_databaseobjectfactory.h"
#include "ac_gui_database_graphicsviewmanagerupdater.h"
#include "ac_gui_editor.h"
#include "ac_gui_filerfactory.h"
#include "ac_gui_mainwidget.h"
#include "ac_gui_mainwindow.h"
#include "ac_gui_mainwindowextension.h"
#include "ac_gui_model_editorupdater.h"
#include "ac_gui_undomanager.h"
#include <ac_core_database.h>
#include <ac_core_namespace.h>
#include <mainwindow.h>
#include <icore.h>
#include <imodel.h>
#include <QtPlugin>

namespace Ac {
namespace Gui {

Plugin::Plugin()
{
    new DatabaseObjectFactory;
    new Core::Database;
    new Editor;
    new FilerFactory;
    new UndoManager;
    new Database::GraphicsViewManagerUpdater;
    new Model::EditorUpdater;
    new MainWindow;
    addAutoReleasedObject(new ::Gui::MainWindowExtension);
}

Plugin::~Plugin()
{
    IModel::instance()->reset();
}

void Plugin::extensionsInitialized()
{
    ::Core::MainWindow *main_window = ::Core::ICore::instance()->mainWindow();
    MainWidget *widget = new MainWidget(main_window);
    main_window->setCentralWidget(widget);
}

}
}

Q_EXPORT_PLUGIN(::Ac::Gui::Plugin)
