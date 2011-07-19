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
#include <mi_objectlist.h>
#include <QMetaType>

namespace Private {

class AcGridLinePrivate : public MiObjectPrivate
{
public:
    qreal location;
    QString label;
    int priority;
    QString color;

    AcGridLinePrivate(MiObject *q)
        :   MiObjectPrivate(q)
        ,   location(0.0f)
        ,   label(QString())
        ,   priority(0)
        ,   color("0xc0c0c0")
    {}

    virtual ~AcGridLinePrivate()
    {}
};

} // namespace Private

class AC_CORE_EXPORT AcGridLine : public MiListObject
{
    Q_OBJECT
    Q_DISABLE_COPY(AcGridLine)
    Q_DECLARE_PRIVATE(Private::AcGridLine)
    Q_PROPERTY(qreal location READ location WRITE setLocation)
    Q_PROPERTY(QString label READ label WRITE setLabel)
    Q_PROPERTY(int priority READ priority WRITE setPriority)
    Q_PROPERTY(QString color READ color WRITE setColor)

public:
    enum Properties {
        Location = MiListObject::PropertyCount,
        Label,
        Priority,
        Color,
        PropertyCount
    };

    explicit AcGridLine(QObject *parent)
        :   MiListObject(*(new Private::AcGridLinePrivate(this)), parent)
    {}

    virtual ~AcGridLine()
    {}

    qreal location() const
    {
        Q_D(const Private::AcGridLine);
        return d->location;
    }

    void setLocation(qreal location)
    {
        Q_D(Private::AcGridLine);
        if (location < 0.0f)
            location = 0.0f;
        if (d->location == location)
            return;
        beginChangeProperty(Location);
        d->location = location;
        endChangeProperty(Location);
        sortList();
    }

    const QString &label() const
    {
        Q_D(const Private::AcGridLine);
        return d->label;
    }

    void setLabel(const QString &label)
    {
        Q_D(Private::AcGridLine);
        if (d->label == label)
            return;
        beginChangeProperty(Label);
        d->label = label;
        endChangeProperty(Label);
    }

    int priority() const
    {
        Q_D(const Private::AcGridLine);
        return d->priority;
    }

    void setPriority(int priority)
    {
        Q_D(Private::AcGridLine);
        if (priority < 0)
            priority = 0;
        if (d->priority == priority)
            return;
        beginChangeProperty(Priority);
        d->priority = priority;
        endChangeProperty(Priority);
    }

    const QString &color() const
    {
        Q_D(const Private::AcGridLine);
        return d->color;
    }

    void setColor(const QString &color)
    {
        Q_D(Private::AcGridLine);
        if (d->color == color)
            return;
        beginChangeProperty(Color);
        d->color = color;
        endChangeProperty(Color);
    }

    void set(qreal location, const QString &label, int priority, const QString &color = QString())
    {
        setLocation(location);
        setLabel(label);
        setPriority(priority);
        if (!color.isEmpty())
            setColor(color);
    }

    void set(qreal location, int priority, const QString &color = QString())
    {
        setLocation(location);
        setPriority(priority);
        if (!color.isEmpty())
            setColor(color);
    }

    static bool lessThan(AcGridLine *a, AcGridLine *b)
    {
        return a->location() < b->location();
    }
};

typedef MiSortedList<AcGridLine> AcGridLineList;
typedef MiList<AcGridLineList> AcGridLinesList;

Q_DECLARE_METATYPE(AcGridLinesList*)

#endif // AC_GRIDLINE_H
