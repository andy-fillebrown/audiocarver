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

#include "mi_isession.h"

#include "mi_core_session_aggregate.h"

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
    (new Session::Aggregate)->initialize();
#ifdef QT_DEBUG
    test();
#endif
    return true;
}

Plugin::~Plugin()
{
    delete ISession::instance();
}

}
}

Q_EXPORT_PLUGIN(Mi::Core::Plugin)

#ifdef QT_DEBUG

#include "mi_imodel.h"
#include "mi_qimodel.h"

#define RUN(x) if (!x()) return false
#define CHECK(x) if (!(x)) { Q_ASSERT(x); return false; }

using namespace Mi::Core;

bool test_1()
{
    // Make sure querying for interfaces works correctly.
    IAggregate *session = ISession::instance();
    IModel *model_i = 0;
    QIModel *model_qi = 0;
    model_i = IModel::instance();
    CHECK(model_i);
    model_qi = QIModel::instance();
    CHECK(model_qi);
    model_i = 0;
    model_i = query<IModel>(session);
    CHECK(model_i);
    model_qi = 0;
    model_qi = query<QIModel>(session);
    CHECK(model_qi);
    model_i = 0;
    model_i = query<IModel>(model_qi);
    CHECK(model_i);
    model_qi = 0;
    model_qi = query<QIModel>(model_i);
    CHECK(model_qi);
    return true;
}

bool test()
{
//    RUN(test_1);
//    qDebug() << "Mi::Core::Plugin tests passed.";
    return true;
}

#endif
