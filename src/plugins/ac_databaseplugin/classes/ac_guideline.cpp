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

#include "ac_guideline.h"

using namespace Private;

namespace Private {

class AcGuidelineData
{
public:
    qreal location;
    QColor color;
    QString text;
    int priority;

    AcGuidelineData()
        :   location(0.0f)
        ,   color(Qt::lightGray)
        ,   text(QString())
        ,   priority(0)
    {}
};

} // namespace Private

AcGuideline::AcGuideline(QObject *parent)
    :   MiObject(parent)
    ,   d(new AcGuidelineData)
{}

AcGuideline::~AcGuideline()
{
    delete d;
}

qreal AcGuideline::location() const
{
    return d->location;
}

void AcGuideline::setLocation(qreal location)
{
    if (location < 0.0f)
        location = 0.0f;
    if (d->location == location)
        return;
    d->location = location;
    emit propertyChanged(propertyIndex("location"));
}

const QColor &AcGuideline::color() const
{
    return d->color;
}

void AcGuideline::setColor(const QColor &color)
{
    if (d->color == color)
        return;
    d->color = color;
    emit propertyChanged(propertyIndex("color"));
}

const QString &AcGuideline::text() const
{
    return d->text;
}

void AcGuideline::setText(const QString &text)
{
    if (d->text == text)
        return;
    d->text = text;
    emit propertyChanged(propertyIndex("text"));
}

int AcGuideline::priority() const
{
    return d->priority;
}

void AcGuideline::setPriority(int priority)
{
    if (priority < 0)
        priority = 0;
    if (d->priority == priority)
        return;
    d->priority = priority;
    emit propertyChanged(propertyIndex("priority"));
}
