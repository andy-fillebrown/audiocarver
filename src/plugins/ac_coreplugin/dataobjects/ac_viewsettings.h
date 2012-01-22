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

#ifndef AC_VIEWSETTINGS_H
#define AC_VIEWSETTINGS_H

#include <ac_coreconstants.h>
#include <ac_namespace.h>

#include <mi_object.h>

class Score;

class ViewSettingsPrivate;
class ViewSettings : public Object
{
    Q_OBJECT
    Q_PROPERTY(qreal timePosition READ timePosition WRITE setTimePosition)
    Q_PROPERTY(qreal pitchPosition READ pitchPosition WRITE setPitchPosition)
    Q_PROPERTY(qreal controlPosition READ controlPosition WRITE setControlPosition)
    Q_PROPERTY(qreal timeScale READ timeScale WRITE setTimeScale)
    Q_PROPERTY(qreal pitchScale READ pitchScale WRITE setPitchScale)
    Q_PROPERTY(qreal controlScale READ controlScale WRITE setControlScale)

public:
    enum { Type = Ac::ViewSettingsItem };

    explicit ViewSettings(QObject *parent = 0);

    Score *score() const;

    void clear();

    // Properties
    qreal timePosition() const;
    void setTimePosition(qreal pos);
    qreal pitchPosition() const;
    void setPitchPosition(qreal pos);
    qreal controlPosition() const;
    void setControlPosition(qreal pos);
    qreal timeScale() const;
    void setTimeScale(qreal scale);
    qreal pitchScale() const;
    void setPitchScale(qreal scale);
    qreal controlScale() const;
    void setControlScale(qreal scale);

    // IModelItem
    int type() const { return Type; }

    int persistentRoleAt(int i) const
    {
        switch (i - staticMetaObject.propertyOffset()) {
        case 0:
            return Ac::TimePositionRole;
        case 1:
            return Ac::PitchPositionRole;
        case 2:
            return Ac::ControlPositionRole;
        case 3:
            return Ac::TimeScaleRole;
        case 4:
            return Ac::PitchScaleRole;
        case 5:
            return Ac::ControlScaleRole;
        default:
            return Object::persistentRoleAt(i);
        }
    }

    QVariant data(int role) const;
    bool setData(const QVariant &value, int role);

private:
    Q_DECLARE_PRIVATE(ViewSettings)
};

class ViewSettingsPrivate : public ObjectPrivate
{
    Q_DECLARE_PUBLIC(ViewSettings)

public:
    qreal timePos;
    qreal pitchPos;
    qreal controlPos;
    qreal timeScale;
    qreal pitchScale;
    qreal controlScale;

    ViewSettingsPrivate(ViewSettings *q)
        :   ObjectPrivate(q)
        ,   timePos(64.0f)
        ,   pitchPos(63.5f)
        ,   controlPos(0.5f)
        ,   timeScale(VIEWSCALE_MIN)
        ,   pitchScale(VIEWSCALE_MIN)
        ,   controlScale(VIEWSCALE_MIN)
    {}

    void clear()
    {
        timePos = 0.0f;
        pitchPos = 0.0f;
        controlPos = 0.0f;
        timeScale = -1.0f;
        pitchScale = -1.0f;
        controlScale = -1.0f;
    }
};

#endif // AC_VIEWSETTINGS_H
