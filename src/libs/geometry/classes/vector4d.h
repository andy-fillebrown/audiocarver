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

#ifndef GEOMETRY_VECTOR4D_H
#define GEOMETRY_VECTOR4D_H

#include <geometry/geometry_global.h>

#include <QtGui/QVector2D>
#include <QtGui/QVector3D>
#include <QtGui/QVector4D>
#include <QtCore/QPoint>

#include <gmtl/VecOps.h>

QT_FORWARD_DECLARE_CLASS(QVariant)

namespace Geometry {
namespace Internal {

typedef gmtl::Vec<real, 4> Vector4DData;

} // namespace Internal

class Matrix4x4;
class Point2D;
class Point3D;
class Point4D;
class Vector2D;
class Vector3D;

class GEOMETRY_EXPORT Vector4D
{
public:
    inline Vector4D();
    inline Vector4D(real x, real y, real z, real w);
    inline explicit Vector4D(const QPoint &point);
    inline explicit Vector4D(const QPointF &point);
    inline explicit Vector4D(const QVector2D &vector);
    inline explicit Vector4D(const QVector3D &vector);
    inline explicit Vector4D(const QVector4D &vector);
    explicit Vector4D(const Point2D &vector);
    explicit Vector4D(const Point3D &point);
    explicit Vector4D(const Point4D &point);
    explicit Vector4D(const Vector2D &vector);
    explicit Vector4D(const Vector3D &vector);

    inline bool isNull() const;

    inline real x() const;
    inline real y() const;
    inline real z() const;
    inline real w() const;

    inline void setX(real x);
    inline void setY(real y);
    inline void setZ(real z);
    inline void setW(real w);

    inline real length() const;
    inline real lengthSquared() const;

    inline bool isNormalized() const;
    inline Vector4D normalized() const;
    inline real normalize();

    inline real dotProduct(const Vector4D &vector);

    inline Vector4D reflected(const Vector4D &normal) const;
    inline Vector4D &reflect(const Vector4D &normal);

    inline Vector4D lerped(const Vector4D &to, real t);
    inline Vector4D &lerp(const Vector4D &to, real t);

    inline Vector4D &operator+=(const Vector4D &vector);
    inline Vector4D &operator-=(const Vector4D &vector);
    inline Vector4D &operator*=(real factor);
    inline Vector4D &operator*=(const Vector4D &vector);
    inline Vector4D &operator/=(real divisor);

    friend inline bool operator==(const Vector4D &v1, const Vector4D &v2);
    friend inline bool operator!=(const Vector4D &v1, const Vector4D &v2);
    friend inline Vector4D operator+(const Vector4D &v1, const Vector4D &v2);
    friend inline Vector4D operator-(const Vector4D &v1, const Vector4D &v2);
    friend inline Vector4D operator*(real factor, const Vector4D &vector);
    friend inline Vector4D operator*(const Vector4D &vector, real factor);
    friend inline Vector4D operator*(const Vector4D &v1, const Vector4D &v2);
    friend inline Vector4D operator-(const Vector4D &vector);
    friend inline Vector4D operator/(const Vector4D &vector, real divisor);

    friend inline bool qFuzzyCompare(const Vector4D &v1, const Vector4D &v2);

    inline QVector2D toVector2D() const;
    inline QVector3D toVector3D() const;
    inline QVector4D toVector4D() const;

    inline QPoint toPoint() const;
    inline QPointF toPointF() const;

    operator QVariant() const;

private:
    Internal::Vector4DData d;

    inline Vector4D(const Internal::Vector4DData &d);

