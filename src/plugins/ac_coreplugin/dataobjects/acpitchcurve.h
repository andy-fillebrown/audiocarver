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

#ifndef ACPITCHCURVE_H
#define ACPITCHCURVE_H

#include <accurve.h>

class PitchCurvePrivate;
class AC_CORE_EXPORT PitchCurve : public Curve
{
    Q_OBJECT

public:
    explicit PitchCurve(QObject *parent = 0);

    void setPoints(const PointList &points);

    // IModelItem
    ItemType type() const { return PitchCurveItem; }

private:
    Q_DISABLE_COPY(PitchCurve)
    Q_DECLARE_PRIVATE(PitchCurve)
};

#endif // ACPITCHCURVE_H
