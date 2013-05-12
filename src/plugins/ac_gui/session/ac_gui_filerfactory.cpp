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

#include "ac_gui_filerfactory.h"
#include "ac_gui_copyfiler.h"
#include <ac_core_namespace.h>
#include <ac_core_reader.h>
#include <ac_core_writer.h>
#include <mi_core_base_aggregate.h>

namespace Ac {
namespace Gui {

IAggregate *FilerFactory::create(int filerType)
{
    if (CopyFiler == filerType) {
        IAggregate *aggregate = new Base::Aggregate;
        new Xml::CopyFiler(aggregate);
        new Xml::Reader(aggregate);
        new Xml::Writer(aggregate);
        aggregate->initialize();
        return aggregate;
    } else
        return Core::FilerFactory::create(filerType);
}

}
}
