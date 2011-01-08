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

#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/actionmanager/actionmanager.h>

#include <coreplugin/icontext.h>
#include <coreplugin/icore.h>
#include <coreplugin/mainwindow.h>
#include <coreplugin/versiondialog.h>

#include <QtGui/QAction>

using namespace AudioCarver;
using namespace AudioCarver::Internal;

MainWindowImpl::MainWindowImpl()
    :   m_versionDialog(0)
{
}

MainWindowImpl::~MainWindowImpl()
{
}

void MainWindowImpl::initMenuBarGroups(QStringList &groups) const
{
    Q_UNUSED(groups);
}

void MainWindowImpl::initMenuGroups(const QString &menuBarGroup, QString &id, QString &title, QStringList &groups) const
{
    if (menuBarGroup == Core::Constants::G_HELP)
        groups  << Constants::G_HELP_ABOUTAUDIOCARVER;
}

void MainWindowImpl::initActions()
{
    Core::ActionManager *am = Core::ICore::instance()->actionManager();
    Core::ActionContainer *helpMenu = am->actionContainer(Core::Constants::M_HELP);
    Core::Context globalContext(Core::Constants::C_GLOBAL);

    QIcon icon;
    QAction *action = 0;
    Core::Command *cmd = 0;

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
