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

#ifndef GEOMETRY_POINT4D_H
#define GEOMETRY_POINT4D_H

#include <geometry/geometry_global.h>

#include <QtGui/QVector2D>
#include <QtGui/QVector3D>
#include <QtGui/QVector4D>
#include <QtCore/QPoint>

#include <gmtl/Point.h>

namespace Geometry {
namespace Internal {

typedef gmtl::Point<real, 4> Point4DData;

} // namespace Internal

class Point2D;
class Point3D;
class Vector2D;
class Vector3D;
class Vector4D;

class GEOMETRY_EXPORT Point4D
{
public:
    inline Point4D();
    inline Point4D(real x, real y, real z, real w);
    inline explicit Point4D(const QPoint &point);
    inline explicit Point4D(const QPointF &point);
    inline explicit Point4D(const QVector2D &vector);
    inline explicit Point4D(const QVector3D &vector);
    inline explicit Point4D(const QVector4D &vector);
    explicit Point4D(const Point2D &point);
    explicit Point4D(const Point3D &point);
    explicit Point4D(const Vector2D &vector);
    explicit Point4D(const Vector3D &vector);
    explicit Point4D(const Vector4D &vector);

    inline bool isNull() const;

    inline real x() const;
    inline real y() const;
    inline real z() const;
    inline real w() const;

    inline void setX(real x);
    inline void setY(real y);
    inline void setZ(real z);
    inline void setW(real w);

    inline Point4D &operator+=(const Point4D &point);
    inline Point4D &operator-=(const Point4D &point);
    inline Point4D &operator*=(real factor);
    inline Point4D &operator*=(const Point4D &point);
    inline Point4D &operator/=(real divisor);

    friend inline bool operator==(const Point4D &pt1, const Point4D &pt2);
    friend inline bool operator!=(const Point4D &pt1, const Point4D &pt2);
    friend inline const Point4D operator+(const Point4D &pt1, const Point4D &pt2);
    friend inline const Point4D operator-(const Point4D &pt1, const Point4D &pt2);
    friend inline const Point4D operator*(real factor, const Point4D &point);
    friend inline const Point4D operator*(const Point4D &point, real factor);
    friend inline const Point4D operator*(const Point4D &pt1, const Point4D &pt2);
    friend inline const Point4D operator-(const Point4D &point);
    friend inline const Point4D operator/(const Point4D &point, real divisor);

    friend inline bool qFuzzyCompare(const Point4D &pt1, const Point4D &pt2);

    inline QVector2D toVector2D() const;
    inline QVector3D toVector3D() const;
    inline QVector4D toVector4D() const;

    inline QPoint toPoint() const;
    inline QPointF toPointF() const;

    operator QVariant() const;

private:
    Internal::Point4DData d;

    inline Point4D(const Internal::Point4DData &d);

