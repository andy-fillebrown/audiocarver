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

#ifndef AC_SCOREOBJECT_H
#define AC_SCOREOBJECT_H

#include "ac_graphicsparent.h"

#include <ac_namespace.h>
#include <ac_pitchcurve.h>

#include <mi_dataobjectlist.h>

class ControlCurve;
class PitchCurve;

class QGraphicsItem;

class AC_CORE_EXPORT ScoreObject : public GraphicsParent
{
    Q_DECLARE_AGGREGATOR(ScoreObject, GraphicsParent, 1, 2)

    // Properties
    qreal _volume;

    // Items
    QScopedPointer<PitchCurve> _pitchCurve;
    QScopedPointer<DataObjectList> _controlCurves;

protected:
    ScoreObject()
        :   _volume(0.0f)
    {}

    qreal volume() const
    {
        return _volume;
    }

    void setVolume(qreal volume);

    PitchCurve *pitchCurve() const
    {
        return qGetPtrHelper(_pitchCurve);
    }

    DataObjectList *controlCurves() const
    {
        return qGetPtrHelper(_controlCurves);
    }

    virtual qreal length() const = 0;

public:
    virtual void updatePoints()
    {}

protected:
    class ModelItem : public GraphicsParent::ModelItem
    {
        Q_DECLARE_AGGREGATE(ModelItem)

        int count() const
        {
            return TotalRoleCount;
        }

        int indexOf(const IModelItem *item) const;
    };

//    // IModelItem
//    int modelItemCount() const { return ModelItemCount; }
//    int modelItemIndex(const IModelItem *item) const;
//    IModelItem *modelItemAt(int i) const;
//    IModelItem *findModelItem(int type) const;
//    IModelItemList *findModelItemList(int type) const;

//    int persistentRoleAt(int i) const
//    {
//        if (staticMetaObject.propertyOffset() == i)
//            return Ac::VolumeRole;
//        return Object::persistentRoleAt(i);
//        Q_UNUSED(i);
//        return 0;
//    }

//    QVariant data(int role) const;
//    bool setData(const QVariant &value, int role);
};

#endif // AC_SCOREOBJECT_H
