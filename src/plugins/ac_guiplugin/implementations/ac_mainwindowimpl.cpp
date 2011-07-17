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

#include "ac_mainwindowimpl.h"
#include <ac_guiconstants.h>
#include <actioncontainer.h>
#include <actionmanager.h>
#include <command.h>
#include <icontext.h>
#include <icore.h>
#include <mainwindow.h>
#include <mi_guiconstants.h>
#include <QAction>
#include <QMenu>
#include <versiondialog.h>

using namespace Private;

namespace Private {

class AcMainWindowImplData
{
public:
    Core::VersionDialog *versionDialog;

    AcMainWindowImplData()
        :   versionDialog(0)
    {}
};

} // namespace Private

static AcMainWindowImpl *instance = 0;

AcMainWindowImpl::AcMainWindowImpl()
    :   d(new AcMainWindowImplData)
{
    ::instance = this;
}

AcMainWindowImpl::~AcMainWindowImpl()
{
    delete d;
}

AcMainWindowImpl *AcMainWindowImpl::instance()
{
    return ::instance;
}

void AcMainWindowImpl::initMenuBarGroups(QStringList &groups) const
{
    Q_UNUSED(groups);
}

void AcMainWindowImpl::initMenuGroups(const QString &menuBarGroup, QString &id, QString &title, QStringList &groups) const
{
    Q_UNUSED(id);
    Q_UNUSED(title);
    if (menuBarGroup == Core::Constants::G_HELP)
        groups  << G_HELP_ABOUTAUDIOCARVER;
}

void AcMainWindowImpl::initActions()
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
    cmd = am->registerAction(action, ABOUTAUDIOCARVER, globalContext);
    helpMenu->addAction(cmd, G_HELP_ABOUTAUDIOCARVER);
    action->setEnabled(true);
#   ifdef Q_WS_MAC
    {   cmd->action()->setMenuRole(QAction::ApplicationSpecificRole);
    }
#   endif
    connect(action, SIGNAL(triggered()), SLOT(aboutAudioCarver()));
}

void AcMainWindowImpl::aboutAudioCarver()
{
    if (!d->versionDialog) {
        d->versionDialog = new Core::VersionDialog(Core::ICore::instance()->mainWindow());
        connect(d->versionDialog, SIGNAL(finished(int)), SLOT(destroyVersionDialog()));
    }
    d->versionDialog->show();
}

void AcMainWindowImpl::destroyVersionDialog()
{
    if (d->versionDialog) {
        d->versionDialog->deleteLater();
        d->versionDialog = 0;
    }
}
