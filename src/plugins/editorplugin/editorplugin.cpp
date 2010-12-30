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

#include "editorconstants.h"

#include <coreplugin/coreconstants.h>
#include <coreplugin/icontext.h>
#include <coreplugin/icore.h>

#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/command.h>

#include <QtCore/QtPlugin>

#include <QtGui/QAction>

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

    QAction *tmpAction = 0;
    Core::Command *cmd = 0;

    Core::ActionContainer *mfile = am->actionContainer(Core::Constants::M_FILE);
    tmpAction = new QAction(tr("&New"), this);
    cmd = am->registerAction(tmpAction, Constants::NEW, globalContext);
    cmd->setDefaultKeySequence(QKeySequence::New);
    mfile->addAction(cmd, Core::Constants::G_DEFAULT_ONE);
    connect(tmpAction, SIGNAL(triggered()), SLOT(createNewFile()));

    tmpAction = new QAction(tr("&Open"), this);
    cmd = am->registerAction(tmpAction, Constants::OPEN, globalContext);
    cmd->setDefaultKeySequence(QKeySequence::Open);
    mfile->addAction(cmd, Core::Constants::G_DEFAULT_ONE);
    connect(tmpAction, SIGNAL(triggered()), SLOT(openFile()));
}

void EditorPlugin::createNewFile()
{
    qDebug() << Q_FUNC_INFO;
}

void EditorPlugin::openFile()
{
    qDebug() << Q_FUNC_INFO;
}

Q_EXPORT_PLUGIN(EditorPlugin)
