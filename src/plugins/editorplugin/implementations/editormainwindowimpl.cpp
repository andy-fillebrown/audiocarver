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

#include "editormainwindowimpl.h"

#include "interfaces/ieditor.h"

#include "../editorconstants.h"

#include <databaseplugin/interfaces/idatabase.h>

#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/command.h>

#include <coreplugin/icontext.h>
#include <coreplugin/icore.h>
#include <coreplugin/mainwindow.h>

#include <extensionsystem/pluginmanager.h>

#include <QtGui/QAction>
#include <QtGui/QFileDialog>
#include <QtGui/QIcon>

using namespace Editor;
using namespace Editor::Internal;

MainWindowImpl::MainWindowImpl()
{
}

MainWindowImpl::~MainWindowImpl()
{
}

void MainWindowImpl::initMenuBarGroups(QStringList &groups) const
{
    const int fileGroupIndex = groups.indexOf(Core::Constants::G_FILE);
    groups.insert(fileGroupIndex + 1, Constants::G_EDIT);
}

void MainWindowImpl::initMenuGroups(const QString &menuBarGroup, QString &id, QString &title, QStringList &groups) const
{
    if (menuBarGroup == Core::Constants::G_FILE) {
        groups  << Constants::G_FILE_NEW
                << Constants::G_FILE_OPEN
                << Constants::G_FILE_SAVE;
    }
    if (menuBarGroup == Constants::G_EDIT) {
        id = Constants::M_EDIT;
        title = tr("&Edit");
        groups  << Constants::G_EDIT_UNDOREDO
                << Constants::G_EDIT_COPYPASTE
                << Constants::G_EDIT_SELECTALL
                << Constants::G_EDIT_OTHER;
    }
}

void MainWindowImpl::initActions()
{
    Core::ActionManager *am = Core::ICore::instance()->actionManager();
    Core::ActionContainer *fileMenu = am->actionContainer(Core::Constants::M_FILE);
    Core::ActionContainer *editMenu = am->actionContainer(Constants::M_EDIT);
    Core::Context globalContext(Core::Constants::C_GLOBAL);

    QIcon icon;
    QAction *action = 0;
    Core::Command *cmd = 0;

    icon = QIcon::fromTheme(QLatin1String("document-new"), QIcon(Constants::ICON_NEW));
    action = new QAction(icon, tr("&New"), this);
    cmd = am->registerAction(action, Constants::NEW, globalContext);
    cmd->setDefaultKeySequence(QKeySequence::New);
    fileMenu->addAction(cmd, Constants::G_FILE_NEW);
    connect(action, SIGNAL(triggered()), SLOT(newFile()));

    icon = QIcon::fromTheme(QLatin1String("document-open"), QIcon(Constants::ICON_OPEN));
    action = new QAction(icon, tr("&Open"), this);
    cmd = am->registerAction(action, Constants::OPEN, globalContext);
    cmd->setDefaultKeySequence(QKeySequence::Open);
    fileMenu->addAction(cmd, Constants::G_FILE_OPEN);
    connect(action, SIGNAL(triggered()), SLOT(openFile()));

    action = new QAction(this);
    action->setSeparator(true);
    cmd = am->registerAction(action, PRO_NAME_STR".File.Sep.Save", globalContext);
    fileMenu->addAction(cmd, Constants::G_FILE_SAVE);

    icon = QIcon::fromTheme(QLatin1String("document-save"), QIcon(Constants::ICON_SAVE));
    action = new QAction(icon, tr("&Save"), this);
    cmd = am->registerAction(action, Constants::SAVE, globalContext);
    cmd->setDefaultKeySequence(QKeySequence::Save);
    fileMenu->addAction(cmd, Constants::G_FILE_SAVE);
    connect(action, SIGNAL(triggered()), SLOT(saveFile()));

    action = new QAction(tr("Save &As"), this);
    cmd = am->registerAction(action, Constants::SAVEAS, globalContext);
    fileMenu->addAction(cmd, Constants::G_FILE_SAVE);
    connect(action, SIGNAL(triggered()), SLOT(saveFileAs()));

    // Undo Action
    icon = QIcon::fromTheme(QLatin1String("edit-undo"), QIcon(Constants::ICON_UNDO));
    action = new QAction(icon, tr("&Undo"), this);
    cmd = am->registerAction(action, Constants::UNDO, globalContext);
    cmd->setDefaultKeySequence(QKeySequence::Undo);
    cmd->setAttribute(Core::Command::CA_UpdateText);
    cmd->setDefaultText(tr("&Undo"));
    editMenu->addAction(cmd, Constants::G_EDIT_UNDOREDO);
    connect(action, SIGNAL(triggered()), SLOT(undo()));

    // Redo Action
    icon = QIcon::fromTheme(QLatin1String("edit-redo"), QIcon(Constants::ICON_REDO));
    action = new QAction(icon, tr("&Redo"), this);
    cmd = am->registerAction(action, Constants::REDO, globalContext);
    cmd->setDefaultKeySequence(QKeySequence::Redo);
    cmd->setAttribute(Core::Command::CA_UpdateText);
    cmd->setDefaultText(tr("&Redo"));
    editMenu->addAction(cmd, Constants::G_EDIT_UNDOREDO);
    connect(action, SIGNAL(triggered()), SLOT(redo()));

    // Copy/Paste Separator
    action = new QAction(this);
    action->setSeparator(true);
    cmd = am->registerAction(action, PRO_NAME_STR".Edit.Sep.CopyPaste", globalContext);
    editMenu->addAction(cmd, Constants::G_EDIT_COPYPASTE);

    // Cut Action
    icon = QIcon::fromTheme(QLatin1String("edit-cut"), QIcon(Constants::ICON_CUT));
    action = new QAction(icon, tr("Cu&t"), this);
    cmd = am->registerAction(action, Constants::CUT, globalContext);
    cmd->setDefaultKeySequence(QKeySequence::Cut);
    editMenu->addAction(cmd, Constants::G_EDIT_COPYPASTE);
    connect(action, SIGNAL(triggered()), SLOT(cut()));

    // Copy Action
    icon = QIcon::fromTheme(QLatin1String("edit-copy"), QIcon(Constants::ICON_COPY));
    action = new QAction(icon, tr("&Copy"), this);
    cmd = am->registerAction(action, Constants::COPY, globalContext);
    cmd->setDefaultKeySequence(QKeySequence::Copy);
    editMenu->addAction(cmd, Constants::G_EDIT_COPYPASTE);
    connect(action, SIGNAL(triggered()), SLOT(copy()));

    // Paste Action
    icon = QIcon::fromTheme(QLatin1String("edit-paste"), QIcon(Constants::ICON_PASTE));
    action = new QAction(icon, tr("&Paste"), this);
    cmd = am->registerAction(action, Constants::PASTE, globalContext);
    cmd->setDefaultKeySequence(QKeySequence::Paste);
    editMenu->addAction(cmd, Constants::G_EDIT_COPYPASTE);
    connect(action, SIGNAL(triggered()), SLOT(paste()));

    // Select All Separator
    action = new QAction(this);
    action->setSeparator(true);
    cmd = am->registerAction(action, PRO_NAME_STR".Edit.Sep.SelectAll", globalContext);
    editMenu->addAction(cmd, Constants::G_EDIT_SELECTALL);

    // Select All
    icon = QIcon::fromTheme(QLatin1String("edit-select-all"));
    action = new QAction(icon, tr("&Select All"), this);
    cmd = am->registerAction(action, Constants::SELECTALL, globalContext);
    cmd->setDefaultKeySequence(QKeySequence::SelectAll);
    editMenu->addAction(cmd, Constants::G_EDIT_SELECTALL);
    connect(action, SIGNAL(triggered()), SLOT(selectAll()));
}

