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

#include "ac_sceneplugin.h"

#include <implementations/scene.h>

#include <extensionsystem/pluginmanager.h>

#include <QtCore/QtPlugin>

using namespace AudioCarver;
using namespace AudioCarver::Internal;

ScenePlugin::ScenePlugin()
{
}

ScenePlugin::~ScenePlugin()
{
}

bool ScenePlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorMessage);

    addAutoReleasedObject(new SceneImpl);

    return true;
}

void ScenePlugin::extensionsInitialized()
{
}

Q_EXPORT_PLUGIN(ScenePlugin)
