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

#include "mi_gui_mainwindow.h"
#include "mi_gui_namespace.h"
#include <icore.h>
#include <idatabase.h>
#include <mainwindow.h>
#include <QFileDialog>

using namespace Mi::Gui;

static void fileSaveAs(MainWindow *mainWindow)
{
    IDatabase *database = IDatabase::instance();
    QString filename = QFileDialog::getSaveFileName(Core::ICore::instance()->mainWindow(), "", "", QObject::tr(qPrintable(database->fileFilter())));
    if (filename.isEmpty())
        return;
    if (!filename.endsWith(database->fileExtension()))
        filename.append(database->fileExtension());
    database->write(filename);
}

static void fileSave(MainWindow *mainWindow)
{
    IDatabase *database = IDatabase::instance();
    if (database->fileName().isEmpty())
        fileSaveAs(mainWindow);
    else
        database->write(database->fileName());
}

static void fileNew(MainWindow *mainWindow)
{
    IDatabase *database = IDatabase::instance();
    if (database->isDirty() && mainWindow->maybeSaveDatabase())
        database->reset();
}

static void fileOpen(MainWindow *mainWindow)
{
    IDatabase *database = IDatabase::instance();
    if (database->isDirty())
        if (!mainWindow->maybeSaveDatabase())
            return;
    QString filename = QFileDialog::getOpenFileName(Core::ICore::instance()->mainWindow(), "", "", QObject::tr(qPrintable(database->fileFilter())));
    if (QFile::exists(filename))
        database->read(filename);
}

namespace Mi {
namespace Gui {

void MainWindow::runCommand(int command)
{
    switch (command) {
    case FileNewCommand:
        return fileNew(this);
    case FileOpenCommand:
        return fileOpen(this);
    case FileSaveCommand:
        return fileSave(this);
    case FileSaveAsCommand:
        return fileSaveAs(this);
    default:
        return;
    }
}

}
}