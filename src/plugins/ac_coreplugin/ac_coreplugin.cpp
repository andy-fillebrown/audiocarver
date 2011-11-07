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

#include "ac_coreplugin.h"

#include <ac_database.h>
#include <ac_factory.h>
#include <ac_model.h>

#include <pluginmanager.h>

#include <QtPlugin>

bool AcCorePlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorMessage);
    addAutoReleasedObject(new ObjectFactory);
    addAutoReleasedObject(new FilerFactory);
    addAutoReleasedObject(new Database);
    addAutoReleasedObject(new Model);
    return true;
}

Q_EXPORT_PLUGIN(AcCorePlugin)