    friend class Point2D;
    friend class Point3D;
    friend class Vector2D;
    friend class Vector3D;
    friend class Vector4D;
};

inline Point4D::Point4D() {}

inline Point4D::Point4D(real x, real y, real z, real w) : d(x, y, z, w) {}

inline Point4D::Point4D(const QPoint &point) : d(point.x(), point.y(), 0.0f, 0.0f) {}

inline Point4D::Point4D(const QPointF &point) : d(point.x(), point.y(), 0.0f, 0.0f) {}

inline Point4D::Point4D(const QVector2D &vector) : d(vector.x(), vector.y(), 0.0f, 0.0f) {}

inline Point4D::Point4D(const QVector3D &vector) : d(vector.x(), vector.y(), vector.z(), 0.0f) {}

inline Point4D::Point4D(const QVector4D &vector) : d(vector.x(), vector.y(), vector.z(), vector.w()) {}

inline bool Point4D::isNull() const
{
    return qIsNull(d[0]) && qIsNull(d[1]) && qIsNull(d[2]) && qIsNull(d[3]);
}

inline real Point4D::x() const
{
    return d[0];
}

inline real Point4D::y() const
{
    return d[1];
}

inline real Point4D::z() const
{
    return d[2];
}

inline real Point4D::w() const
{
    return d[3];
}

inline void Point4D::setX(real x)
{
    d[0] = x;
}

inline void Point4D::setY(real y)
{
    d[1] = y;
}

inline void Point4D::setZ(real z)
{
    d[2] = z;
}

inline void Point4D::setW(real w)
{
    d[3] = w;
}

inline Point4D &Point4D::operator+=(const Point4D &point)
{
    d[0] += point.d[0];
    d[1] += point.d[1];
    d[2] += point.d[2];
    d[3] += point.d[3];
    return *this;
}

inline Point4D &Point4D::operator-=(const Point4D &point)
{
    d[0] -= point.d[0];
    d[1] -= point.d[1];
    d[2] -= point.d[2];
    d[3] -= point.d[3];
    return *this;
}

inline Point4D &Point4D::operator*=(real factor)
{
    d[0] *= factor;
    d[1] *= factor;
    d[2] *= factor;
    d[3] *= factor;
    return *this;
}

inline Point4D &Point4D::operator*=(const Point4D &point)
{
    d[0] *= point.d[0];
    d[1] *= point.d[1];
    d[2] *= point.d[2];
    d[3] *= point.d[3];
    return *this;
}

inline Point4D &Point4D::operator/=(real divisor)
{
    d[0] /= divisor;
    d[1] /= divisor;
    d[2] /= divisor;
    d[3] /= divisor;
    return *this;
}

inline bool operator==(const Point4D &pt1, const Point4D &pt2)
{
    return pt1.d[0] == pt2.d[0] && pt1.d[1] == pt2.d[1] && pt1.d[2] == pt2.d[2] && pt1.d[3] == pt2.d[3];
}

inline bool operator!=(const Point4D &pt1, const Point4D &pt2)
{
    return pt1.d[0] != pt2.d[0] || pt1.d[1] != pt2.d[1] || pt1.d[2] != pt2.d[2] || pt1.d[3] != pt2.d[3];
}

inline const Point4D operator+(const Point4D &pt1, const Point4D &pt2)
{
    return Point4D(Internal::Point4DData(pt1.d[0] + pt2.d[0], pt1.d[1] + pt2.d[1], pt1.d[2] + pt2.d[2], pt1.d[3] + pt2.d[3]));
}

inline const Point4D operator-(const Point4D &pt1, const Point4D &pt2)
{
    return Point4D(Internal::Point4DData(pt1.d[0] - pt2.d[0], pt1.d[1] - pt2.d[1], pt1.d[2] - pt2.d[2], pt1.d[3] - pt2.d[3]));
}

inline const Point4D operator*(real factor, const Point4D &point)
{
    return Point4D(Internal::Point4DData(factor * point.d[0], factor * point.d[1], factor * point.d[2], factor * point.d[3]));
}

inline const Point4D operator*(const Point4D &point, real factor)
{
    return Point4D(Internal::Point4DData(factor * point.d[0], factor * point.d[1], factor * point.d[2], factor * point.d[3]));
}

inline const Point4D operator*(const Point4D &pt1, const Point4D &pt2)
{
    return Point4D(Internal::Point4DData(pt1.d[0] * pt2.d[0], pt1.d[1] * pt2.d[1], pt1.d[2] * pt2.d[2], pt1.d[3] * pt2.d[3]));
}

inline const Point4D operator/(const Point4D &point, real divisor)
{
    return Point4D(Internal::Point4DData(point.d[0] / divisor, point.d[1] / divisor, point.d[2] / divisor, point.d[3] / divisor));
}

inline bool qFuzzyCompare(const Point4D &pt1, const Point4D &pt2)
{
    return ::qFuzzyCompare(pt1.d[0], pt2.d[0]) &&
           ::qFuzzyCompare(pt1.d[1], pt2.d[1]) &&
           ::qFuzzyCompare(pt1.d[2], pt2.d[2]) &&
           ::qFuzzyCompare(pt1.d[2], pt2.d[2]);
}

inline QVector2D Point4D::toVector2D() const
{
    return QVector2D(d[0], d[1]);
}

inline QVector3D Point4D::toVector3D() const
{
    return QVector3D(d[0], d[1], d[2]);
}

inline QVector4D Point4D::toVector4D() const
{
    return QVector4D(d[0], d[1], d[2], d[3]);
}

inline QPoint Point4D::toPoint() const
{
    return QPoint(qRound(d[0]), qRound(d[1]));
}

inline QPointF Point4D::toPointF() const
{
    return QPointF(qreal(d[0]), qreal(d[1]));
}

inline Point4D::Point4D(const Internal::Point4DData &d) : d(d) {}

} // namespace Geometry

Q_DECLARE_TYPEINFO(Geometry::Point4D, Q_MOVABLE_TYPE);

#endif // GEOMETRY_POINT4D_H
