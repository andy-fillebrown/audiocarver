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

#include "editor3dmainwindowimpl.h"

#include "../interfaces/ieditor3d.h"
#include "../editor3dconstants.h"

#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/command.h>

#include <coreplugin/icontext.h>
#include <coreplugin/icore.h>
#include <coreplugin/mainwindow.h>

#include <extensionsystem/pluginmanager.h>

#include <QtGui/QAction>
#include <QtGui/QMenu>

using namespace Editor3D;
using namespace Editor3D::Internal;

MainWindowImpl::MainWindowImpl()
{
}

MainWindowImpl::~MainWindowImpl()
{
}

void MainWindowImpl::initMenuBarGroups(QStringList &groups) const
{
    const int editGroupIndex = groups.indexOf(Editor::Constants::G_EDIT);
    groups.insert(editGroupIndex + 1, Constants::G_VIEW);
}

void MainWindowImpl::initMenuGroups(const QString &menuBarGroup, QString &id, QString &title, QStringList &groups) const
{
    if (menuBarGroup == Constants::G_VIEW) {
        id = Constants::M_VIEW;
        title = tr("&View");
        groups  << Constants::G_VIEW_ALL
                << Constants::G_VIEW_CAMERA
                << Constants::G_VIEW_PROJECTION
                << Constants::G_VIEW_TRANSPARENCY;
    }
}

void MainWindowImpl::initActions()
{
    Core::ActionManager *am = Core::ICore::instance()->actionManager();
    Core::ActionContainer *viewMenu = am->actionContainer(Constants::M_VIEW);
    Core::Context globalContext(Core::Constants::C_GLOBAL);

    QAction *action = 0;
    Core::Command *cmd = 0;
    Core::ActionContainer *subMenu = 0;

    // View All Action
    action = new QAction(tr("&All"), this);
    cmd = am->registerAction(action, Constants::VIEWALL, globalContext);
    cmd->setDefaultKeySequence(QKeySequence("a"));
    viewMenu->addAction(cmd, Constants::G_VIEW_ALL);
    connect(action, SIGNAL(triggered()), SLOT(viewAll()));

    // View Camera Separator
    action = new QAction(this);
    action->setSeparator(true);
    cmd = am->registerAction(action, PRO_NAME_STR".View.Sep.Camera", globalContext);
    viewMenu->addAction(cmd, Constants::G_VIEW_CAMERA);

    // View Zoom Action
    action = new QAction(tr("&Zoom"), this);
    cmd = am->registerAction(action, Constants::VIEWZOOM, globalContext);
    viewMenu->addAction(cmd, Constants::G_VIEW_CAMERA);
    connect(action, SIGNAL(triggered()), SLOT(viewZoom()));

    // View Pan Action
    action = new QAction(tr("&Pan"), this);
    cmd = am->registerAction(action, Constants::VIEWPAN, globalContext);
    viewMenu->addAction(cmd, Constants::G_VIEW_CAMERA);
    connect(action, SIGNAL(triggered()), SLOT(viewPan()));

    // View Rotate Action
    action = new QAction(tr("&Rotate"), this);
    cmd = am->registerAction(action, Constants::VIEWROTATE, globalContext);
    viewMenu->addAction(cmd, Constants::G_VIEW_CAMERA);
    connect(action, SIGNAL(triggered()), SLOT(viewRotate()));

    // View Projection Separator
    action = new QAction(this);
    action->setSeparator(true);
    cmd = am->registerAction(action, PRO_NAME_STR".View.Sep.Projection", globalContext);
    viewMenu->addAction(cmd, Constants::G_VIEW_PROJECTION);

    // View Projection Sub-Menu
    subMenu = am->createMenu(Constants::M_VIEW_PROJECTION);
    subMenu->menu()->setTitle(tr("Projection"));
    viewMenu->addMenu(subMenu, Constants::G_VIEW_PROJECTION);

    // View Projection Parallel Action
    action = new QAction(tr("Parallel"), this);
    cmd = am->registerAction(action, Constants::VIEWPARALLEL, globalContext);
    subMenu->addAction(cmd, Core::Constants::G_DEFAULT_ONE);
    connect(action, SIGNAL(triggered()), SLOT(viewParallel()));

    // View Projection Perspective Action
    action = new QAction(tr("Perspective"), this);
    cmd = am->registerAction(action, Constants::VIEWPERSPECTIVE, globalContext);
    subMenu->addAction(cmd, Core::Constants::G_DEFAULT_ONE);
    connect(action, SIGNAL(triggered()), SLOT(viewPerspective()));

    // View Transparency Separator
    action = new QAction(this);
    action->setSeparator(true);
    cmd = am->registerAction(action, PRO_NAME_STR".View.Sep.Transparency", globalContext);
    viewMenu->addAction(cmd, Constants::G_VIEW_TRANSPARENCY);

    // View Transparency Sub-Menu
    subMenu = am->createMenu(Constants::M_VIEW_TRANSPARENCY);
    subMenu->menu()->setTitle(tr("Transparency"));
    viewMenu->addMenu(subMenu, Constants::G_VIEW_TRANSPARENCY);

    // View Transparency None Action
    action = new QAction(tr("None"), this);
    cmd = am->registerAction(action, Constants::VIEWTRANSPARENCYNONE, globalContext);
    subMenu->addAction(cmd, Core::Constants::G_DEFAULT_ONE);
    connect(action, SIGNAL(triggered()), SLOT(viewTransparencyNone()));

    // View Transparency Screen Action
    action = new QAction(tr("Screen"), this);
    cmd = am->registerAction(action, Constants::VIEWTRANSPARENCYSCREEN, globalContext);
    subMenu->addAction(cmd, Core::Constants::G_DEFAULT_ONE);
    connect(action, SIGNAL(triggered()), SLOT(viewTransparencyScreen()));

    // View Transparency Full Action
    action = new QAction(tr("Full"), this);
    cmd = am->registerAction(action, Constants::VIEWTRANSPARENCYFULL, globalContext);
    subMenu->addAction(cmd, Core::Constants::G_DEFAULT_ONE);
    connect(action, SIGNAL(triggered()), SLOT(viewTransparencyFull()));
}

