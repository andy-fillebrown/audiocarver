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

#include "mi_core_session.h"

#include "mi_core_model.h"
#include "mi_core_qmodel.h"

static Mi::Core::Session *instance = 0;

namespace Mi {
namespace Core {

Session *Session::instance()
{
    return ::instance;
}

Session::Session()
{
    delete ::instance;
    ::instance = this;
}

QObject *Session::initialize()
{
    (new Model(this))->initialize();
    (new QModel(this))->initialize();
    return this;
}

Session::~Session()
{
    ::instance = 0;
}

void *Session::queryInterface(int interfaceType) const
{
    foreach (QObject *child, children()) {
        QObject *interface = 0;
        switch (interfaceType) {
        case I::QModel:
            interface = qobject_cast<QModel*>(child);
            break;
        }
        if (interface)
            return interface;
    }
    return Aggregate::queryInterface(interfaceType);
}

} // namespace Core
} // namespace Mi
