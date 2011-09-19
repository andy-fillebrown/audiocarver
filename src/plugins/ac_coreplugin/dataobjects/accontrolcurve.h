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

#ifndef ACCONTROLCURVE_H
#define ACCONTROLCURVE_H

#include <accurve.h>

class ControlCurvePrivate;
class AC_CORE_EXPORT ControlCurve : public Curve
{
    Q_OBJECT
    Q_PROPERTY(int controlId READ controlId WRITE setControlId)

public:
    explicit ControlCurve(QObject *parent = 0);

    int controlId() const;
    void setControlId(int controlId);

    ScoreObject *graphicsParent() const;

    // IModelItem
    Ac::ItemType type() const { return Ac::ControlCurveItem; }
    QVariant data(int role) const;
    bool setData(const QVariant &value, int role);

private:
    Q_DISABLE_COPY(ControlCurve)
    Q_DECLARE_PRIVATE(ControlCurve)
};

#endif // ACCONTROLCURVE_H
