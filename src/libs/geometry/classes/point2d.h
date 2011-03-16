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

#ifndef GEOMETRY_POINT2D_H
#define GEOMETRY_POINT2D_H

#include <geometry/geometry_global.h>

#include <QtGui/QVector2D>
#include <QtGui/QVector3D>
#include <QtGui/QVector4D>
#include <QtCore/QPoint>

#include <gmtl/Point.h>

QT_FORWARD_DECLARE_CLASS(QVariant)

namespace Geometry {
namespace Internal {

typedef gmtl::Point<real, 2> Point2DData;

} // namespace Internal

class Matrix4x4;
class Point3D;
class Point4D;
class Vector2D;
class Vector3D;
class Vector4D;

class GEOMETRY_EXPORT Point2D
{
public:
    inline Point2D();
    inline Point2D(real x, real y);
    inline explicit Point2D(const QPoint &point);
    inline explicit Point2D(const QPointF &point);
    inline explicit Point2D(const QVector2D &vector);
    inline explicit Point2D(const QVector3D &vector);
    inline explicit Point2D(const QVector4D &vector);
    explicit Point2D(const Point3D &point);
    explicit Point2D(const Point4D &point);
    explicit Point2D(const Vector2D &vector);
    explicit Point2D(const Vector3D &vector);
    explicit Point2D(const Vector4D &vector);

    inline bool isNull() const;

    inline real x() const;
    inline real y() const;

    inline void setX(real x);
    inline void setY(real y);

    inline Point2D &operator+=(const Point2D &point);
    inline Point2D &operator-=(const Point2D &point);
    inline Point2D &operator*=(real factor);
    inline Point2D &operator*=(const Point2D &point);
    inline Point2D &operator/=(real divisor);

    friend bool operator==(const Point2D &pt1, const Point2D &pt2);
    friend bool operator!=(const Point2D &pt1, const Point2D &pt2);
    friend Point2D operator+(const Point2D &pt1, const Point2D &pt2);
    friend Point2D operator-(const Point2D &pt1, const Point2D &pt2);
    friend Point2D operator*(real factor, const Point2D &point);
    friend Point2D operator*(const Point2D &point, real factor);
    friend Point2D operator*(const Point2D &pt1, const Point2D &pt2);
    friend Point2D operator-(const Point2D &point);
    friend Point2D operator/(const Point2D &point, real divisor);

    friend Point2D operator*(const Matrix4x4 &matrix, const Point2D &point);
    friend Point2D operator*(const Point2D &point, const Matrix4x4 &matrix);

    friend inline bool qFuzzyCompare(const Point2D &pt1, const Point2D &pt2);

    inline QVector2D toVector2D() const;
    inline QVector3D toVector3D() const;
    inline QVector4D toVector4D() const;

    inline QPoint toPoint() const;
    inline QPointF toPointF() const;

    operator QVariant() const;

private:
    Internal::Point2DData d;

    inline Point2D(const Internal::Point2DData &d);

    friend class Point3D;
    friend class Point4D;
    friend class Vector2D;
    friend class Vector3D;
    friend class Vector4D;
};

inline Point2D::Point2D() {}

inline Point2D::Point2D(real x, real y) : d(x, y) {}

inline Point2D::Point2D(const QPoint &point) : d(point.x(), point.y()) {}

inline Point2D::Point2D(const QPointF &point) : d(point.x(), point.y()) {}

inline Point2D::Point2D(const QVector2D &vector) : d(vector.x(), vector.y()) {}

inline Point2D::Point2D(const QVector3D &vector) : d(vector.x(), vector.y()) {}

inline Point2D::Point2D(const QVector4D &vector) : d(vector.x(), vector.y()) {}

inline bool Point2D::isNull() const
{
    return qIsNull(d[0]) && qIsNull(d[1]);
}

inline real Point2D::x() const
{
    return d[0];
}

inline real Point2D::y() const
{
    return d[1];
}

inline void Point2D::setX(real x)
{
    d[0] = x;
}

inline void Point2D::setY(real y)
{
    d[1] = y;
}

inline Point2D &Point2D::operator+=(const Point2D &point)
{
    d[0] += point.d[0];
    d[1] += point.d[1];
    return *this;
}

inline Point2D &Point2D::operator-=(const Point2D &point)
{
    d[0] -= point.d[0];
    d[1] -= point.d[1];
    return *this;
}

inline Point2D &Point2D::operator*=(real factor)
{
    d[0] *= factor;
    d[1] *= factor;
    return *this;
}

inline Point2D &Point2D::operator*=(const Point2D &point)
{
    d[0] *= point.d[0];
    d[1] *= point.d[1];
    return *this;
}

inline Point2D &Point2D::operator/=(real divisor)
{
    d[0] /= divisor;
    d[1] /= divisor;
    return *this;
}

inline bool operator==(const Point2D &pt1, const Point2D &pt2)
{
    return pt1.d[0] == pt2.d[0] && pt1.d[1] == pt2.d[1];
}

inline bool operator!=(const Point2D &pt1, const Point2D &pt2)
{
    return pt1.d[0] != pt2.d[0] || pt1.d[1] != pt2.d[1];
}

inline Point2D operator+(const Point2D &pt1, const Point2D &pt2)
{
    return Point2D(Internal::Point2DData(pt1.d[0] + pt2.d[0], pt1.d[1] + pt2.d[1]));
}

inline Point2D operator-(const Point2D &pt1, const Point2D &pt2)
{
    return Point2D(Internal::Point2DData(pt1.d[0] - pt2.d[0], pt1.d[1] - pt2.d[1]));
}

inline Point2D operator*(real factor, const Point2D &point)
{
    return Point2D(Internal::Point2DData(factor * point.d[0], factor * point.d[1]));
}

inline Point2D operator*(const Point2D &point, real factor)
{
    return Point2D(Internal::Point2DData(factor * point.d[0], factor * point.d[1]));
}

inline Point2D operator*(const Point2D &pt1, const Point2D &pt2)
{
    return Point2D(Internal::Point2DData(pt1.d[0] * pt2.d[0], pt1.d[1] * pt2.d[1]));
}

inline Point2D operator/(const Point2D &point, real divisor)
{
    return Point2D(Internal::Point2DData(point.d[0] / divisor, point.d[1] / divisor));
}

inline bool qFuzzyCompare(const Point2D &pt1, const Point2D &pt2)
{
    return ::qFuzzyCompare(pt1.d[0], pt2.d[0]) &&
           ::qFuzzyCompare(pt1.d[1], pt2.d[1]);
}

inline QVector2D Point2D::toVector2D() const
{
    return QVector2D(d[0], d[1]);
}

inline QVector3D Point2D::toVector3D() const
{
    return QVector3D(d[0], d[1], 0.0f);
}

inline QVector4D Point2D::toVector4D() const
{
    return QVector4D(d[0], d[1], 0.0f, 0.0f);
}

inline QPoint Point2D::toPoint() const
{
    return QPoint(qRound(d[0]), qRound(d[1]));
}

inline QPointF Point2D::toPointF() const
{
    return QPointF(qreal(d[0]), qreal(d[1]));
}

inline Point2D::Point2D(const Internal::Point2DData &d) : d(d) {}

} // namespace Geometry

Q_DECLARE_TYPEINFO(Geometry::Point2D, Q_MOVABLE_TYPE);

#endif // GEOMETRY_POINT2D_H
