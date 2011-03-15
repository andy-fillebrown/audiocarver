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

#ifndef GEOMETRY_VECTOR2D_H
#define GEOMETRY_VECTOR2D_H

#include <geometry/geometry_global.h>

#include <QtGui/QVector2D>
#include <QtGui/QVector3D>
#include <QtGui/QVector4D>
#include <QtCore/QPoint>

#include <gmtl/VecOps.h>

QT_FORWARD_DECLARE_CLASS(QVariant)

namespace Geometry {
namespace Internal {

typedef gmtl::Vec<real, 2> Vector2DData;

} // namespace Internal

class Point2D;
class Point3D;
class Point4D;
class Vector3D;
class Vector4D;

class GEOMETRY_EXPORT Vector2D
{
public:
    inline Vector2D();
    inline Vector2D(real x, real y);
    inline explicit Vector2D(const QPoint &point);
    inline explicit Vector2D(const QPointF &point);
    inline explicit Vector2D(const QVector2D &vector);
    inline explicit Vector2D(const QVector3D &vector);
    inline explicit Vector2D(const QVector4D &vector);
    explicit Vector2D(const Point2D &vector);
    explicit Vector2D(const Point3D &point);
    explicit Vector2D(const Point4D &point);
    explicit Vector2D(const Vector3D &vector);
    explicit Vector2D(const Vector4D &vector);

    inline bool isNull() const;

    inline real x() const;
    inline real y() const;

    inline void setX(real x);
    inline void setY(real y);

    inline real length() const;
    inline real lengthSquared() const;

    inline bool isNormalized() const;
    inline Vector2D normalized() const;
    inline real normalize();

    inline real dotProduct(const Vector2D &vector);

    inline Vector2D reflected(const Vector2D &normal) const;
    inline Vector2D &reflect(const Vector2D &normal);

    inline Vector2D lerped(const Vector2D &to, real t);
    inline Vector2D &lerp(const Vector2D &to, real t);

    inline Vector2D &operator+=(const Vector2D &vector);
    inline Vector2D &operator-=(const Vector2D &vector);
    inline Vector2D &operator*=(real factor);
    inline Vector2D &operator*=(const Vector2D &vector);
    inline Vector2D &operator/=(real divisor);

    friend inline bool operator==(const Vector2D &v1, const Vector2D &v2);
    friend inline bool operator!=(const Vector2D &v1, const Vector2D &v2);
    friend inline const Vector2D operator+(const Vector2D &v1, const Vector2D &v2);
    friend inline const Vector2D operator-(const Vector2D &v1, const Vector2D &v2);
    friend inline const Vector2D operator*(real factor, const Vector2D &vector);
    friend inline const Vector2D operator*(const Vector2D &vector, real factor);
    friend inline const Vector2D operator*(const Vector2D &v1, const Vector2D &v2);
    friend inline const Vector2D operator-(const Vector2D &vector);
    friend inline const Vector2D operator/(const Vector2D &vector, real divisor);

    friend inline bool qFuzzyCompare(const Vector2D &v1, const Vector2D &v2);

    inline QVector2D toVector2D() const;
    inline QVector3D toVector3D() const;
    inline QVector4D toVector4D() const;

    inline QPoint toPoint() const;
    inline QPointF toPointF() const;

    operator QVariant() const;

private:
    Internal::Vector2DData d;

    inline Vector2D(const Internal::Vector2DData &d);

