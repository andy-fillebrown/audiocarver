/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2012 Andrew Fillebrown.
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

#include "ac_guiplugin.h"

//#include <ac_editor.h>
//#include <ac_mainwidget.h>
#include <ac_database_gui_objectfactory.h>
//#include <ac_guimainwindowextension.h>
//#include <ac_selecteditemspropertyview.h>
//#include <ac_trackview.h>

//#include <mi_idatabase.h>

//#include <icore.h>
//#include <mainwindow.h>

//#include <QDockWidget>

#include <QtPlugin>

bool AcGuiPlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorMessage);
    new Database::Gui::ObjectFactory;
//    addAutoReleasedObject(new Editor);
//    addAutoReleasedObject(new Ac::Gui::MainWindowExtension);
    return true;
}

void AcGuiPlugin::extensionsInitialized()
{
//    Core::MainWindow *mw = Core::ICore::instance()->mainWindow();

//    MainWidget *widget = new MainWidget(mw);
//    mw->setCentralWidget(widget);
}

Q_EXPORT_PLUGIN(AcGuiPlugin)