    friend class Matrix4x4;
    friend class Point2D;
    friend class Point3D;
    friend class Point4D;
    friend class Vector2D;
    friend class Vector3D;
};

inline Vector4D::Vector4D() {}

inline Vector4D::Vector4D(real x, real y, real z, real w) : d(x, y, z, w) {}

inline Vector4D::Vector4D(const QPoint &point) : d(point.x(), point.y(), 0.0f, 0.0f) {}

inline Vector4D::Vector4D(const QPointF &point) : d(point.x(), point.y(), 0.0f, 0.0f) {}

inline Vector4D::Vector4D(const QVector2D &vector) : d(vector.x(), vector.y(), 0.0f, 0.0f) {}

inline Vector4D::Vector4D(const QVector3D &vector) : d(vector.x(), vector.y(), vector.z(), 0.0f) {}

inline Vector4D::Vector4D(const QVector4D &vector) : d(vector.x(), vector.y(), vector.z(), vector.w()) {}

inline bool Vector4D::isNull() const
{
    return qIsNull(d[0]) && qIsNull(d[1]) && qIsNull(d[2]) && qIsNull(d[3]);
}

inline real Vector4D::x() const
{
    return d[0];
}

inline real Vector4D::y() const
{
    return d[1];
}

inline real Vector4D::z() const
{
    return d[2];
}

inline real Vector4D::w() const
{
    return d[3];
}

inline void Vector4D::setX(real x)
{
    d[0] = x;
}

inline void Vector4D::setY(real y)
{
    d[1] = y;
}

inline void Vector4D::setZ(real z)
{
    d[2] = z;
}

inline void Vector4D::setW(real w)
{
    d[3] = w;
}

inline real Vector4D::length() const
{
    return gmtl::length(d);
}

inline real Vector4D::lengthSquared() const
{
    return gmtl::lengthSquared(d);
}

inline bool Vector4D::isNormalized() const
{
    return gmtl::isNormalized(d);
}

inline Vector4D Vector4D::normalized() const
{
    Internal::Vector4DData v = d;
    gmtl::normalize(v);
    return Vector4D(Internal::Vector4DData(v));
}

inline real Vector4D::normalize()
{
    return gmtl::normalize(d);
}

inline real Vector4D::dotProduct(const Vector4D &vector)
{
    return gmtl::dot(d, vector.d);
}

inline Vector4D Vector4D::reflected(const Vector4D &normal) const
{
    Internal::Vector4DData result;
    return Vector4D(gmtl::reflect(result, d, normal.d));
}

inline Vector4D &Vector4D::reflect(const Vector4D &normal)
{
    gmtl::reflect(d, d, normal.d);
    return *this;
}

inline Vector4D Vector4D::lerped(const Vector4D &to, real t)
{
    Internal::Vector4DData result;
    return Vector4D(gmtl::lerp(result, t, d, to.d));
}

inline Vector4D &Vector4D::lerp(const Vector4D &to, real t)
{
    gmtl::lerp(d, t, d, to.d);
    return *this;
}

inline Vector4D &Vector4D::operator+=(const Vector4D &vector)
{
    d[0] += vector.d[0];
    d[1] += vector.d[1];
    d[2] += vector.d[2];
    d[3] += vector.d[3];
    return *this;
}

inline Vector4D &Vector4D::operator-=(const Vector4D &vector)
{
    d[0] -= vector.d[0];
    d[1] -= vector.d[1];
    d[2] -= vector.d[2];
    d[3] -= vector.d[3];
    return *this;
}

inline Vector4D &Vector4D::operator*=(real factor)
{
    d[0] *= factor;
    d[1] *= factor;
    d[2] *= factor;
    d[3] *= factor;
    return *this;
}

inline Vector4D &Vector4D::operator*=(const Vector4D &vector)
{
    d[0] *= vector.d[0];
    d[1] *= vector.d[1];
    d[2] *= vector.d[2];
    d[3] *= vector.d[3];
    return *this;
}

inline Vector4D &Vector4D::operator/=(real divisor)
{
    d[0] /= divisor;
    d[1] /= divisor;
    d[2] /= divisor;
    d[3] /= divisor;
    return *this;
}

inline bool operator==(const Vector4D &v1, const Vector4D &v2)
{
    return v1.d[0] == v2.d[0] && v1.d[1] == v2.d[1] && v1.d[2] == v2.d[2] && v1.d[3] == v2.d[3];
}

inline bool operator!=(const Vector4D &v1, const Vector4D &v2)
{
    return v1.d[0] != v2.d[0] || v1.d[1] != v2.d[1] || v1.d[2] != v2.d[2] || v1.d[3] != v2.d[3];
}

inline Vector4D operator+(const Vector4D &v1, const Vector4D &v2)
{
    return Vector4D(Internal::Vector4DData(v1.d[0] + v2.d[0], v1.d[1] + v2.d[1], v1.d[2] + v2.d[2], v1.d[3] + v2.d[3]));
}

inline Vector4D operator-(const Vector4D &v1, const Vector4D &v2)
{
    return Vector4D(Internal::Vector4DData(v1.d[0] - v2.d[0], v1.d[1] - v2.d[1], v1.d[2] - v2.d[2], v1.d[3] - v2.d[3]));
}

inline Vector4D operator*(real factor, const Vector4D &vector)
{
    return Vector4D(Internal::Vector4DData(factor * vector.d[0], factor * vector.d[1], factor * vector.d[2], factor * vector.d[3]));
}

inline Vector4D operator*(const Vector4D &vector, real factor)
{
    return Vector4D(Internal::Vector4DData(factor * vector.d[0], factor * vector.d[1], factor * vector.d[2], factor * vector.d[3]));
}

inline Vector4D operator*(const Vector4D &v1, const Vector4D &v2)
{
    return Vector4D(Internal::Vector4DData(v1.d[0] * v2.d[0], v1.d[1] * v2.d[1], v1.d[2] * v2.d[2], v1.d[3] * v2.d[3]));
}

inline Vector4D operator/(const Vector4D &vector, real divisor)
{
    return Vector4D(Internal::Vector4DData(vector.d[0] / divisor, vector.d[1] / divisor, vector.d[2] / divisor, vector.d[3] / divisor));
}

inline bool qFuzzyCompare(const Vector4D &v1, const Vector4D &v2)
{
    return ::qFuzzyCompare(v1.d[0], v2.d[0]) &&
           ::qFuzzyCompare(v1.d[1], v2.d[1]) &&
           ::qFuzzyCompare(v1.d[2], v2.d[2]) &&
           ::qFuzzyCompare(v1.d[3], v2.d[3]);
}

inline QVector2D Vector4D::toVector2D() const
{
    return QVector2D(d[0], d[1]);
}

inline QVector3D Vector4D::toVector3D() const
{
    return QVector3D(d[0], d[1], d[2]);
}

inline QVector4D Vector4D::toVector4D() const
{
    return QVector4D(d[0], d[1], d[2], d[3]);
}

inline QPoint Vector4D::toPoint() const
{
    return QPoint(qRound(d[0]), qRound(d[1]));
}

inline QPointF Vector4D::toPointF() const
{
    return QPointF(qreal(d[0]), qreal(d[1]));
}

inline Vector4D::Vector4D(const Internal::Vector4DData &d) : d(d) {}

} // namespace Geometry

Q_DECLARE_TYPEINFO(Geometry::Vector4D, Q_MOVABLE_TYPE);

#endif // GEOMETRY_VECTOR4D_H
