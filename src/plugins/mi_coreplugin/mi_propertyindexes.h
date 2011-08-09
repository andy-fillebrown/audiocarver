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

struct Object {
    enum Index {
        Id = 0,
        Count
    };
};

struct ListObject : public Object {
    enum Index {
        Children = -1,
        Id = Object::Id,
        Count = Object::Count
    };
};

struct SortedListObject : public ListObject {
    typedef ListObject::Index Index;
};

struct FontSettings : public Object {
    enum Index {
        Family = Object::Count,
        PointSize,
        Count
    };
};

#endif // MI_PROPERTYINDEXES_H
