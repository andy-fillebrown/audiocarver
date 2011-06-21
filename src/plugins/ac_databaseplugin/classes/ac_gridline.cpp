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

#include "ac_gridline.h"
#include <mi_list.h>

using namespace Private;

namespace Private {

class AcGridLineData
{
public:
    qreal location;
    QColor color;
    QString label;
    int priority;

    AcGridLineData()
        :   location(0.0f)
        ,   color(Qt::lightGray)
        ,   label(QString())
        ,   priority(0)
    {}
};

} // namespace Private

AcGridLine::AcGridLine(QObject *parent)
    :   MiObject(parent)
    ,   d(new AcGridLineData)
{}

AcGridLine::~AcGridLine()
{
    delete d;
}

qreal AcGridLine::location() const
{
    return d->location;
}

void AcGridLine::setLocation(qreal location)
{
    if (location < 0.0f)
        location = 0.0f;
    if (d->location == location)
        return;
    d->location = location;
    emit propertyChanged("location");
}

const QColor &AcGridLine::color() const
{
    return d->color;
}

void AcGridLine::setColor(const QColor &color)
{
    if (d->color == color)
        return;
    d->color = color;
    emit propertyChanged("color");
}

const QString &AcGridLine::label() const
{
    return d->label;
}

void AcGridLine::setLabel(const QString &label)
{
    if (d->label == label)
        return;
    d->label = label;
    emit propertyChanged("label");
}

int AcGridLine::priority() const
{
    return d->priority;
}

void AcGridLine::setPriority(int priority)
{
    if (priority < 0)
        priority = 0;
    if (d->priority == priority)
        return;
    d->priority = priority;
    emit propertyChanged("priority");
}
