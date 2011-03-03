/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2010 Andrew Fillebrown.
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

#include "fpoint.h"

#include <databaseplugin/classes/object.h>

namespace AudioCarver {

namespace Internal {
class FCurvePrivate;
} // namespace Internal

class FCurve : public Database::Object
{
    Q_OBJECT

public:
    FCurve(QObject *parent = 0);
    virtual ~FCurve();

    const QList<FPoint> &points() const;
    int pointCount() const;
    const FPoint &pointAt(int i) const;
    void setPointAt(const FPoint &point, int i);
    int indexOfPoint(const FPoint &point);
    void appendPoint(const FPoint &point);
    void removePoint(const FPoint &point);
    void removePoint(int i);

    virtual bool read(QXmlStreamReader &in);
    virtual void write(QXmlStreamWriter &out) const;

private:
    Internal::FCurvePrivate *d;
};

} // namespace AudioCarver

#endif // AC_FCURVE_H
