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

#ifndef AC_SCOREOBJECT_H
#define AC_SCOREOBJECT_H

#include <ac_graphicsparent.h>
#include <ac_objectlist.h>

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

    virtual qreal length() const = 0;

    qreal volume() const;
    void setVolume(qreal volume);

    PitchCurve *pitchCurve() const;
    ObjectList<ControlCurve> *controlCurves() const;

    // IModelItem
    int modelItemCount() const { return ModelItemCount; }
    int modelItemIndex(IModelItem *item) const;
    IModelItem *modelItemAt(int i) const;
    IModelItem *findModelItem(Ac::ItemType type) const;
    IModelItem *findModelItemList(Ac::ItemType type) const;

    int persistentRoleAt(int i) const
    {
        if (metaObject()->propertyOffset() == i)
            return Ac::VolumeRole;
        return Object::persistentRoleAt(i);
    }

    QVariant data(int role) const;
    bool setData(const QVariant &value, int role);

protected:
    ScoreObject(ScoreObjectPrivate &dd, QObject *parent);

private:
    Q_DISABLE_COPY(ScoreObject)
    Q_DECLARE_PRIVATE(ScoreObject)

    friend class CurvePrivate;
};

class ScoreObjectPrivate : public GraphicsParentPrivate
{
    Q_DECLARE_PUBLIC(ScoreObject)

public:
    qreal volume;
    PitchCurve *pitchCurve;
    ObjectList<ControlCurve> *controlCurves;

    ScoreObjectPrivate(ScoreObject *q);
    void init();
    ~ScoreObjectPrivate();
};

#endif // AC_SCOREOBJECT_H