void MainWindowImpl::newFile()
{
    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    Database::IDatabase *db = pm->getObject<Database::IDatabase>();
    if (!db)
        return;
    db->clear();
}

void MainWindowImpl::openFile()
{
    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    Database::IDatabase *db = pm->getObject<Database::IDatabase>();
    if (!db)
        return;
    const QString filter = db->fileFilter();
    QString filename = QFileDialog::getOpenFileName(
                Core::ICore::instance()->mainWindow(), "", "",
                tr(qPrintable(filter)));
    if (!QFile::exists(filename))
        return;
    db->read(filename);
}

void MainWindowImpl::saveFile()
{
    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    Database::IDatabase *db = pm->getObject<Database::IDatabase>();
    if (!db)
        return;
    db->write(db->fileName());
}

void MainWindowImpl::saveFileAs()
{
    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    Database::IDatabase *db = pm->getObject<Database::IDatabase>();
    if (!db)
        return;
    const QString filter = db->fileFilter();
    QString filename = QFileDialog::getSaveFileName(
                Core::ICore::instance()->mainWindow(), "", "",
                tr(qPrintable(filter)));
    if (filename.isEmpty())
        return;
    if (!filename.endsWith(db->fileExtension()))
        filename.append(db->fileExtension());
    db->write(filename);
}

void MainWindowImpl::undo()
{
    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    Editor::IEditor *ed = pm->getObject<Editor::IEditor>();
    if (!ed)
        return;
    ed->undo();
}

void MainWindowImpl::redo()
{
    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    Editor::IEditor *ed = pm->getObject<Editor::IEditor>();
    if (!ed)
        return;
    ed->redo();
}

void MainWindowImpl::cut()
{
    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    Editor::IEditor *ed = pm->getObject<Editor::IEditor>();
    if (!ed)
        return;
    ed->cut();
}

void MainWindowImpl::copy()
{
    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    Editor::IEditor *ed = pm->getObject<Editor::IEditor>();
    if (!ed)
        return;
    ed->copy();
}

void MainWindowImpl::paste()
{
    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    Editor::IEditor *ed = pm->getObject<Editor::IEditor>();
    if (!ed)
        return;
    ed->paste();
}

void MainWindowImpl::selectAll()
{
    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    Editor::IEditor *ed = pm->getObject<Editor::IEditor>();
    if (!ed)
        return;
    ed->selectAll();
}