    friend class Point2D;
    friend class Point3D;
    friend class Point4D;
    friend class Vector3D;
    friend class Vector4D;
};

inline Vector2D::Vector2D() {}

inline Vector2D::Vector2D(real x, real y) : d(x, y) {}

inline Vector2D::Vector2D(const QPoint &point) : d(point.x(), point.y()) {}

inline Vector2D::Vector2D(const QPointF &point) : d(point.x(), point.y()) {}

inline Vector2D::Vector2D(const QVector2D &vector) : d(vector.x(), vector.y()) {}

inline Vector2D::Vector2D(const QVector3D &vector) : d(vector.x(), vector.y()) {}

inline Vector2D::Vector2D(const QVector4D &vector) : d(vector.x(), vector.y()) {}

inline bool Vector2D::isNull() const
{
    return qIsNull(d[0]) && qIsNull(d[1]);
}

inline real Vector2D::x() const
{
    return d[0];
}

inline real Vector2D::y() const
{
    return d[1];
}

inline void Vector2D::setX(real x)
{
    d[0] = x;
}

inline void Vector2D::setY(real y)
{
    d[1] = y;
}

inline real Vector2D::length() const
{
    return gmtl::length(d);
}

inline real Vector2D::lengthSquared() const
{
    return gmtl::lengthSquared(d);
}

inline bool Vector2D::isNormalized() const
{
    return gmtl::isNormalized(d);
}

inline Vector2D Vector2D::normalized() const
{
    Internal::Vector2DData v = d;
    gmtl::normalize(v);
    return Vector2D(Internal::Vector2DData(v));
}

inline real Vector2D::normalize()
{
    return gmtl::normalize(d);
}

inline real Vector2D::dotProduct(const Vector2D &vector)
{
    return gmtl::dot(d, vector.d);
}

inline Vector2D Vector2D::reflected(const Vector2D &normal) const
{
    Internal::Vector2DData result;
    return Vector2D(gmtl::reflect(result, d, normal.d));
}

inline Vector2D &Vector2D::reflect(const Vector2D &normal)
{
    gmtl::reflect(d, d, normal.d);
    return *this;
}

inline Vector2D Vector2D::lerped(const Vector2D &to, real t)
{
    Internal::Vector2DData result;
    return Vector2D(gmtl::lerp(result, t, d, to.d));
}

inline Vector2D &Vector2D::lerp(const Vector2D &to, real t)
{
    gmtl::lerp(d, t, d, to.d);
    return *this;
}

inline Vector2D &Vector2D::operator+=(const Vector2D &vector)
{
    d[0] += vector.d[0];
    d[1] += vector.d[1];
    return *this;
}

inline Vector2D &Vector2D::operator-=(const Vector2D &vector)
{
    d[0] -= vector.d[0];
    d[1] -= vector.d[1];
    return *this;
}

inline Vector2D &Vector2D::operator*=(real factor)
{
    d[0] *= factor;
    d[1] *= factor;
    return *this;
}

inline Vector2D &Vector2D::operator*=(const Vector2D &vector)
{
    d[0] *= vector.d[0];
    d[1] *= vector.d[1];
    return *this;
}

inline Vector2D &Vector2D::operator/=(real divisor)
{
    d[0] /= divisor;
    d[1] /= divisor;
    return *this;
}

inline bool operator==(const Vector2D &v1, const Vector2D &v2)
{
    return v1.d[0] == v2.d[0] && v1.d[1] == v2.d[1];
}

inline bool operator!=(const Vector2D &v1, const Vector2D &v2)
{
    return v1.d[0] != v2.d[0] || v1.d[1] != v2.d[1];
}

inline const Vector2D operator+(const Vector2D &v1, const Vector2D &v2)
{
    return Vector2D(Internal::Vector2DData(v1.d[0] + v2.d[0], v1.d[1] + v2.d[1]));
}

inline const Vector2D operator-(const Vector2D &v1, const Vector2D &v2)
{
    return Vector2D(Internal::Vector2DData(v1.d[0] - v2.d[0], v1.d[1] - v2.d[1]));
}

inline const Vector2D operator*(real factor, const Vector2D &vector)
{
    return Vector2D(Internal::Vector2DData(factor * vector.d[0], factor * vector.d[1]));
}

inline const Vector2D operator*(const Vector2D &vector, real factor)
{
    return Vector2D(Internal::Vector2DData(factor * vector.d[0], factor * vector.d[1]));
}

inline const Vector2D operator*(const Vector2D &v1, const Vector2D &v2)
{
    return Vector2D(Internal::Vector2DData(v1.d[0] * v2.d[0], v1.d[1] * v2.d[1]));
}

inline const Vector2D operator/(const Vector2D &vector, real divisor)
{
    return Vector2D(Internal::Vector2DData(vector.d[0] / divisor, vector.d[1] / divisor));
}

inline bool qFuzzyCompare(const Vector2D &v1, const Vector2D &v2)
{
    return ::qFuzzyCompare(v1.d[0], v2.d[0]) &&
           ::qFuzzyCompare(v1.d[1], v2.d[1]);
}

inline QVector2D Vector2D::toVector2D() const
{
    return QVector2D(d[0], d[1]);
}

inline QVector3D Vector2D::toVector3D() const
{
    return QVector3D(d[0], d[1], 0.0f);
}

inline QVector4D Vector2D::toVector4D() const
{
    return QVector4D(d[0], d[1], 0.0f, 0.0f);
}

inline QPoint Vector2D::toPoint() const
{
    return QPoint(qRound(d[0]), qRound(d[1]));
}

inline QPointF Vector2D::toPointF() const
{
    return QPointF(qreal(d[0]), qreal(d[1]));
}

inline Vector2D::Vector2D(const Internal::Vector2DData &d) : d(d) {}

} // namespace Geometry

Q_DECLARE_TYPEINFO(Geometry::Vector2D, Q_MOVABLE_TYPE);

#endif // GEOMETRY_VECTOR2D_H
