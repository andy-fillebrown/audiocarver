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

#ifndef MI_PROPERTYINDEXES_H
#define MI_PROPERTYINDEXES_H

namespace Properties {

namespace Object { enum Index {
    Id = 0,
    Count
};}

namespace ListObject {
typedef Object::Index Index;
}

namespace SortedListObject {
typedef ListObject::Index Index;
}

namespace FontSettings { enum Index {
    Family = Object::Count,
    PointSize,
    Count
};}

} // namespace Properties

#endif // MI_PROPERTYINDEXES_H
