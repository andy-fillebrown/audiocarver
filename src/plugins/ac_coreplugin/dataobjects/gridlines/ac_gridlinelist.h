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
#include <ac_propertyindexes.h>
#include <mi_sortedlistobject.h>

class AcGridLine;

#define AcGridLineListPrivate MiSortedListObjectPrivate

class AC_CORE_EXPORT AcGridLineList : public MiSortedListObject
{
    Q_OBJECT

public:
    explicit AcGridLineList(int propertyIndex = GridLineList::Children)
        :   MiSortedListObject(*(new AcGridLineListPrivate(this, propertyIndex)))
    {}

    ~AcGridLineList()
    {}

    const QList<AcGridLine*> &children() const;
    bool isSorted() const;
    void sort();
    void addChild(MiObject *child);

private:
    Q_DISABLE_COPY(AcGridLineList)
    Q_DECLARE_PRIVATE(AcGridLineList)
};

class AcTimeLineList : public AcGridLineList
{
    Q_OBJECT

public:
    AcTimeLineList(int propertyIndex = TimeLineList::Children)
        :   AcGridLineList(propertyIndex)
    {}
};

class AcPitchLineList : public AcGridLineList
{
    Q_OBJECT

public:
    AcPitchLineList(int propertyIndex = PitchLineList::Children)
        :   AcGridLineList(propertyIndex)
    {}
};

class AcVolumeLineList : public AcGridLineList
{
    Q_OBJECT

public:
    AcVolumeLineList(int propertyIndex = VolumeLineList::Children)
        :   AcGridLineList(propertyIndex)
    {}
};

Q_DECLARE_METATYPE(AcGridLineList*)

#endif // AC_GRIDLINELIST_H
