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

#ifndef GEOMETRY_POINT3D_H
#define GEOMETRY_POINT3D_H

#include <geometry/geometry_global.h>

#include <QtGui/QVector2D>
#include <QtGui/QVector3D>
#include <QtGui/QVector4D>
#include <QtCore/QPoint>

#include <gmtl/Point.h>

namespace Geometry {
namespace Internal {

typedef gmtl::Point<real, 3> Point3DData;

} // namespace Internal

class Matrix4x4;
class Point2D;
class Point4D;
class Vector2D;
class Vector3D;
class Vector4D;

class GEOMETRY_EXPORT Point3D
{
public:
    inline Point3D();
    inline Point3D(real x, real y, real z);
    inline explicit Point3D(const QPoint &point);
    inline explicit Point3D(const QPointF &point);
    inline explicit Point3D(const QVector2D &vector);
    inline explicit Point3D(const QVector3D &vector);
    inline explicit Point3D(const QVector4D &vector);
    explicit Point3D(const Point2D &point);
    explicit Point3D(const Point4D &point);
    explicit Point3D(const Vector2D &vector);
    explicit Point3D(const Vector3D &vector);
    explicit Point3D(const Vector4D &vector);

    inline bool isNull() const;

    inline real x() const;
    inline real y() const;
    inline real z() const;

    inline void setX(real x);
    inline void setY(real y);
    inline void setZ(real z);

    inline Point3D &operator+=(const Point3D &point);
    inline Point3D &operator-=(const Point3D &point);
    inline Point3D &operator*=(real factor);
    inline Point3D &operator*=(const Point3D &point);
    inline Point3D &operator/=(real divisor);

    friend bool operator==(const Point3D &pt1, const Point3D &pt2);
    friend bool operator!=(const Point3D &pt1, const Point3D &pt2);
    friend Point3D operator+(const Point3D &pt1, const Point3D &pt2);
    friend Point3D operator-(const Point3D &pt1, const Point3D &pt2);
    friend Point3D operator*(real factor, const Point3D &point);
    friend Point3D operator*(const Point3D &point, real factor);
    friend Point3D operator*(const Point3D &pt1, const Point3D &pt2);
    friend Point3D operator-(const Point3D &point);
    friend Point3D operator/(const Point3D &point, real divisor);

    friend Point3D operator*(const Matrix4x4 &matrix, const Point3D &point);
    friend Point3D operator*(const Point3D &point, const Matrix4x4 &matrix);

    friend inline bool qFuzzyCompare(const Point3D &pt1, const Point3D &pt2);

    inline QVector2D toVector2D() const;
    inline QVector3D toVector3D() const;
    inline QVector4D toVector4D() const;

    inline QPoint toPoint() const;
    inline QPointF toPointF() const;

    operator QVariant() const;

private:
    Internal::Point3DData d;

    inline Point3D(const Internal::Point3DData &d);

