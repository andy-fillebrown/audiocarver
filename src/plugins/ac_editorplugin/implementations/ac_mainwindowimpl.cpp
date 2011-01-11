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

#include "ac_mainwindowimpl.h"

#include "../ac_editorconstants.h"

#include <editorplugin3d/editor3dconstants.h>

#include <editorplugin/editorconstants.h>

#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/command.h>

#include <coreplugin/icontext.h>
#include <coreplugin/icore.h>
#include <coreplugin/mainwindow.h>
#include <coreplugin/versiondialog.h>

#include <QtGui/QAction>
#include <QtGui/QMenu>

using namespace AudioCarver;
using namespace AudioCarver::Internal;

MainWindowImpl::MainWindowImpl()
    :   m_versionDialog(0)
{
}

MainWindowImpl::~MainWindowImpl()
{
    m_versionDialog = 0;
}

void MainWindowImpl::initMenuBarGroups(QStringList &groups) const
{
}

void MainWindowImpl::initMenuGroups(const QString &menuBarGroup, QString &id, QString &title, QStringList &groups) const
{
    if (menuBarGroup == Editor3D::Constants::G_VIEW) {
        const int viewAllIndex = groups.indexOf(Editor3D::Constants::G_VIEW_ALL);
        groups.insert(viewAllIndex + 1, Constants::G_VIEW_PRESET);
        const int viewProjectionIndex = groups.indexOf(Editor3D::Constants::G_VIEW_PROJECTION);
        groups.insert(viewProjectionIndex + 1, Constants::G_VIEW_SCALE);
    }
    else if (menuBarGroup == Core::Constants::G_HELP)
        groups  << Constants::G_HELP_ABOUTAUDIOCARVER;
}

