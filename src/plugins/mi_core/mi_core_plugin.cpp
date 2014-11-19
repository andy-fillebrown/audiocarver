/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2013 Andrew Fillebrown.
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

#include "mi_core_plugin.h"
#include "mi_core_base_session.h"
#include "mi_core_namespace.h"
#include <isession.h>
#include <pluginmanager.h>
#include <QtPlugin>

using namespace Base;

namespace Mi {
namespace Core {

Plugin::Plugin()
{
    new Session;
}

Plugin::~Plugin()
{
    delete ISession::instance();
}

bool Plugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    appendItemDataRole(ItemTypeRole, "type");
    appendItemDataRole(ListTypeRole, "listType");
    appendItemDataRole(NameRole, "name");
    return true;
}

void Plugin::extensionsInitialized()
{
    ISession::instance()->initialize();
}

}
}

//Q_EXPORT_PLUGIN(Mi::Core::Plugin)
