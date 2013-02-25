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

#include "mi_core_plugin.h"
#include "mi_core_namespace.h"
#include "mi_core_session.h"
#include <isession.h>
#include <pluginmanager.h>
#include <QtDebug>
#include <QtPlugin>

using namespace Base;

#ifdef QT_DEBUG
static bool test();
#endif

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
#ifdef QT_DEBUG
    test();
#endif
    return true;
}

void Plugin::extensionsInitialized()
{
    ISession::instance()->initialize();
}

}
}

Q_EXPORT_PLUGIN(Mi::Core::Plugin)

#ifdef QT_DEBUG

#include <imodel.h>

#define RUN(x) if (!x()) return false
#define CHECK(x) if (!(x)) { Q_ASSERT(x); return false; }

using namespace Mi::Core;

bool test_1()
{
    return true;
}

bool test()
{
    RUN(test_1);
    qDebug() << "Mi::Core::Plugin tests passed.";
    return true;
}

#endif
