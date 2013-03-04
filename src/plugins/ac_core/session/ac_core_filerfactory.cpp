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

#include "ac_core_filerfactory.h"
#include "ac_core_filefiler.h"
#include "ac_core_namespace.h"
#include "ac_core_reader.h"
#include "ac_core_writer.h"
#include <mi_core_base_aggregate.h>

using namespace Ac;

namespace Core {

IAggregate *FilerFactory::create(int filerType)
{
    IAggregate *aggregate = new Base::Aggregate;
    switch (filerType) {
    case FileFiler:
        new Xml::FileFiler(aggregate);
        new Xml::Reader(aggregate);
        new Xml::Writer(aggregate);
        break;
    default:
        delete aggregate;
        return 0;
    }
    aggregate->initialize();
    return aggregate;
}

}
