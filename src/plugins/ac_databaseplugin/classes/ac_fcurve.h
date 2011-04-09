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

#ifndef AC_FCURVE_H
#define AC_FCURVE_H

#include <mi_object.h>

#include <ac_database_global.h>

namespace Private {

class AcFCurveData;

} // namespace Private

class AcFPoint;

class AC_DATABASE_EXPORT AcFCurve : public MiObject
{
    Q_OBJECT

public:
    AcFCurve(QObject *parent = 0);
    virtual ~AcFCurve();

    const QList<AcFPoint> &points() const;
    int pointCount() const;
    const AcFPoint &pointAt(int i) const;
    void setPointAt(const AcFPoint &point, int i);
    int indexOfPoint(const AcFPoint &point);
    void appendPoint(const AcFPoint &point);
    void removePoint(const AcFPoint &point);
    void removePoint(int i);

    virtual bool read(QXmlStreamReader &in);
    virtual void write(QXmlStreamWriter &out) const;

signals:
    void pointsChanged();

private:
    Q_DISABLE_COPY(AcFCurve)
    Private::AcFCurveData *d;
};

#endif // AC_FCURVE_H
