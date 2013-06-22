/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2012 Andrew Fillebrown.
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

#include "mi_audioengine_plugin.h"
#include "mi_audioengine_dialog.h"
#include "mi_audioengine_dialogupdater.h"
#include <QtPlugin>

using namespace ExtensionSystem;

namespace Mi {
namespace AudioEngine {

bool Plugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    addAutoReleasedObject(new AudioEngineDialog);
    new ::AudioEngine::DialogUpdater;
    return true;
}

IPlugin::ShutdownFlag Plugin::aboutToShutdown()
{
    return SynchronousShutdown;
}

}
}

Q_EXPORT_PLUGIN(Mi::AudioEngine::Plugin)
