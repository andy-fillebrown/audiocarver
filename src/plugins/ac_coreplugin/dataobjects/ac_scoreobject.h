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

#include <ac_graphicsparent.h>
#include <ac_namespace.h>

#include <mi_objectlist.h>

class ControlCurve;
class PitchCurve;

class QGraphicsItem;

class ScoreObjectPrivate;
class AC_CORE_EXPORT ScoreObject : public GraphicsParent
{
    Q_OBJECT
    Q_PROPERTY(qreal volume READ volume WRITE setVolume)

public:
    enum { ModelItemCount = 2 };

    PitchCurve *pitchCurve() const;
    ObjectTList<ControlCurve> *controlCurves() const;

    virtual qreal length() const = 0;

    // Properties
    qreal volume() const;
    void setVolume(qreal volume);

    virtual void updatePoints() {}

    // IModelItem
    int modelItemCount() const { return ModelItemCount; }
    int modelItemIndex(const IModelItem *item) const;
    IModelItem *modelItemAt(int i) const;
    IModelItem *findModelItem(int type) const;
    IModelItem *findModelItemList(int type) const;

    int persistentRoleAt(int i) const
    {
        if (staticMetaObject.propertyOffset() == i)
            return Ac::VolumeRole;
        return Object::persistentRoleAt(i);
    }

    QVariant data(int role) const;
    bool setData(const QVariant &value, int role);

protected:
    ScoreObject(ScoreObjectPrivate &dd, QObject *parent);

private:
    Q_DECLARE_PRIVATE(ScoreObject)

    friend class CurvePrivate;
};

class ScoreObjectPrivate : public GraphicsParentPrivate
{
    Q_DECLARE_PUBLIC(ScoreObject)

public:
    qreal volume;
    PitchCurve *pitchCurve;
    ObjectTList<ControlCurve> *controlCurves;

    ScoreObjectPrivate(ScoreObject *q);
    void init();
    ~ScoreObjectPrivate();
};

#endif // AC_SCOREOBJECT_H
