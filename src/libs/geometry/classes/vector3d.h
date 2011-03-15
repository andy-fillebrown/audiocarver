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

#ifndef GEOMETRY_VECTOR3D_H
#define GEOMETRY_VECTOR3D_H

#include <geometry/geometry_global.h>

#include <QtGui/QVector2D>
#include <QtGui/QVector3D>
#include <QtGui/QVector4D>
#include <QtCore/QPoint>

#include <gmtl/VecOps.h>

QT_FORWARD_DECLARE_CLASS(QVariant)

namespace Geometry {
namespace Internal {

typedef gmtl::Vec<real, 3> Vector3DData;

} // namespace Internal

class Point2D;
class Point3D;
class Point4D;
class Vector2D;
class Vector4D;

class GEOMETRY_EXPORT Vector3D
{
public:
    inline Vector3D();
    inline Vector3D(real x, real y, real z);
    inline explicit Vector3D(const QPoint &point);
    inline explicit Vector3D(const QPointF &point);
    inline explicit Vector3D(const QVector2D &vector);
    inline explicit Vector3D(const QVector3D &vector);
    inline explicit Vector3D(const QVector4D &vector);
    explicit Vector3D(const Point2D &vector);
    explicit Vector3D(const Point3D &point);
    explicit Vector3D(const Point4D &point);
    explicit Vector3D(const Vector2D &vector);
    explicit Vector3D(const Vector4D &vector);

    inline bool isNull() const;

    inline real x() const;
    inline real y() const;
    inline real z() const;

    inline void setX(real x);
    inline void setY(real y);
    inline void setZ(real z);

    inline real length() const;
    inline real lengthSquared() const;

    inline bool isNormalized() const;
    inline Vector3D normalized() const;
    inline real normalize();

    inline Vector3D crossProduct(const Vector3D &vector);
    inline real dotProduct(const Vector3D &vector);

    inline Vector3D reflected(const Vector3D &normal) const;
    inline Vector3D &reflect(const Vector3D &normal);

    inline Vector3D lerped(const Vector3D &to, real t);
    inline Vector3D &lerp(const Vector3D &to, real t);

    inline Vector3D &operator+=(const Vector3D &vector);
    inline Vector3D &operator-=(const Vector3D &vector);
    inline Vector3D &operator*=(real factor);
    inline Vector3D &operator*=(const Vector3D &vector);
    inline Vector3D &operator/=(real divisor);

    friend inline bool operator==(const Vector3D &v1, const Vector3D &v2);
    friend inline bool operator!=(const Vector3D &v1, const Vector3D &v2);
    friend inline const Vector3D operator+(const Vector3D &v1, const Vector3D &v2);
    friend inline const Vector3D operator-(const Vector3D &v1, const Vector3D &v2);
    friend inline const Vector3D operator*(real factor, const Vector3D &vector);
    friend inline const Vector3D operator*(const Vector3D &vector, real factor);
    friend inline const Vector3D operator*(const Vector3D &v1, const Vector3D &v2);
    friend inline const Vector3D operator-(const Vector3D &vector);
    friend inline const Vector3D operator/(const Vector3D &vector, real divisor);

    friend inline bool qFuzzyCompare(const Vector3D &v1, const Vector3D &v2);

    inline QVector2D toVector2D() const;
    inline QVector3D toVector3D() const;
    inline QVector4D toVector4D() const;

    inline QPoint toPoint() const;
    inline QPointF toPointF() const;

    operator QVariant() const;

private:
    Internal::Vector3DData d;

    inline Vector3D(const Internal::Vector3DData &d);

