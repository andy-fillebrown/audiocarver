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

#include "ac_midi_mainwindowextension.h"
#include "ac_midi_constants.h"
#include "ac_midi_fileimportdialog.h"
#include <actioncontainer.h>
#include <actionmanager.h>
#include <icontext.h>
#include <icore.h>
#include <mainwindow.h>
#include <QAction>
#include <QMenu>

using namespace Midi;
using namespace Core;

namespace Ac {
namespace Midi {

void MainWindowExtension::initMenuBarGroups(QStringList &groups) const
{}

void MainWindowExtension::initMenuGroups(const QString &menuBarGroup, QString &id, QString &title, QStringList &groups) const
{}

void MainWindowExtension::initActions()
{
    ActionManager *am = ICore::instance()->actionManager();
    ActionContainer *file_menu = am->actionContainer(Constants::M_FILE);
    Context global_context(Constants::C_GLOBAL);
    QAction *action = 0;
    Command *cmd = 0;

    // Create File->Import menu if not already created.
    ActionContainer *import_menu = am->actionContainer(M_IMPORT);
    if (!import_menu) {
        action = new QAction(this);
        action->setSeparator(true);
        cmd = am->registerAction(action, PRO_NAME_STR".File.Sep.Import", global_context);
        file_menu->addAction(cmd, G_FILE_IMPORT);
        import_menu = am->createMenu(M_IMPORT);
        file_menu->addMenu(import_menu, G_FILE_IMPORT);
        import_menu->menu()->setTitle(tr("&Import"));
    }

    // Import MIDI File Action
    action = new QAction(tr("&MIDI File"), this);
    cmd = am->registerAction(action, IMPORTMIDIFILE, global_context);
    import_menu->addAction(cmd);
    connect(action, SIGNAL(triggered()), SLOT(importMidiFile()));
}

void MainWindowExtension::importMidiFile()
{
    FileImportDialog *dlg = new FileImportDialog(ICore::instance()->mainWindow());
    dlg->exec();
    delete dlg;
}

}
}
