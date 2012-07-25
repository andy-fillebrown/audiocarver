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

#include <mi_imodel.h>

#include "mi_core_qmodel.h"
#include "mi_core_session.h"

#include <pluginmanager.h>

#include <QtPlugin>

static bool test();

namespace Mi {
namespace Core {

bool Plugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    appendItemDataRole(ItemTypeRole, "type");
    appendItemDataRole(ListTypeRole, "listType");
    appendItemDataRole(ParentRole, "parent");
    appendItemDataRole(NameRole, "name");
    (new Session)->initialize();
#ifdef QT_DEBUG
    test();
#endif
    return true;
}

Plugin::~Plugin()
{
    delete Session::instance();
}

} // namespace Core
} // namespace Mi

Q_EXPORT_PLUGIN(Mi::Core::Plugin)

#ifdef QT_DEBUG

#define RUN(x) if (!x()) return false
#define CHECK(x) if (!(x)) { Q_ASSERT(x); return false; }

using namespace Mi::Core;

bool test_1()
{
    // Make sure query works.
    Session *session = Session::instance();
    IModel *imodel = query<IModel>(session);
    CHECK(imodel);
    QModel *qmodel = query<QModel>(session);
    CHECK(qmodel);
    IModel *imodel_from_qmodel = query<IModel>(qmodel);
    CHECK(imodel_from_qmodel);
    QModel *qmodel_from_imodel = query<QModel>(imodel);
    CHECK(qmodel_from_imodel);
    return true;
}

bool test()
{
    RUN(test_1);
    qDebug() << "Mi::Core::Plugin tests passed.";
    return true;
}

#endif // #ifdef QT_DEBUG
