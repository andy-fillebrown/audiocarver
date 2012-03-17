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

#ifndef AC_GRIDSETTINGS_H
#define AC_GRIDSETTINGS_H

#include <ac_graphicsparent.h>
#include <ac_namespace.h>

#include <mi_objectlist.h>

class ControlGridLine;
class PitchGridLine;
class Score;
class TimeGridLine;

class GridSettingsPrivate;
class AC_CORE_EXPORT GridSettings : public GraphicsParent
{
    Q_OBJECT
    Q_PROPERTY(bool snapEnabled READ isSnapEnabled WRITE setSnapEnabled)
    Q_PROPERTY(qreal timeSnap READ timeSnap WRITE setTimeSnap)
    Q_PROPERTY(qreal pitchSnap READ pitchSnap WRITE setPitchSnap)
    Q_PROPERTY(qreal controlSnap READ controlSnap WRITE setControlSnap)

public:
    enum { Type = Ac::GridSettingsItem };
    enum { ModelItemCount = 3 };

    explicit GridSettings(QObject *parent = 0);

    Score *score() const;

    bool isSnapEnabled() const;
    void setSnapEnabled(bool enabled);
    qreal timeSnap() const;
    void setTimeSnap(qreal snap);
    qreal pitchSnap() const;
    void setPitchSnap(qreal snap);
    qreal controlSnap() const;
    void setControlSnap(qreal snap);

    ObjectTList<TimeGridLine> *timeGridLines() const;
    ObjectTList<PitchGridLine> *pitchGridLines() const;
    ObjectTList<ControlGridLine> *controlGridLines() const;

    void clear();

    // IModelItem
    int type() const { return Type; }
    int modelItemCount() const { return ModelItemCount; }
    int modelItemIndex(const IModelItem *item) const;
    IModelItem *modelItemAt(int i) const;
    IModelItem *findModelItemList(int type) const;

    int persistentRoleAt(int i) const
    {
        switch (i - staticMetaObject.propertyOffset()) {
        case 0:
            return Ac::SnapEnabledRole;
        case 1:
            return Ac::TimeSnapRole;
        case 2:
            return Ac::PitchSnapRole;
        case 3:
            return Ac::ControlSnapRole;
        default:
            return GraphicsParent::persistentRoleAt(i);
        }
    }

    QVariant data(int role) const;
    bool setData(const QVariant &value, int role);

private:
    Q_DECLARE_PRIVATE(GridSettings)

    friend class GridLinePrivate;
};

class GridSettingsPrivate : public GraphicsParentPrivate
{
    Q_DECLARE_PUBLIC(GridSettings)

public:
    uint snapEnabled : bitsizeof(uint);
    qreal timeSnap;
    qreal pitchSnap;
    qreal controlSnap;
    ObjectTList<TimeGridLine> *timeGridLines;
    ObjectTList<PitchGridLine> *pitchGridLines;
    ObjectTList<ControlGridLine> *controlGridLines;

    GridSettingsPrivate(GridSettings *q);
    void init();
    ~GridSettingsPrivate();

    GraphicsParentPrivate *graphicsParent() const;
};

#endif // AC_GRIDSETTINGS_H
