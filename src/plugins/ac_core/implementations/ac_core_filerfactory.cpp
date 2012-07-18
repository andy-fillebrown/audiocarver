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

#include "ac_core_filerfactory.h"

#include "ac_core_xmlfilefiler.h"

#include <ac_core_database.h>
#include <ac_core_namespace.h>

namespace Ac {
namespace Core {

IAggregate *FilerFactory::init()
{
    return this;
}

IAggregator *FilerFactory::create(int filerType)
{
    switch (filerType) {
    case FileFiler:
        return (new XmlFileFiler)->init();
    default:
        return 0;
    }
}

IAggregator *FilerFactory::aggregator() const
{
    return _aggregator;
}

} // namespace Core
} // namespace Ac
