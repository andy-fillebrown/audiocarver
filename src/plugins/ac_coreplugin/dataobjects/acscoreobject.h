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

#ifndef ACSCOREOBJECT_H
#define ACSCOREOBJECT_H

#include <acobjectlist.h>

class ControlCurve;
class PitchCurve;

class ScoreObject;
class ScoreObjectPrivate : public ObjectPrivate
{
public:
    qreal volume;
    PitchCurve *pitchCurve;
    ObjectList<ControlCurve> *controlCurves;

    ScoreObjectPrivate(ScoreObject *q);
    void init();
};

class AC_CORE_EXPORT ScoreObject : public Object
{
    Q_OBJECT
    Q_PROPERTY(qreal volume READ volume WRITE setVolume)

public:
    enum { ModelItemCount = 2 };

    virtual qreal length() const = 0;

    qreal volume() const;
    void setVolume(qreal volume);

    ScoreObject *parent() const
    {
        return qobject_cast<ScoreObject*>(QObject::parent());
    }

    PitchCurve *pitchCurve() const;
    ObjectList<ControlCurve> *controlCurves() const;

    // IModelItem
    int modelItemCount() const { return ModelItemCount; }
    int modelItemIndex(IModelItem *item) const;
    IModelItem *modelItemAt(int i) const;
    IModelItem *findModelItem(ItemType type) const;
    IModelItem *findModelItemList(ItemType type) const;
    QVariant data(int role) const;
    bool setData(const QVariant &value, int role);

protected:
    ScoreObject(ScoreObjectPrivate &dd, QObject *parent);

private:
    Q_DISABLE_COPY(ScoreObject)
    Q_DECLARE_PRIVATE(ScoreObject)
};

#endif // ACSCOREOBJECT_H
