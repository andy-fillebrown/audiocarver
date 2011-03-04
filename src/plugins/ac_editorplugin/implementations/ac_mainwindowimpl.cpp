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

#include "ac_editorconstants.h"

#include <ac_databaseplugin/classes/score.h>
#include <ac_databaseplugin/classes/track.h>

#include <gleditorplugin/gleditorconstants.h>

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

#include <QtCore/QDebug>

using namespace AudioCarver;
using namespace AudioCarver::Internal;

MainWindowImpl::MainWindowImpl()
    :   _versionDialog(0)
{
}

MainWindowImpl::~MainWindowImpl()
{
    _versionDialog = 0;
}

void MainWindowImpl::initMenuBarGroups(QStringList &groups) const
{
    const int viewMenuIndex = groups.indexOf(GLEditor::Constants::G_VIEW);
    groups.insert(viewMenuIndex + 1, Constants::G_CREATE);
    groups.insert(viewMenuIndex + 2, Constants::G_MODIFY);
    groups.insert(viewMenuIndex + 3, Constants::G_BUILD);
}

void MainWindowImpl::initMenuGroups(const QString &menuBarGroup, QString &id, QString &title, QStringList &groups) const
{
    if (menuBarGroup == GLEditor::Constants::G_VIEW) {
        const int viewAllIndex = groups.indexOf(GLEditor::Constants::G_VIEW_ALL);
        groups.insert(viewAllIndex + 1, Constants::G_VIEW_PRESET);
        const int viewProjectionIndex = groups.indexOf(GLEditor::Constants::G_VIEW_PROJECTION);
        groups.insert(viewProjectionIndex + 1, Constants::G_VIEW_SCALE);
    }
    else if (menuBarGroup == Constants::G_CREATE) {
        id = Constants::M_CREATE;
        title = tr("&Create");
    }
    else if (menuBarGroup == Constants::G_MODIFY) {
        id = Constants::M_MODIFY;
        title = tr("&Modify");
    }
    else if (menuBarGroup == Constants::G_BUILD) {
        id = Constants::M_BUILD;
        title = tr("&Build");
    }
    else if (menuBarGroup == Core::Constants::G_HELP)
        groups  << Constants::G_HELP_ABOUTAUDIOCARVER;
}

void MainWindowImpl::initActions()
{
    Core::ActionManager *am = Core::ICore::instance()->actionManager();
    Core::ActionContainer *viewMenu = am->actionContainer(GLEditor::Constants::M_VIEW);
    Core::ActionContainer *createMenu = am->actionContainer(Constants::M_CREATE);
    Core::ActionContainer *modifyMenu = am->actionContainer(Constants::M_MODIFY);
    Core::ActionContainer *buildMenu = am->actionContainer(Constants::M_BUILD);
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

    // Create Track Action
    action = new QAction(tr("Track"), this);
    cmd = am->registerAction(action, Constants::CREATETRACK, globalContext);
    createMenu->addAction(cmd, Core::Constants::G_DEFAULT_ONE);
    connect(action, SIGNAL(triggered()), SLOT(createTrack()));

    // Create Note Action
    action = new QAction(tr("Note"), this);
    cmd = am->registerAction(action, Constants::CREATENOTE, globalContext);
    createMenu->addAction(cmd, Core::Constants::G_DEFAULT_ONE);
    connect(action, SIGNAL(triggered()), SLOT(createNote()));

    // Create Curve Action
    action = new QAction(tr("Curve"), this);
    cmd = am->registerAction(action, Constants::CREATECURVE, globalContext);
    createMenu->addAction(cmd, Core::Constants::G_DEFAULT_ONE);
    connect(action, SIGNAL(triggered()), SLOT(createCurve()));

    // Erase Action (Modify menu).
    action = new QAction(tr("Erase"), this);
    cmd = am->registerAction(action, Constants::ERASE, globalContext);
    cmd->setKeySequence(QKeySequence(Qt::Key_Delete));
    modifyMenu->addAction(cmd, Core::Constants::G_DEFAULT_ONE);
    connect(action, SIGNAL(triggered()), SLOT(erase()));

    // Build All Action
    action = new QAction(tr("Build All"), this);
    cmd = am->registerAction(action, Constants::BUILDALL, globalContext);
    cmd->setKeySequence(QKeySequence("Ctrl+Shift+F7"));
    buildMenu->addAction(cmd, Core::Constants::G_DEFAULT_ONE);
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

void MainWindowImpl::createTrack()
{
    Score *score = Score::instance();

    Database::Object *track = score->createObject("Track");
    track->setParent(score);

    score->tracks()->append(track);
}

void MainWindowImpl::createNote()
{
    Score *score = Score::instance();

    if (score->tracks()->count() == 0)
        createTrack();

    Track *track = qobject_cast<Track*>(score->tracks()->data()[0]);
    Q_ASSERT(track);

    Database::Object *note = score->createObject("Note");
    note->setParent(track);

    track->notes()->append(note);
}

void MainWindowImpl::createCurve()
{
    Score *score = Score::instance();

    Database::Object *curve = score->createObject("FCurve");
    curve->setParent(score);

    score->curves()->append(curve);
}

void MainWindowImpl::erase()
{
    qDebug() << Q_FUNC_INFO;
}

void MainWindowImpl::buildAll()
{
    qDebug() << Q_FUNC_INFO;
}

void MainWindowImpl::aboutAudioCarver()
{
    qDebug() << Q_FUNC_INFO;

    if (!_versionDialog) {
        _versionDialog = new Core::VersionDialog(Core::ICore::instance()->mainWindow());
        connect(_versionDialog, SIGNAL(finished(int)), SLOT(destroyVersionDialog()));
    }
    _versionDialog->show();
}

void MainWindowImpl::destroyVersionDialog()
{
    if (_versionDialog) {
        _versionDialog->deleteLater();
        _versionDialog = 0;
    }
}
