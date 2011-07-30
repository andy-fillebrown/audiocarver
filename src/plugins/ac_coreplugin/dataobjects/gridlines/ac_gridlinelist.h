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

#ifndef AC_GRIDLINELIST_H
#define AC_GRIDLINELIST_H

#include <ac_core_global.h>
#include <mi_sortedlistobject.h>

#define AcGridLineListPrivate MiSortedListObjectPrivate

class AcGridLineList : public MiSortedListObject
{
    Q_OBJECT

public:
    typedef MiSortedListObject::PropertyIndex PropertyIndex;

    virtual ~AcGridLineList()
    {}

    const QList<AcGridLine*> &children() const;

    virtual bool isSorted() const;
    virtual void sort();

protected:
    AcGridLineList(AcGridLineListPrivate &dd)
        :   MiSortedListObject(dd)
    {}

private:
    Q_DISABLE_COPY(AcGridLineList)
    Q_DECLARE_PRIVATE(AcGridLineList)
};

#endif // AC_GRIDLINELIST_H
