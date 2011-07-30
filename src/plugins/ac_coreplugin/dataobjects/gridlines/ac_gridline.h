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

#ifndef AC_GRIDLINE_H
#define AC_GRIDLINE_H

#include <ac_core_global.h>
#include <mi_scopedchange.h>

class AcGridLinePrivate : public MiObjectPrivate
{
public:
    qreal location;
    QString label;
    int priority;
    quint32 color;

    AcGridLinePrivate(MiObject *q)
        :   MiObjectPrivate(q)
        ,   location(0.0f)
        ,   label(QString())
        ,   priority(0)
        ,   color(0xc0c0c0)
    {}

    virtual ~AcGridLinePrivate()
    {}
};

class AC_CORE_EXPORT AcGridLine : public MiObject
{
    Q_OBJECT
    Q_PROPERTY(qreal location READ location WRITE setLocation)
    Q_PROPERTY(QString label READ label WRITE setLabel)
    Q_PROPERTY(int priority READ priority WRITE setPriority)
    Q_PROPERTY(quint32 color READ color WRITE setColor)

public:
    enum PropertyIndex {
        LocationIndex = MiObject::PropertyCount,
        LabelIndex,
        PriorityIndex,
        ColorIndex,
        PropertyCount
    };

    AcGridLine()
        :   MiObject(*(new AcGridLinePrivate(this)))
    {}

    virtual ~AcGridLine()
    {}

    qreal location() const
    {
        Q_D(const AcGridLine);
        return d->location;
    }

    void setLocation(qreal location)
    {
        Q_D(AcGridLine);
        if (location < 0.0f)
            location = 0.0f;
        if (d->location == location)
            return;
        changing(LocationIndex);
        d->location = location;
    }

    const QString &label() const
    {
        Q_D(const AcGridLine);
        return d->label;
    }

    void setLabel(const QString &label)
    {
        Q_D(AcGridLine);
        if (d->label == label)
            return;
        changing(LabelIndex);
        d->label = label;
    }

    int priority() const
    {
        Q_D(const AcGridLine);
        return d->priority;
    }

    void setPriority(int priority)
    {
        Q_D(AcGridLine);
        if (priority < 0)
            priority = 0;
        if (d->priority == priority)
            return;
        changing(PriorityIndex);
        d->priority = priority;
    }

    const quint32 &color() const
    {
        Q_D(const AcGridLine);
        return d->color;
    }

    void setColor(quint32 color)
    {
        Q_D(AcGridLine);
        if (d->color == color)
            return;
        changing(ColorIndex);
        d->color = color;
    }

    void set(qreal location, const QString &label, int priority, quint32 color = 0xffffffff)
    {
        setLocation(location);
        setLabel(label);
        setPriority(priority);
        if (color != 0xffffffff)
            setColor(color);
    }

    void set(qreal location, int priority, quint32 color = 0xffffffff)
    {
        setLocation(location);
        setPriority(priority);
        if (color != 0xffffffff)
            setColor(color);
    }

    bool isLessThan(const AcGridLine *other) const
    {
        return location() < other->location();
    }

private:
    Q_DISABLE_COPY(AcGridLine)
    Q_DECLARE_PRIVATE(AcGridLine)
    Q_DECLARE_FRIENDS(AcGridLine)
};

#endif // AC_GRIDLINE_H
