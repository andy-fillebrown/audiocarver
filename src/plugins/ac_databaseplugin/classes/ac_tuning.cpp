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

#include "ac_tuning.h"

#include <mi_list.h>

using namespace Private;

namespace Private {

class AcTuningData : public MiLinkableObjectData
{
public:
    qreal cents;
    QColor color;
    int priority;

    AcTuningData(AcTuning *q)
        :   MiLinkableObjectData(q)
        ,   cents(0.0f)
        ,   color(Qt::black)
        ,   priority(0)
    {}
};

} // namespace Private

AcTuning::AcTuning(QObject *parent)
    :   MiObject(parent)
    ,   d(new AcTuningData(this))
{}

AcTuning::~AcTuning()
{
    delete d;
}

qreal AcTuning::cents() const
{
    return d->cents;
}

void AcTuning::setCents(qreal cents)
{
    if (d->cents == cents)
        return;
    d->cents = cents;
    emit propertyChanged(propertyIndex("cents"));
}

const QColor &AcTuning::color() const
{
    return d->color;
}

void AcTuning::setColor(const QColor &color)
{
    if (d->color == color)
        return;
    d->color = color;
    emit propertyChanged(propertyIndex("color"));
}

int AcTuning::priority() const
{
    return d->priority;
}

void AcTuning::setPriority(int priority)
{
    if (d->priority == priority)
        return;
    d->priority = priority;
    emit propertyChanged(propertyIndex("priority"));
}