    friend class Point2D;
    friend class Point3D;
    friend class Point4D;
    friend class Vector2D;
    friend class Vector4D;
};

inline Vector3D::Vector3D() {}

inline Vector3D::Vector3D(real x, real y, real z) : d(x, y, z) {}

inline Vector3D::Vector3D(const QPoint &point) : d(point.x(), point.y(), 0.0f) {}

inline Vector3D::Vector3D(const QPointF &point) : d(point.x(), point.y(), 0.0f) {}

inline Vector3D::Vector3D(const QVector2D &vector) : d(vector.x(), vector.y(), 0.0f) {}

inline Vector3D::Vector3D(const QVector3D &vector) : d(vector.x(), vector.y(), vector.z()) {}

inline Vector3D::Vector3D(const QVector4D &vector) : d(vector.x(), vector.y(), vector.z()) {}

inline bool Vector3D::isNull() const
{
    return qIsNull(d[0]) && qIsNull(d[1]) && qIsNull(d[2]);
}

inline real Vector3D::x() const
{
    return d[0];
}

inline real Vector3D::y() const
{
    return d[1];
}

inline real Vector3D::z() const
{
    return d[2];
}

inline void Vector3D::setX(real x)
{
    d[0] = x;
}

inline void Vector3D::setY(real y)
{
    d[1] = y;
}

inline void Vector3D::setZ(real z)
{
    d[2] = z;
}

inline real Vector3D::length() const
{
    return gmtl::length(d);
}

inline real Vector3D::lengthSquared() const
{
    return gmtl::lengthSquared(d);
}

inline bool Vector3D::isNormalized() const
{
    return gmtl::isNormalized(d);
}

inline Vector3D Vector3D::normalized() const
{
    Internal::Vector3DData v = d;
    gmtl::normalize(v);
    return Vector3D(Internal::Vector3DData(v));
}

inline real Vector3D::normalize()
{
    return gmtl::normalize(d);
}

inline Vector3D Vector3D::crossProduct(const Vector3D &vector)
{
    Internal::Vector3DData result;
    return Vector3D(gmtl::cross(result, d, vector.d));
}

inline real Vector3D::dotProduct(const Vector3D &vector)
{
    return gmtl::dot(d, vector.d);
}

inline Vector3D Vector3D::reflected(const Vector3D &normal) const
{
    Internal::Vector3DData result;
    return Vector3D(gmtl::reflect(result, d, normal.d));
}

inline Vector3D &Vector3D::reflect(const Vector3D &normal)
{
    gmtl::reflect(d, d, normal.d);
    return *this;
}

inline Vector3D Vector3D::lerped(const Vector3D &to, real t)
{
    Internal::Vector3DData result;
    return Vector3D(gmtl::lerp(result, t, d, to.d));
}

inline Vector3D &Vector3D::lerp(const Vector3D &to, real t)
{
    gmtl::lerp(d, t, d, to.d);
    return *this;
}

inline Vector3D &Vector3D::operator+=(const Vector3D &vector)
{
    d[0] += vector.d[0];
    d[1] += vector.d[1];
    d[2] += vector.d[2];
    return *this;
}

inline Vector3D &Vector3D::operator-=(const Vector3D &vector)
{
    d[0] -= vector.d[0];
    d[1] -= vector.d[1];
    d[2] -= vector.d[2];
    return *this;
}

inline Vector3D &Vector3D::operator*=(real factor)
{
    d[0] *= factor;
    d[1] *= factor;
    d[2] *= factor;
    return *this;
}

inline Vector3D &Vector3D::operator*=(const Vector3D &vector)
{
    d[0] *= vector.d[0];
    d[1] *= vector.d[1];
    d[2] *= vector.d[2];
    return *this;
}

inline Vector3D &Vector3D::operator/=(real divisor)
{
    d[0] /= divisor;
    d[1] /= divisor;
    d[2] /= divisor;
    return *this;
}

inline bool operator==(const Vector3D &v1, const Vector3D &v2)
{
    return v1.d[0] == v2.d[0] && v1.d[1] == v2.d[1] && v1.d[2] == v2.d[2];
}

inline bool operator!=(const Vector3D &v1, const Vector3D &v2)
{
    return v1.d[0] != v2.d[0] || v1.d[1] != v2.d[1] || v1.d[2] != v2.d[2];
}

inline const Vector3D operator+(const Vector3D &v1, const Vector3D &v2)
{
    return Vector3D(Internal::Vector3DData(v1.d[0] + v2.d[0], v1.d[1] + v2.d[1], v1.d[2] + v2.d[2]));
}

inline const Vector3D operator-(const Vector3D &v1, const Vector3D &v2)
{
    return Vector3D(Internal::Vector3DData(v1.d[0] - v2.d[0], v1.d[1] - v2.d[1], v1.d[2] - v2.d[2]));
}

inline const Vector3D operator*(real factor, const Vector3D &vector)
{
    return Vector3D(Internal::Vector3DData(factor * vector.d[0], factor * vector.d[1], factor * vector.d[2]));
}

inline const Vector3D operator*(const Vector3D &vector, real factor)
{
    return Vector3D(Internal::Vector3DData(factor * vector.d[0], factor * vector.d[1], factor * vector.d[2]));
}

inline const Vector3D operator*(const Vector3D &v1, const Vector3D &v2)
{
    return Vector3D(Internal::Vector3DData(v1.d[0] * v2.d[0], v1.d[1] * v2.d[1], v1.d[2] * v2.d[2]));
}

inline const Vector3D operator/(const Vector3D &vector, real divisor)
{
    return Vector3D(Internal::Vector3DData(vector.d[0] / divisor, vector.d[1] / divisor, vector.d[2] / divisor));
}

inline bool qFuzzyCompare(const Vector3D &v1, const Vector3D &v2)
{
    return ::qFuzzyCompare(v1.d[0], v2.d[0]) &&
           ::qFuzzyCompare(v1.d[1], v2.d[1]) &&
           ::qFuzzyCompare(v1.d[2], v2.d[2]);
}

inline QVector2D Vector3D::toVector2D() const
{
    return QVector2D(d[0], d[1]);
}

inline QVector3D Vector3D::toVector3D() const
{
    return QVector3D(d[0], d[1], d[2]);
}

inline QVector4D Vector3D::toVector4D() const
{
    return QVector4D(d[0], d[1], d[2], 0.0f);
}

inline QPoint Vector3D::toPoint() const
{
    return QPoint(qRound(d[0]), qRound(d[1]));
}

inline QPointF Vector3D::toPointF() const
{
    return QPointF(qreal(d[0]), qreal(d[1]));
}

inline Vector3D::Vector3D(const Internal::Vector3DData &d) : d(d) {}

} // namespace Geometry

Q_DECLARE_TYPEINFO(Geometry::Vector3D, Q_MOVABLE_TYPE);

#endif // GEOMETRY_VECTOR3D_H
