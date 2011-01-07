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

#include "editorplugin.h"

#include "interfaces/ieditor.h"

#include "editorconstants.h"

#include <extensionsystem/pluginmanager.h>

#include <coreplugin/coreconstants.h>
#include <coreplugin/icontext.h>
#include <coreplugin/icore.h>

#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/command.h>

#include <databaseplugin/interfaces/idatabase.h>

#include <QtCore/QDebug>
#include <QtCore/QtPlugin>

#include <QtGui/QAction>
#include <QtGui/QFileDialog>
#include <QtGui/QMainWindow>

using namespace Editor;
using namespace Editor::Internal;

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
    return true;
}

void EditorPlugin::extensionsInitialized()
{
    Core::ActionManager *am = Core::ICore::instance()->actionManager();
    Core::Context globalContext(Core::Constants::C_GLOBAL);

    QIcon icon;
    QAction *action = 0;
    Core::Command *cmd = 0;

    Core::ActionContainer *fileMenu = am->actionContainer(Core::Constants::M_FILE);

    icon = QIcon::fromTheme(QLatin1String("document-new"), QIcon(Constants::ICON_NEW));
    action = new QAction(icon, tr("&New"), this);
    cmd = am->registerAction(action, Constants::NEW, globalContext);
    cmd->setDefaultKeySequence(QKeySequence::New);
    fileMenu->addAction(cmd, Core::Constants::G_FILE_NEW);
    connect(action, SIGNAL(triggered()), SLOT(newFile()));

    icon = QIcon::fromTheme(QLatin1String("document-open"), QIcon(Constants::ICON_OPEN));
    action = new QAction(icon, tr("&Open"), this);
    cmd = am->registerAction(action, Constants::OPEN, globalContext);
    cmd->setDefaultKeySequence(QKeySequence::Open);
    fileMenu->addAction(cmd, Core::Constants::G_FILE_OPEN);
    connect(action, SIGNAL(triggered()), SLOT(openFile()));

    action = new QAction(this);
    action->setSeparator(true);
    cmd = am->registerAction(action, PRO_NAME_STR".File.Sep.Save", globalContext);
    fileMenu->addAction(cmd, Core::Constants::G_FILE_SAVE);

    icon = QIcon::fromTheme(QLatin1String("document-save"), QIcon(Constants::ICON_SAVE));
    action = new QAction(icon, tr("&Save"), this);
    cmd = am->registerAction(action, Constants::SAVE, globalContext);
    cmd->setDefaultKeySequence(QKeySequence::Save);
    fileMenu->addAction(cmd, Core::Constants::G_FILE_SAVE);
    connect(action, SIGNAL(triggered()), SLOT(saveFile()));

    action = new QAction(tr("Save &As"), this);
    cmd = am->registerAction(action, Constants::SAVEAS, globalContext);
    fileMenu->addAction(cmd, Core::Constants::G_FILE_SAVE);
    connect(action, SIGNAL(triggered()), SLOT(saveFileAs()));

    connect(am->command(Core::Constants::UNDO)->action(), SIGNAL(triggered()), SLOT(undo()));
    connect(am->command(Core::Constants::REDO)->action(), SIGNAL(triggered()), SLOT(redo()));
    connect(am->command(Core::Constants::CUT)->action(), SIGNAL(triggered()), SLOT(cut()));
    connect(am->command(Core::Constants::COPY)->action(), SIGNAL(triggered()), SLOT(copy()));
    connect(am->command(Core::Constants::PASTE)->action(), SIGNAL(triggered()), SLOT(paste()));
    connect(am->command(Core::Constants::SELECTALL)->action(), SIGNAL(triggered()), SLOT(selectAll()));
}

void EditorPlugin::newFile()
{
    qDebug() << Q_FUNC_INFO;

    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();

    // Get database.
    Database::IDatabase *db = pm->getObject<Database::IDatabase>();
    if (!db)
        return;

    // Clear database.
    db->clear();
}

void EditorPlugin::openFile()
{
    qDebug() << Q_FUNC_INFO;

    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();

    // Get database.
    Database::IDatabase *db = pm->getObject<Database::IDatabase>();
    if (!db)
        return;

    // Get filename filter.
    const QString filter = db->fileFilter();

    // Get filename from user.
    QString filename = QFileDialog::getOpenFileName(
                Core::ICore::instance()->mainWindow()->centralWidget(), "", "",
                tr(qPrintable(filter)));
    if (!QFile::exists(filename))
        return;

    // Read file into database.
    db->read(filename);
}

void EditorPlugin::saveFile()
{
    qDebug() << Q_FUNC_INFO;

    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();

    // Get database.
    Database::IDatabase *db = pm->getObject<Database::IDatabase>();
    if (!db)
        return;

    // Write database using current filename.
    db->write(db->fileName());
}

void EditorPlugin::saveFileAs()
{
    qDebug() << Q_FUNC_INFO;

    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();

    // Get database.
    Database::IDatabase *db = pm->getObject<Database::IDatabase>();
    if (!db)
        return;

    // Get filename filter.
    const QString filter = db->fileFilter();

    // Get filename from user.
    QString filename = QFileDialog::getSaveFileName(
                Core::ICore::instance()->mainWindow()->centralWidget(), "", "",
                tr(qPrintable(filter)));
    if (filename.isEmpty())
        return;

    // Add file extension if missing.
    if (!filename.endsWith(db->fileExtension()))
        filename.append(db->fileExtension());

    // Write database using filename chosen by user.
    db->write(filename);
}

void EditorPlugin::undo()
{
    qDebug() << Q_FUNC_INFO;

    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    Editor::IEditor *ed = pm->getObject<Editor::IEditor>();
    if (!ed)
        return;
    ed->undo();
}

void EditorPlugin::redo()
{
    qDebug() << Q_FUNC_INFO;

    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    Editor::IEditor *ed = pm->getObject<Editor::IEditor>();
    if (!ed)
        return;
    ed->redo();
}

void EditorPlugin::cut()
{
    qDebug() << Q_FUNC_INFO;

    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    Editor::IEditor *ed = pm->getObject<Editor::IEditor>();
    if (!ed)
        return;
    ed->cut();
}

void EditorPlugin::copy()
{
    qDebug() << Q_FUNC_INFO;

    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    Editor::IEditor *ed = pm->getObject<Editor::IEditor>();
    if (!ed)
        return;
    ed->copy();
}

void EditorPlugin::paste()
{
    qDebug() << Q_FUNC_INFO;

    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    Editor::IEditor *ed = pm->getObject<Editor::IEditor>();
    if (!ed)
        return;
    ed->paste();
}

void EditorPlugin::selectAll()
{
    qDebug() << Q_FUNC_INFO;

    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    Editor::IEditor *ed = pm->getObject<Editor::IEditor>();
    if (!ed)
        return;
    ed->selectAll();
}

Q_EXPORT_PLUGIN(EditorPlugin)
