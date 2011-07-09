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

#ifndef AC_POINT_H
#define AC_POINT_H

#include <mi_object.h>
#include <ac_database_global.h>

namespace Private {

class AcPointData;

} // namespace Private

class AC_DATABASE_EXPORT AcPoint : public MiObject
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX)
    Q_PROPERTY(qreal y READ y WRITE setY)
    Q_PROPERTY(bool curved READ isCurved WRITE setCurved)

public:
    AcPoint(QObject *parent = 0);
    virtual ~AcPoint();

    qreal x() const;
    void setX(qreal x);
    qreal y() const;
    void setY(qreal y);
    bool isCurved() const;
    void setCurved(bool curved);

private:
    Q_DISABLE_COPY(AcPoint)
    Private::AcPointData *d;
};

class AC_DATABASE_EXPORT AcPitchPoint : public AcPoint
{
    Q_OBJECT

public:
    AcPitchPoint(QObject *parent = 0);
    virtual ~AcPitchPoint();

private:
    Q_DISABLE_COPY(AcPitchPoint)
};

class AC_DATABASE_EXPORT AcVolumePoint : public AcPoint
{
    Q_OBJECT

public:
    AcVolumePoint(QObject *parent = 0);
    virtual ~AcVolumePoint();

private:
    Q_DISABLE_COPY(AcVolumePoint)
};

#endif // AC_POINT_H
