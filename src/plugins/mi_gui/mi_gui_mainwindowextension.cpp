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

#include "mi_gui_mainwindowextension.h"
#include "mi_gui_constants.h"
#include "mi_gui_namespace.h"
#include <actioncontainer.h>
#include <actionmanager.h>
#include <command.h>
#include <icontext.h>
#include <icore.h>
#include <ieditor.h>
#include <imainwindow.h>
#include <iundomanager.h>
#include <QAction>
#include <QIcon>

using namespace Mi;
using namespace Core;

namespace Base {

void MainWindowExtension::initMenuBarGroups(QStringList &groups) const
{
    const int fileGroupIndex = groups.indexOf(Constants::G_FILE);
    groups.insert(fileGroupIndex + 1, G_EDIT);
}

void MainWindowExtension::initMenuGroups(const QString &menuBarGroup, QString &id, QString &title, QStringList &groups) const
{
    if (Constants::G_FILE == menuBarGroup) {
        groups << G_FILE_NEW
               << G_FILE_OPEN
               << G_FILE_SAVE
               << G_FILE_IMPORT;
    } else if (G_EDIT == menuBarGroup) {
        id = M_EDIT;
        title = tr("&Edit");
        groups << G_EDIT_UNDOREDO
               << G_EDIT_COPYPASTE
               << G_EDIT_SELECTALL
               << G_EDIT_OTHER;
    }
}

void MainWindowExtension::initActions()
{
    ActionManager *am = Core::ICore::instance()->actionManager();
    ActionContainer *fileMenu = am->actionContainer(Constants::M_FILE);
    ActionContainer *editMenu = am->actionContainer(M_EDIT);
    Context globalContext(Constants::C_GLOBAL);
    QIcon icon;
    QAction *action = 0;
    Command *cmd = 0;

    // New Action
    icon = QIcon::fromTheme(QLatin1String("document-new"), QIcon(ICON_NEW));
    action = new QAction(icon, tr("&New"), this);
    cmd = am->registerAction(action, NEW, globalContext);
    cmd->setDefaultKeySequence(QKeySequence::New);
    fileMenu->addAction(cmd, G_FILE_NEW);
    connect(action, SIGNAL(triggered()), SLOT(newFile()));

    // Open Action
    icon = QIcon::fromTheme(QLatin1String("document-open"), QIcon(ICON_OPEN));
    action = new QAction(icon, tr("&Open"), this);
    cmd = am->registerAction(action, OPEN, globalContext);
    cmd->setDefaultKeySequence(QKeySequence::Open);
    fileMenu->addAction(cmd, G_FILE_OPEN);
    connect(action, SIGNAL(triggered()), SLOT(openFile()));

    // Save/Save As Separator
    action = new QAction(this);
    action->setSeparator(true);
    cmd = am->registerAction(action, PRO_NAME_STR".File.Sep.Save", globalContext);
    fileMenu->addAction(cmd, G_FILE_SAVE);

    // Save
    icon = QIcon::fromTheme(QLatin1String("document-save"), QIcon(ICON_SAVE));
    action = new QAction(icon, tr("&Save"), this);
    cmd = am->registerAction(action, SAVE, globalContext);
    cmd->setDefaultKeySequence(QKeySequence::Save);
    fileMenu->addAction(cmd, G_FILE_SAVE);
    connect(action, SIGNAL(triggered()), SLOT(saveFile()));

    // Save As
    action = new QAction(tr("Save &As"), this);
    cmd = am->registerAction(action, SAVEAS, globalContext);
    fileMenu->addAction(cmd, G_FILE_SAVE);
    connect(action, SIGNAL(triggered()), SLOT(saveFileAs()));

    // Undo Action
    icon = QIcon::fromTheme(QLatin1String("edit-undo"), QIcon(ICON_UNDO));
    action = new QAction(icon, tr("&Undo"), this);
    cmd = am->registerAction(action, UNDO, globalContext);
    cmd->setDefaultKeySequence(QKeySequence::Undo);
    cmd->setAttribute(Command::CA_UpdateText);
    cmd->setDefaultText(tr("&Undo"));
    editMenu->addAction(cmd, G_EDIT_UNDOREDO);
    connect(action, SIGNAL(triggered()), SLOT(undo()));

    // Redo Action
    icon = QIcon::fromTheme(QLatin1String("edit-redo"), QIcon(ICON_REDO));
    action = new QAction(icon, tr("&Redo"), this);
    cmd = am->registerAction(action, REDO, globalContext);
    cmd->setDefaultKeySequence(QKeySequence::Redo);
    cmd->setAttribute(Command::CA_UpdateText);
    cmd->setDefaultText(tr("&Redo"));
    editMenu->addAction(cmd, G_EDIT_UNDOREDO);
    connect(action, SIGNAL(triggered()), SLOT(redo()));

    // Copy/Paste Separator
    action = new QAction(this);
    action->setSeparator(true);
    cmd = am->registerAction(action, PRO_NAME_STR".Edit.Sep.CopyPaste", globalContext);
    editMenu->addAction(cmd, G_EDIT_COPYPASTE);

    // Cut Action
    icon = QIcon::fromTheme(QLatin1String("edit-cut"), QIcon(ICON_CUT));
    action = new QAction(icon, tr("Cu&t"), this);
    cmd = am->registerAction(action, CUT, globalContext);
    cmd->setDefaultKeySequence(QKeySequence::Cut);
    editMenu->addAction(cmd, G_EDIT_COPYPASTE);
    connect(action, SIGNAL(triggered()), SLOT(cut()));

    // Copy Action
    icon = QIcon::fromTheme(QLatin1String("edit-copy"), QIcon(ICON_COPY));
    action = new QAction(icon, tr("&Copy"), this);
    cmd = am->registerAction(action, COPY, globalContext);
    cmd->setDefaultKeySequence(QKeySequence::Copy);
    editMenu->addAction(cmd, G_EDIT_COPYPASTE);
    connect(action, SIGNAL(triggered()), SLOT(copy()));

    // Paste Action
    icon = QIcon::fromTheme(QLatin1String("edit-paste"), QIcon(ICON_PASTE));
    action = new QAction(icon, tr("&Paste"), this);
    cmd = am->registerAction(action, PASTE, globalContext);
    cmd->setDefaultKeySequence(QKeySequence::Paste);
    editMenu->addAction(cmd, G_EDIT_COPYPASTE);
    connect(action, SIGNAL(triggered()), SLOT(paste()));

    // Select All Separator
    action = new QAction(this);
    action->setSeparator(true);
    cmd = am->registerAction(action, PRO_NAME_STR".Edit.Sep.SelectAll", globalContext);
    editMenu->addAction(cmd, G_EDIT_SELECTALL);

    // Select All
    icon = QIcon::fromTheme(QLatin1String("edit-select-all"));
    action = new QAction(icon, tr("&Select All"), this);
    cmd = am->registerAction(action, SELECTALL, globalContext);
    cmd->setDefaultKeySequence(QKeySequence::SelectAll);
    editMenu->addAction(cmd, G_EDIT_SELECTALL);
    connect(action, SIGNAL(triggered()), SLOT(selectAll()));
}

void MainWindowExtension::newFile()
{
    IMainWindow::instance()->runCommand(FileNewCommand);
}

void MainWindowExtension::openFile()
{
    IMainWindow::instance()->runCommand(FileOpenCommand);
}

void MainWindowExtension::saveFile()
{
    IMainWindow::instance()->runCommand(FileSaveCommand);
}

void MainWindowExtension::saveFileAs()
{
    IMainWindow::instance()->runCommand(FileSaveAsCommand);
}

void MainWindowExtension::undo()
{
    IUndoManager::instance()->undo();
}

void MainWindowExtension::redo()
{
    IUndoManager::instance()->redo();
}

void MainWindowExtension::cut()
{
    IEditor::instance()->runCommand(CutCommand);
}

void MainWindowExtension::copy()
{
    IEditor::instance()->runCommand(CopyCommand);
}

void MainWindowExtension::paste()
{
    IEditor::instance()->runCommand(PasteCommand);
}

void MainWindowExtension::selectAll()
{
    IEditor::instance()->runCommand(SelectAllCommand);
}

}
