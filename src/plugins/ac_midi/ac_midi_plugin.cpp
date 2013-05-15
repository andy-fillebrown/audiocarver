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

#include "ac_midi_plugin.h"
#include "ac_midi_mainwindowextension.h"
#include <QtPlugin>

namespace Ac {
namespace Midi {

bool Plugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    addAutoReleasedObject(new MainWindowExtension);
    return true;
}

}
}

Q_EXPORT_PLUGIN(Ac::Midi::Plugin)
