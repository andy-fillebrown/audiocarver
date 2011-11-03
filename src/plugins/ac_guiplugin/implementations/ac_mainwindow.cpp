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

#include "ac_mainwindow.h"

#include <ac_guiconstants.h>

#include <ac_ifactory.h>
#include <ac_namespace.h>

#include <mi_guiconstants.h>
#include <mi_ieditor.h>

#include <mi_imodel.h>

#include <actioncontainer.h>
#include <actionmanager.h>
#include <command.h>
#include <icontext.h>
#include <icore.h>
#include <mainwindow.h>
#include <versiondialog.h>

#include <QAction>
#include <QMenu>

#include <QDebug>

class MainWindowPrivate
{
public:
    Core::VersionDialog *versionDialog;

    MainWindowPrivate()
        :   versionDialog(0)
    {}
};

MainWindow::MainWindow()
    :   d(new MainWindowPrivate)
{}

MainWindow::~MainWindow()
{
    delete d;
}

void MainWindow::initMenuBarGroups(QStringList &groups) const
{
    const int editGroupIndex = groups.indexOf(G_EDIT);
    groups.insert(editGroupIndex + 1, G_CREATE);
    groups.insert(editGroupIndex + 2, G_MODIFY);
    groups.insert(editGroupIndex + 3, G_BUILD);
}

void MainWindow::initMenuGroups(const QString &menuBarGroup, QString &id, QString &title, QStringList &groups) const
{
    if (G_CREATE == menuBarGroup) {
        title = tr("&Create");
        id = M_CREATE;
        groups << G_CREATE_OTHER;
    } else if (G_MODIFY == menuBarGroup) {
        title = tr("&Modify");
        id = M_MODIFY;
        groups << G_MODIFY_OTHER;
    } else if (G_BUILD == menuBarGroup) {
        title = tr("&Build");
        id = M_BUILD;
        groups << G_BUILD_OTHER;
    } else if (Core::Constants::G_HELP == menuBarGroup)
        groups  << G_HELP_ABOUTAUDIOCARVER;
}

void MainWindow::initActions()
{
    Core::ActionManager *am = Core::ICore::instance()->actionManager();

    Core::ActionContainer *createMenu = am->actionContainer(M_CREATE);
    Core::ActionContainer *modifyMenu = am->actionContainer(M_MODIFY);
    Core::ActionContainer *buildMenu = am->actionContainer(M_BUILD);
    Core::ActionContainer *helpMenu = am->actionContainer(Core::Constants::M_HELP);

    Core::Context globalContext(Core::Constants::C_GLOBAL);

    QIcon icon;
    QAction *action = 0;
    Core::Command *cmd = 0;

    // Create Track Action
    action = new QAction(tr("&Track"), this);
    cmd = am->registerAction(action, CREATETRACK, globalContext);
    cmd->setDefaultKeySequence(Qt::Key_Insert);
    createMenu->addAction(cmd, G_CREATE_OTHER);
    connect(action, SIGNAL(triggered()), SLOT(createTrack()));

    // Create Note Action
    action = new QAction(tr("&Note"), this);
    cmd = am->registerAction(action, CREATENOTE, globalContext);
    createMenu->addAction(cmd, G_CREATE_OTHER);
    connect(action, SIGNAL(triggered()), SLOT(createNote()));

    // Erase Action
    action = new QAction(tr("&Erase"), this);
    cmd = am->registerAction(action, ERASE, globalContext);
    cmd->setDefaultKeySequence(QKeySequence::Delete);
    modifyMenu->addAction(cmd, G_MODIFY_OTHER);
    connect(action, SIGNAL(triggered()), SLOT(erase()));

    // Build Action
    action = new QAction(tr("&Build"), this);
    cmd = am->registerAction(action, BUILD, globalContext);
    cmd->setDefaultKeySequence(tr("Ctrl+B"));
    buildMenu->addAction(cmd, G_BUILD_OTHER);
    connect(action, SIGNAL(triggered()), SLOT(build()));

    // Build All Action
    action = new QAction(tr("Build &All"), this);
    cmd = am->registerAction(action, BUILDALL, globalContext);
    cmd->setDefaultKeySequence(tr("Ctrl+Shift+B"));
    buildMenu->addAction(cmd, G_BUILD_OTHER);
    connect(action, SIGNAL(triggered()), SLOT(buildAll()));

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

void MainWindow::aboutAudioCarver()
{
    if (!d->versionDialog) {
        d->versionDialog = new Core::VersionDialog(Core::ICore::instance()->mainWindow());
        connect(d->versionDialog, SIGNAL(finished(int)), SLOT(destroyVersionDialog()));
    }
    d->versionDialog->show();
}

void MainWindow::destroyVersionDialog()
{
    if (d->versionDialog) {
        d->versionDialog->deleteLater();
        d->versionDialog = 0;
    }
}

void MainWindow::createTrack()
{
    IEditor *editor = IEditor::instance();
    editor->beginCommand();
    IModel *model = IModel::instance();
    IModelItem *track = IObjectFactory::instance()->create(Ac::TrackItem);
    model->insertItem(track, 0, model->listIndex(Ac::TrackItem));
    editor->endCommand();
}

void MainWindow::createNote()
{
    qDebug() << Q_FUNC_INFO;
}

void MainWindow::erase()
{
    qDebug() << Q_FUNC_INFO;
}

void MainWindow::build()
{
    qDebug() << Q_FUNC_INFO;
}

void MainWindow::buildAll()
{
    qDebug() << Q_FUNC_INFO;
}