void MainWindowImpl::viewAll()
{
    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    IEditor3D *ed = pm->getObject<IEditor3D>();
    if (!ed)
        return;
    ed->viewAll();
}

void MainWindowImpl::viewZoom()
{
    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    IEditor3D *ed = pm->getObject<IEditor3D>();
    if (!ed)
        return;
    ed->viewZoom();
}

void MainWindowImpl::viewPan()
{
    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    IEditor3D *ed = pm->getObject<IEditor3D>();
    if (!ed)
        return;
    ed->viewPan();
}

void MainWindowImpl::viewRotate()
{
    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    IEditor3D *ed = pm->getObject<IEditor3D>();
    if (!ed)
        return;
    ed->viewRotate();
}

void MainWindowImpl::viewParallel()
{
    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    IEditor3D *ed = pm->getObject<IEditor3D>();
    if (!ed)
        return;
    ed->viewParallel();
}

void MainWindowImpl::viewPerspective()
{
    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    IEditor3D *ed = pm->getObject<IEditor3D>();
    if (!ed)
        return;
    ed->viewPerspective();
}

void MainWindowImpl::viewTransparencyNone()
{
    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    IEditor3D *ed = pm->getObject<IEditor3D>();
    if (!ed)
        return;
    ed->viewTransparencyNone();
}

void MainWindowImpl::viewTransparencyScreen()
{
    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    IEditor3D *ed = pm->getObject<IEditor3D>();
    if (!ed)
        return;
    ed->viewTransparencyScreen();
}

void MainWindowImpl::viewTransparencyFull()
{
    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    IEditor3D *ed = pm->getObject<IEditor3D>();
    if (!ed)
        return;
    ed->viewTransparencyFull();
}