    friend class Point2D;
    friend class Point4D;
    friend class Vector2D;
    friend class Vector3D;
    friend class Vector4D;
};

inline Point3D::Point3D() {}

inline Point3D::Point3D(real x, real y, real z) : d(x, y, z) {}

inline Point3D::Point3D(const QPoint &point) : d(point.x(), point.y(), 0.0f) {}

inline Point3D::Point3D(const QPointF &point) : d(point.x(), point.y(), 0.0f) {}

inline Point3D::Point3D(const QVector2D &vector) : d(vector.x(), vector.y(), 0.0f) {}

inline Point3D::Point3D(const QVector3D &vector) : d(vector.x(), vector.y(), vector.z()) {}

inline Point3D::Point3D(const QVector4D &vector) : d(vector.x(), vector.y(), vector.z()) {}

inline bool Point3D::isNull() const
{
    return qIsNull(d[0]) && qIsNull(d[1]) && qIsNull(d[2]);
}

inline real Point3D::x() const
{
    return d[0];
}

inline real Point3D::y() const
{
    return d[1];
}

inline real Point3D::z() const
{
    return d[2];
}

inline void Point3D::setX(real x)
{
    d[0] = x;
}

inline void Point3D::setY(real y)
{
    d[1] = y;
}

inline void Point3D::setZ(real z)
{
    d[2] = z;
}

inline Point3D &Point3D::operator+=(const Point3D &point)
{
    d[0] += point.d[0];
    d[1] += point.d[1];
    d[2] += point.d[2];
    return *this;
}

inline Point3D &Point3D::operator-=(const Point3D &point)
{
    d[0] -= point.d[0];
    d[1] -= point.d[1];
    d[2] -= point.d[2];
    return *this;
}

inline Point3D &Point3D::operator*=(real factor)
{
    d[0] *= factor;
    d[1] *= factor;
    d[2] *= factor;
    return *this;
}

inline Point3D &Point3D::operator*=(const Point3D &point)
{
    d[0] *= point.d[0];
    d[1] *= point.d[1];
    d[2] *= point.d[2];
    return *this;
}

inline Point3D &Point3D::operator/=(real divisor)
{
    d[0] /= divisor;
    d[1] /= divisor;
    d[2] /= divisor;
    return *this;
}

inline bool operator==(const Point3D &pt1, const Point3D &pt2)
{
    return pt1.d[0] == pt2.d[0] && pt1.d[1] == pt2.d[1] && pt1.d[2] == pt2.d[2];
}

inline bool operator!=(const Point3D &pt1, const Point3D &pt2)
{
    return pt1.d[0] != pt2.d[0] || pt1.d[1] != pt2.d[1] || pt1.d[2] != pt2.d[2];
}

inline Point3D operator+(const Point3D &pt1, const Point3D &pt2)
{
    return Point3D(Internal::Point3DData(pt1.d[0] + pt2.d[0], pt1.d[1] + pt2.d[1], pt1.d[2] + pt2.d[2]));
}

inline Point3D operator-(const Point3D &pt1, const Point3D &pt2)
{
    return Point3D(Internal::Point3DData(pt1.d[0] - pt2.d[0], pt1.d[1] - pt2.d[1], pt1.d[2] - pt2.d[2]));
}

inline Point3D operator*(real factor, const Point3D &point)
{
    return Point3D(Internal::Point3DData(factor * point.d[0], factor * point.d[1], factor * point.d[2]));
}

inline Point3D operator*(const Point3D &point, real factor)
{
    return Point3D(Internal::Point3DData(factor * point.d[0], factor * point.d[1], factor * point.d[2]));
}

inline Point3D operator*(const Point3D &pt1, const Point3D &pt2)
{
    return Point3D(Internal::Point3DData(pt1.d[0] * pt2.d[0], pt1.d[1] * pt2.d[1], pt1.d[2] * pt2.d[2]));
}

inline Point3D operator/(const Point3D &point, real divisor)
{
    return Point3D(Internal::Point3DData(point.d[0] / divisor, point.d[1] / divisor, point.d[2] / divisor));
}

inline bool qFuzzyCompare(const Point3D &pt1, const Point3D &pt2)
{
    return ::qFuzzyCompare(pt1.d[0], pt2.d[0]) &&
           ::qFuzzyCompare(pt1.d[1], pt2.d[1]) &&
           ::qFuzzyCompare(pt1.d[2], pt2.d[2]);
}

inline QVector2D Point3D::toVector2D() const
{
    return QVector2D(d[0], d[1]);
}

inline QVector3D Point3D::toVector3D() const
{
    return QVector3D(d[0], d[1], d[2]);
}

inline QVector4D Point3D::toVector4D() const
{
    return QVector4D(d[0], d[1], d[2], 0.0f);
}

inline QPoint Point3D::toPoint() const
{
    return QPoint(qRound(d[0]), qRound(d[1]));
}

inline QPointF Point3D::toPointF() const
{
    return QPointF(qreal(d[0]), qreal(d[1]));
}

inline Point3D::Point3D(const Internal::Point3DData &d) : d(d) {}

} // namespace Geometry

Q_DECLARE_TYPEINFO(Geometry::Point3D, Q_MOVABLE_TYPE);

#endif // GEOMETRY_POINT3D_H
