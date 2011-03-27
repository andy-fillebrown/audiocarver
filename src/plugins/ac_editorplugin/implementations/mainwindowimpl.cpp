/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2011 Andrew Fillebrown.
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

#include "mainwindowimpl.h"

#include <ac_editorplugin/ac_editorconstants.h>

#include <ac_databaseplugin/classes/score.h>
#include <ac_databaseplugin/classes/track.h>
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

namespace AudioCarver {
namespace Internal {

class MainWindowImplData
{
public:
    Core::VersionDialog *versionDialog;

    MainWindowImplData()
        :   versionDialog(0)
    {}
};

} // namespace Internal
} // namespace AudioCarver

static MainWindowImpl *instance = 0;

MainWindowImpl::MainWindowImpl()
    :   d(new MainWindowImplData)
{
    ::instance = this;
}

MainWindowImpl::~MainWindowImpl()
{
    delete d;
}

MainWindowImpl *MainWindowImpl::instance()
{
    return ::instance;
}

void MainWindowImpl::initMenuBarGroups(QStringList &groups) const
{
    Q_UNUSED(groups);
}

void MainWindowImpl::initMenuGroups(const QString &menuBarGroup, QString &id, QString &title, QStringList &groups) const
{
    Q_UNUSED(id);
    Q_UNUSED(title);
    Q_UNUSED(groups);

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
    if (!d->versionDialog) {
        d->versionDialog = new Core::VersionDialog(Core::ICore::instance()->mainWindow());
        connect(d->versionDialog, SIGNAL(finished(int)), SLOT(destroyVersionDialog()));
    }
    d->versionDialog->show();
}

void MainWindowImpl::destroyVersionDialog()
{
    if (d->versionDialog) {
        d->versionDialog->deleteLater();
        d->versionDialog = 0;
    }
}