void MainWindowImpl::initActions()
{
    Core::ActionManager *am = Core::ICore::instance()->actionManager();
    Core::ActionContainer *viewMenu = am->actionContainer(Editor3D::Constants::M_VIEW);
    Core::ActionContainer *helpMenu = am->actionContainer(Core::Constants::M_HELP);
    Core::Context globalContext(Core::Constants::C_GLOBAL);

    QIcon icon;
    QAction *action = 0;
    Core::Command *cmd = 0;
    Core::ActionContainer *subMenu = 0;

    // View Preset Separator
    action = new QAction(this);
    action->setSeparator(true);
    cmd = am->registerAction(action, PRO_NAME_STR".View.Sep.Preset", globalContext);
    viewMenu->addAction(cmd, Constants::G_VIEW_PRESET);

    // View Front Action
    action = new QAction(tr("&Front"), this);
    cmd = am->registerAction(action, Constants::VIEWFRONT, globalContext);
    cmd->setDefaultKeySequence(QKeySequence("f"));
    viewMenu->addAction(cmd, Constants::G_VIEW_PRESET);
    connect(action, SIGNAL(triggered()), SLOT(viewFront()));

    // View Side Action
    action = new QAction(tr("&Side"), this);
    cmd = am->registerAction(action, Constants::VIEWSIDE, globalContext);
    cmd->setDefaultKeySequence(QKeySequence("s"));
    viewMenu->addAction(cmd, Constants::G_VIEW_PRESET);
    connect(action, SIGNAL(triggered()), SLOT(viewSide()));

    // View Bottom Action
    action = new QAction(tr("&Bottom"), this);
    cmd = am->registerAction(action, Constants::VIEWBOTTOM, globalContext);
    cmd->setDefaultKeySequence(QKeySequence("b"));
    viewMenu->addAction(cmd, Constants::G_VIEW_PRESET);
    connect(action, SIGNAL(triggered()), SLOT(viewBottom()));

    // View Scale Sub-Menu
    subMenu = am->createMenu(Constants::M_VIEW_SCALE);
    subMenu->menu()->setTitle(tr("Scale"));
    viewMenu->addMenu(subMenu, Constants::G_VIEW_SCALE);

    // View Scale Increase X Action
    action = new QAction(tr("Increase X"), this);
    cmd = am->registerAction(action, Constants::VIEWSCALEINCREASEX, globalContext);
    cmd->setDefaultKeySequence(QKeySequence("."));
    subMenu->addAction(cmd, Core::Constants::G_DEFAULT_ONE);
    connect(action, SIGNAL(triggered()), SLOT(viewScaleIncreaseX()));

    // View Scale Decrease X Action
    action = new QAction(tr("Decrease X"), this);
    cmd = am->registerAction(action, Constants::VIEWSCALEDECREASEX, globalContext);
    cmd->setDefaultKeySequence(QKeySequence(","));
    subMenu->addAction(cmd, Core::Constants::G_DEFAULT_ONE);
    connect(action, SIGNAL(triggered()), SLOT(viewScaleDecreaseX()));

    // View Scale Increase Z Action
    action = new QAction(tr("Increase Z"), this);
    cmd = am->registerAction(action, Constants::VIEWSCALEINCREASEZ, globalContext);
    cmd->setDefaultKeySequence(QKeySequence("Ctrl+."));
    subMenu->addAction(cmd, Core::Constants::G_DEFAULT_ONE);
    connect(action, SIGNAL(triggered()), SLOT(viewScaleIncreaseZ()));

    // View Scale Decrease Z Action
    action = new QAction(tr("Decrease Z"), this);
    cmd = am->registerAction(action, Constants::VIEWSCALEDECREASEZ, globalContext);
    cmd->setDefaultKeySequence(QKeySequence("Ctrl+,"));
    subMenu->addAction(cmd, Core::Constants::G_DEFAULT_ONE);
    connect(action, SIGNAL(triggered()), SLOT(viewScaleDecreaseZ()));

    // About Project Action
    icon = QIcon::fromTheme(QLatin1String("help-about"));
#   ifdef Q_WS_MAC
    {   action = new QAction(icon, tr("About &"PRO_NAME_STR), this); // it's convention not to add dots to the about menu
    }
#   else
    {   action = new QAction(icon, tr("About &"PRO_NAME_STR"..."), this);
    }
#   endif
    cmd = am->registerAction(action, Constants::ABOUTAUDIOCARVER, globalContext);
    helpMenu->addAction(cmd, Constants::G_HELP_ABOUTAUDIOCARVER);
    action->setEnabled(true);
#   ifdef Q_WS_MAC
    {   cmd->action()->setMenuRole(QAction::ApplicationSpecificRole);
    }
#   endif
    connect(action, SIGNAL(triggered()), SLOT(aboutAudioCarver()));
}

void MainWindowImpl::viewFront()
{
    qDebug() << Q_FUNC_INFO;
}

void MainWindowImpl::viewSide()
{
    qDebug() << Q_FUNC_INFO;
}

void MainWindowImpl::viewBottom()
{
    qDebug() << Q_FUNC_INFO;
}

void MainWindowImpl::viewScaleIncreaseX()
{
    qDebug() << Q_FUNC_INFO;
}

void MainWindowImpl::viewScaleDecreaseX()
{
    qDebug() << Q_FUNC_INFO;
}

void MainWindowImpl::viewScaleIncreaseZ()
{
    qDebug() << Q_FUNC_INFO;
}

void MainWindowImpl::viewScaleDecreaseZ()
{
    qDebug() << Q_FUNC_INFO;
}

void MainWindowImpl::aboutAudioCarver()
{
    if (!m_versionDialog) {
        m_versionDialog = new Core::VersionDialog(Core::ICore::instance()->mainWindow());
        connect(m_versionDialog, SIGNAL(finished(int)), SLOT(destroyVersionDialog()));
    }
    m_versionDialog->show();
}

void MainWindowImpl::destroyVersionDialog()
{
    if (m_versionDialog) {
        m_versionDialog->deleteLater();
        m_versionDialog = 0;
    }
}
