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

#ifndef GEOMETRY_MATRIX4X4_H
#define GEOMETRY_MATRIX4X4_H

#include <geometry/classes/point2d.h>
#include <geometry/classes/point3d.h>
#include <geometry/classes/point4d.h>
#include <geometry/classes/vector3d.h>
#include <geometry/classes/vector4d.h>

#include <QtGui/QMatrix4x4>
#include <QtGui/QTransform>
#include <QtCore/qmath.h>

#include <gmtl/MatrixOps.h>

namespace Geometry {
namespace Internal {

typedef gmtl::Matrix<real, 4, 4> Matrix4x4Data;

} // namespace Internal

class Matrix2x2;
class Matrix3x3;
class Quaternion;
class Transform3D;

class GEOMETRY_EXPORT Matrix4x4
{
public:
    inline Matrix4x4();
    inline explicit Matrix4x4(const real *values);
    inline Matrix4x4(real m11, real m12, real m13, real m14,
                     real m21, real m22, real m23, real m24,
                     real m31, real m32, real m33, real m34,
                     real m41, real m42, real m43, real m44);

    template <int N, int M>
    inline explicit Matrix4x4(const QGenericMatrix<N, M, real> &matrix);

    inline Matrix4x4(real *values, int cols, int rows);
    inline Matrix4x4(const QTransform &transform);
    inline Matrix4x4(const QMatrix &matrix);
    inline Matrix4x4(const QMatrix4x4 &matrix);
    inline Matrix4x4(const Transform3D &transform);
    inline Matrix4x4(const Matrix2x2 &matrix);
    inline Matrix4x4(const Matrix3x3 &matrix);

    inline const real &operator()(int row, int column) const;
    inline real &operator()(int row, int column);

    inline Vector4D column(int index) const;
    inline void setColumn(int index, const Vector4D &value);

    inline Vector4D row(int index) const;
    inline void setRow(int index, const Vector4D &value);

    inline bool isIdentity() const;
    inline void setToIdentity();

    inline void fill(real value);

    real determinant() const;
    inline Matrix4x4 inverted(bool *invertible = 0) const;
    inline Matrix4x4 &invert(bool *invertible = 0);
    inline Matrix4x4 transposed() const;
    inline Matrix4x4 &transpose();
    inline Matrix3x3 normalMatrix() const;

    inline Matrix4x4 &operator+=(const Matrix4x4 &matrix);
    inline Matrix4x4 &operator-=(const Matrix4x4 &matrix);
    inline Matrix4x4 &operator*=(const Matrix4x4 &matrix);
    inline Matrix4x4 &operator*=(real factor);
    inline Matrix4x4 &operator/=(real divisor);
    inline bool operator==(const Matrix4x4 &matrix) const;
    inline bool operator!=(const Matrix4x4 &matrix) const;

    friend Matrix4x4 operator+(const Matrix4x4 &m1, const Matrix4x4 &m2);
    friend Matrix4x4 operator-(const Matrix4x4 &m1, const Matrix4x4 &m2);
    friend Matrix4x4 operator*(const Matrix4x4 &m1, const Matrix4x4 &m2);
    friend Point2D operator*(const Matrix4x4 &matrix, const Point2D &point);
    friend Point2D operator*(const Point2D &point, const Matrix4x4 &matrix);
    friend Point3D operator*(const Matrix4x4 &matrix, const Point3D &point);
    friend Point3D operator*(const Point3D &point, const Matrix4x4 &matrix);
    friend Point4D operator*(const Matrix4x4 &matrix, const Point4D &point);
    friend Point4D operator*(const Point4D &point, const Matrix4x4 &matrix);
    friend Vector3D operator*(const Vector3D &vector, const Matrix4x4 &matrix);
    friend QPoint operator*(const QPoint &point, const Matrix4x4 &matrix);
    friend QPoint operator*(const Matrix4x4 &matrix, const QPoint &point);
    friend QPointF operator*(const Matrix4x4 &matrix, const QPointF &point);
    friend QPointF operator*(const QPointF &point, const Matrix4x4 &matrix);
    friend Matrix4x4 operator-(const Matrix4x4 &matrix);
    friend Matrix4x4 operator*(const Matrix4x4 &matrix, real factor);
    friend Matrix4x4 operator*(real factor, const Matrix4x4 &matrix);
    friend Matrix4x4 operator/(const Matrix4x4 &matrix, real divisor);

    friend inline bool qFuzzyCompare(const Matrix4x4 &m1, const Matrix4x4 &m2);

    inline void scale(const Vector3D &vector);
    inline void translate(const Vector3D &vector);
    inline void rotate(real angle, const Vector3D &vector);
    inline void scale(real x, real y);
    inline void scale(real x, real y, real z);
    inline void scale(real factor);
    inline void translate(real x, real y);
    inline void translate(real x, real y, real z);
    inline void rotate(real angle, real x, real y, real z = 0.0f);
    inline void rotate(const Quaternion &quaternion);

    inline void ortho(const QRect &rect);
    inline void ortho(const QRectF &rect);
    inline void ortho(real left, real right, real bottom, real top, real nearPlane, real farPlane);
    inline void frustum(real left, real right, real bottom, real top, real nearPlane, real farPlane);
    inline void perspective(real angle, real aspect, real nearPlane, real farPlane);
    inline void lookAt(const Vector3D &eye, const Vector3D &center, const Vector3D &up);
    inline void flipCoordinates();

    inline void copyDataTo(real *values) const;

    inline Matrix2x2 toAffine() const;
    inline Transform3D toTransform() const;
    inline Transform3D toTransform(real distanceToPlane) const;

    // TODO: Check implementation.  It was done backwards compared to QMatrix4x4.
    inline QPoint map(const QPoint &point) const;
    inline QPointF map(const QPointF &point) const;
    inline Point2D map(const Point2D &point) const;
    inline Point3D map(const Point3D &point) const;
    inline Point4D map(const Point4D &point) const;
    inline Vector3D map(const Vector3D &vector) const;
    inline QRect map(const QRect &rect) const;
    inline QRectF map(const QRectF &rect) const;

    template <int N, int M>
    inline QGenericMatrix<N, M, real> toGenericMatrix() const;

    inline real *data();
    inline const real *data() const;
    inline const real *constData() const;

    inline void optimize();

    operator QVariant() const;

private:
    Internal::Matrix4x4Data d;

    Matrix4x4(const Internal::Matrix4x4Data &d);
};

inline Matrix4x4::Matrix4x4() {}

inline Matrix4x4::Matrix4x4(const real *values)
{
    d.set(values);
    d.mState = Internal::Matrix4x4Data::FULL;
}

inline Matrix4x4::Matrix4x4(real m11, real m12, real m13, real m14,
                            real m21, real m22, real m23, real m24,
                            real m31, real m32, real m33, real m34,
                            real m41, real m42, real m43, real m44)
{
    d.set(m11, m12, m13, m14,
          m21, m22, m23, m24,
          m31, m32, m33, m34,
          m41, m42, m43, m44);
    d.mState = Internal::Matrix4x4Data::FULL;
}

template <int N, int M>
inline Matrix4x4::Matrix4x4(const QGenericMatrix<N, M, real> &matrix)
{
    const real *values = matrix.constData();
    for (int col = 0; col < 4; ++col) {
        for (int row = 0; row < 4; ++row) {
            if (col < N && row < M)
                d(col,row) = values[col * M + row];
            else if (col == row)
                d(col,row) = 1.0f;
            else
                d(col,row) = 0.0f;
        }
    }
    d.mState = Internal::Matrix4x4Data::FULL;
}

inline Matrix4x4::Matrix4x4(real *values, int cols, int rows)
{
    for (int col = 0; col < 4; ++col) {
        for (int row = 0; row < 4; ++row) {
            if (col < cols && row < rows)
                d(col,row) = values[col * rows + row];
            else if (col == row)
                d(col,row) = 1.0f;
            else
                d(col,row) = 0.0f;
        }
    }
    d.mState = Internal::Matrix4x4Data::FULL;
}

inline Matrix4x4::Matrix4x4(const QTransform &transform)
{
    d(0,0) = transform.m11();
    d(0,1) = transform.m12();
    d(0,2) = 0.0f;
    d(0,3) = transform.m13();
    d(1,0) = transform.m21();
    d(1,1) = transform.m22();
    d(1,2) = 0.0f;
    d(1,3) = transform.m23();
    d(2,0) = 0.0f;
    d(2,1) = 0.0f;
    d(2,2) = 1.0f;
    d(2,3) = 0.0f;
    d(3,0) = transform.dx();
    d(3,1) = transform.dy();
    d(3,2) = 0.0f;
    d(3,3) = transform.m33();
    d.mState = Internal::Matrix4x4Data::FULL;
}

inline Matrix4x4::Matrix4x4(const QMatrix &matrix)
{
    d(0,0) = matrix.m11();
    d(0,1) = matrix.m12();
    d(0,2) = 0.0f;
    d(0,3) = 0.0f;
    d(1,0) = matrix.m21();
    d(1,1) = matrix.m22();
    d(1,2) = 0.0f;
    d(1,3) = 0.0f;
    d(2,0) = 0.0f;
    d(2,1) = 0.0f;
    d(2,2) = 1.0f;
    d(2,3) = 0.0f;
    d(3,0) = matrix.dx();
    d(3,1) = matrix.dy();
    d(3,2) = 0.0f;
    d(3,3) = 1.0f;
    d.mState = Internal::Matrix4x4Data::FULL;
}

inline Matrix4x4::Matrix4x4(const QMatrix4x4 &matrix)
{
    d(0,0) = matrix(1,1);
    d(0,1) = matrix(1,2);
    d(0,2) = matrix(1,3);
    d(0,3) = matrix(1,4);
    d(1,0) = matrix(2,1);
    d(1,1) = matrix(2,2);
    d(1,2) = matrix(2,3);
    d(1,3) = matrix(2,4);
    d(2,0) = matrix(3,1);
    d(2,1) = matrix(3,2);
    d(2,2) = matrix(3,3);
    d(2,3) = matrix(3,4);
    d(3,0) = matrix(4,1);
    d(3,1) = matrix(4,2);
    d(3,2) = matrix(4,3);
    d(3,3) = matrix(4,4);
    d.mState = Internal::Matrix4x4Data::FULL;
}

inline Matrix4x4::Matrix4x4(const Transform3D &transform)
{
    Q_UNUSED(transform);
    Q_ASSERT(false && "Not implemented yet.");
}

inline Matrix4x4::Matrix4x4(const Matrix2x2 &matrix)
{
    Q_UNUSED(matrix);
    Q_ASSERT(false && "Not implemented yet.");
}

inline Matrix4x4::Matrix4x4(const Matrix3x3 &matrix)
{
    Q_UNUSED(matrix);
    Q_ASSERT(false && "Not implemented yet.");
}

inline const real &Matrix4x4::operator()(int row, int column) const
{
    Q_ASSERT(0 <= row && row < 4 && 0 <= column && column < 4);
    return d(column,row);
}

inline real &Matrix4x4::operator()(int row, int column)
{
    Q_ASSERT(0 <= row && row < 4 && 0 <= column && column < 4);
    d.mState = Internal::Matrix4x4Data::FULL;
    return d(column,row);
}

inline Vector4D Matrix4x4::column(int index) const
{
    Q_ASSERT(0 <= index && index < 4);
    return Vector4D(d(index,0), d(index,1), d(index,2), d(index,3));
}

inline void Matrix4x4::setColumn(int index, const Vector4D &value)
{
    Q_ASSERT(0 <= index && index < 4);
    d(index,0) = value.d[0];
    d(index,1) = value.d[1];
    d(index,2) = value.d[2];
    d(index,3) = value.d[3];
}

inline Vector4D Matrix4x4::row(int index) const
{
    Q_ASSERT(0 <= index && index < 4);
    return Vector4D(d(0,index), d(1,index), d(2,index), d(3,index));
}

inline void Matrix4x4::setRow(int index, const Vector4D &value)
{
    Q_ASSERT(0 <= index && index < 4);
    d(0,index) = value.d[0];
    d(1,index) = value.d[1];
    d(2,index) = value.d[2];
    d(3,index) = value.d[3];
}

inline bool Matrix4x4::isIdentity() const
{
    if (d.mState == Internal::Matrix4x4Data::IDENTITY)
        return true;
    if (d(0,0) != 1.0f || d(0,1) != 0.0f || d(0,2) != 0.0f)
        return false;
    if (d(0,3) != 0.0f || d(1,0) != 0.0f || d(1,1) != 1.0f)
        return false;
    if (d(1,2) != 0.0f || d(1,3) != 0.0f || d(2,0) != 0.0f)
        return false;
    if (d(2,1) != 0.0f || d(2,2) != 1.0f || d(2,3) != 0.0f)
        return false;
    if (d(3,0) != 0.0f || d(3,1) != 0.0f || d(3,2) != 0.0f)
        return false;
    return (d(3,3) == 1.0f);
}

inline void Matrix4x4::setToIdentity()
{
    d(0,0) = 1.0f;
    d(0,1) = 0.0f;
    d(0,2) = 0.0f;
    d(0,3) = 0.0f;
    d(1,0) = 0.0f;
    d(1,1) = 1.0f;
    d(1,2) = 0.0f;
    d(1,3) = 0.0f;
    d(2,0) = 0.0f;
    d(2,1) = 0.0f;
    d(2,2) = 1.0f;
    d(2,3) = 0.0f;
    d(3,0) = 0.0f;
    d(3,1) = 0.0f;
    d(3,2) = 0.0f;
    d(3,3) = 1.0f;
    d.mState = Internal::Matrix4x4Data::IDENTITY;
}

inline void Matrix4x4::fill(real value)
{
    d(0,0) = value;
    d(0,1) = value;
    d(0,2) = value;
    d(0,3) = value;
    d(1,0) = value;
    d(1,1) = value;
    d(1,2) = value;
    d(1,3) = value;
    d(2,0) = value;
    d(2,1) = value;
    d(2,2) = value;
    d(2,3) = value;
    d(3,0) = value;
    d(3,1) = value;
    d(3,2) = value;
    d(3,3) = value;
    d.mState = Internal::Matrix4x4Data::FULL;
}

inline Matrix4x4 Matrix4x4::inverted(bool *invertible) const
{
    Internal::Matrix4x4Data result;
    gmtl::invert(result, d);
    if (invertible)
        *invertible = !result.isError();
    if (result.isError())
        return Matrix4x4();
    return Matrix4x4(result);
}

inline Matrix4x4 &Matrix4x4::invert(bool *invertible)
{
    Internal::Matrix4x4Data result;
    gmtl::invert(result, d);
    if (invertible)
        *invertible = !result.isError();
    if (!result.isError())
        d = result;
    return *this;
}

inline Matrix4x4 Matrix4x4::transposed() const
{
    Internal::Matrix4x4Data result;
    return Matrix4x4(gmtl::transpose(result, d));
}

inline Matrix4x4 &Matrix4x4::transpose()
{
    gmtl::transpose(d);
    return *this;
}

//inline Matrix3x3 Matrix4x4::normalMatrix() const
//{
//    Q_ASSERT(false && "Not implemented yet.");
//    return Matrix3x3();
//}

inline Matrix4x4 &Matrix4x4::operator+=(const Matrix4x4 &matrix)
{
    d(0,0) += matrix.d(0,0);
    d(0,1) += matrix.d(0,1);
    d(0,2) += matrix.d(0,2);
    d(0,3) += matrix.d(0,3);
    d(1,0) += matrix.d(1,0);
    d(1,1) += matrix.d(1,1);
    d(1,2) += matrix.d(1,2);
    d(1,3) += matrix.d(1,3);
    d(2,0) += matrix.d(2,0);
    d(2,1) += matrix.d(2,1);
    d(2,2) += matrix.d(2,2);
    d(2,3) += matrix.d(2,3);
    d(3,0) += matrix.d(3,0);
    d(3,1) += matrix.d(3,1);
    d(3,2) += matrix.d(3,2);
    d(3,3) += matrix.d(3,3);
    d.mState = Internal::Matrix4x4Data::FULL;
    return *this;
}

inline Matrix4x4 &Matrix4x4::operator-=(const Matrix4x4 &matrix)
{
    d(0,0) -= matrix.d(0,0);
    d(0,1) -= matrix.d(0,1);
    d(0,2) -= matrix.d(0,2);
    d(0,3) -= matrix.d(0,3);
    d(1,0) -= matrix.d(1,0);
    d(1,1) -= matrix.d(1,1);
    d(1,2) -= matrix.d(1,2);
    d(1,3) -= matrix.d(1,3);
    d(2,0) -= matrix.d(2,0);
    d(2,1) -= matrix.d(2,1);
    d(2,2) -= matrix.d(2,2);
    d(2,3) -= matrix.d(2,3);
    d(3,0) -= matrix.d(3,0);
    d(3,1) -= matrix.d(3,1);
    d(3,2) -= matrix.d(3,2);
    d(3,3) -= matrix.d(3,3);
    d.mState = Internal::Matrix4x4Data::FULL;
    return *this;
}

inline Matrix4x4 &Matrix4x4::operator*=(const Matrix4x4 &matrix)
{
    d(0,0) *= matrix.d(0,0);
    d(0,1) *= matrix.d(0,1);
    d(0,2) *= matrix.d(0,2);
    d(0,3) *= matrix.d(0,3);
    d(1,0) *= matrix.d(1,0);
    d(1,1) *= matrix.d(1,1);
    d(1,2) *= matrix.d(1,2);
    d(1,3) *= matrix.d(1,3);
    d(2,0) *= matrix.d(2,0);
    d(2,1) *= matrix.d(2,1);
    d(2,2) *= matrix.d(2,2);
    d(2,3) *= matrix.d(2,3);
    d(3,0) *= matrix.d(3,0);
    d(3,1) *= matrix.d(3,1);
    d(3,2) *= matrix.d(3,2);
    d(3,3) *= matrix.d(3,3);
    d.mState = Internal::Matrix4x4Data::FULL;
    return *this;
}

inline Matrix4x4 &Matrix4x4::operator*=(real factor)
{
    d(0,0) *= factor;
    d(0,1) *= factor;
    d(0,2) *= factor;
    d(0,3) *= factor;
    d(1,0) *= factor;
    d(1,1) *= factor;
    d(1,2) *= factor;
    d(1,3) *= factor;
    d(2,0) *= factor;
    d(2,1) *= factor;
    d(2,2) *= factor;
    d(2,3) *= factor;
    d(3,0) *= factor;
    d(3,1) *= factor;
    d(3,2) *= factor;
    d(3,3) *= factor;
    d.mState = Internal::Matrix4x4Data::FULL;
    return *this;
}

inline Matrix4x4 &Matrix4x4::operator/=(real divisor)
{
    d(0,0) /= divisor;
    d(0,1) /= divisor;
    d(0,2) /= divisor;
    d(0,3) /= divisor;
    d(1,0) /= divisor;
    d(1,1) /= divisor;
    d(1,2) /= divisor;
    d(1,3) /= divisor;
    d(2,0) /= divisor;
    d(2,1) /= divisor;
    d(2,2) /= divisor;
    d(2,3) /= divisor;
    d(3,0) /= divisor;
    d(3,1) /= divisor;
    d(3,2) /= divisor;
    d(3,3) /= divisor;
    d.mState = Internal::Matrix4x4Data::FULL;
    return *this;
}

inline bool Matrix4x4::operator==(const Matrix4x4 &matrix) const
{
    return
        d(0,0) == matrix.d(0,0) &&
        d(0,1) == matrix.d(0,1) &&
        d(0,2) == matrix.d(0,2) &&
        d(0,3) == matrix.d(0,3) &&
        d(1,0) == matrix.d(1,0) &&
        d(1,1) == matrix.d(1,1) &&
        d(1,2) == matrix.d(1,2) &&
        d(1,3) == matrix.d(1,3) &&
        d(2,0) == matrix.d(2,0) &&
        d(2,1) == matrix.d(2,1) &&
        d(2,2) == matrix.d(2,2) &&
        d(2,3) == matrix.d(2,3) &&
        d(3,0) == matrix.d(3,0) &&
        d(3,1) == matrix.d(3,1) &&
        d(3,2) == matrix.d(3,2) &&
        d(3,3) == matrix.d(3,3);
}

inline bool Matrix4x4::operator!=(const Matrix4x4 &matrix) const
{
    return
        d(0,0) != matrix.d(0,0) ||
        d(0,1) != matrix.d(0,1) ||
        d(0,2) != matrix.d(0,2) ||
        d(0,3) != matrix.d(0,3) ||
        d(1,0) != matrix.d(1,0) ||
        d(1,1) != matrix.d(1,1) ||
        d(1,2) != matrix.d(1,2) ||
        d(1,3) != matrix.d(1,3) ||
        d(2,0) != matrix.d(2,0) ||
        d(2,1) != matrix.d(2,1) ||
        d(2,2) != matrix.d(2,2) ||
        d(2,3) != matrix.d(2,3) ||
        d(3,0) != matrix.d(3,0) ||
        d(3,1) != matrix.d(3,1) ||
        d(3,2) != matrix.d(3,2) ||
        d(3,3) != matrix.d(3,3);
}

inline Matrix4x4 operator+(const Matrix4x4 &m1, const Matrix4x4 &m2)
{
    Internal::Matrix4x4Data d;
    d(0,0) = m1.d(0,0) + m2.d(0,0);
    d(0,1) = m1.d(0,1) + m2.d(0,1);
    d(0,2) = m1.d(0,2) + m2.d(0,2);
    d(0,3) = m1.d(0,3) + m2.d(0,3);
    d(1,0) = m1.d(1,0) + m2.d(1,0);
    d(1,1) = m1.d(1,1) + m2.d(1,1);
    d(1,2) = m1.d(1,2) + m2.d(1,2);
    d(1,3) = m1.d(1,3) + m2.d(1,3);
    d(2,0) = m1.d(2,0) + m2.d(2,0);
    d(2,1) = m1.d(2,1) + m2.d(2,1);
    d(2,2) = m1.d(2,2) + m2.d(2,2);
    d(2,3) = m1.d(2,3) + m2.d(2,3);
    d(3,0) = m1.d(3,0) + m2.d(3,0);
    d(3,1) = m1.d(3,1) + m2.d(3,1);
    d(3,2) = m1.d(3,2) + m2.d(3,2);
    d(3,3) = m1.d(3,3) + m2.d(3,3);
    return Matrix4x4(d);
}

inline Matrix4x4 operator-(const Matrix4x4& m1, const Matrix4x4& m2)
{
    Internal::Matrix4x4Data d;
    d(0,0) = m1.d(0,0) - m2.d(0,0);
    d(0,1) = m1.d(0,1) - m2.d(0,1);
    d(0,2) = m1.d(0,2) - m2.d(0,2);
    d(0,3) = m1.d(0,3) - m2.d(0,3);
    d(1,0) = m1.d(1,0) - m2.d(1,0);
    d(1,1) = m1.d(1,1) - m2.d(1,1);
    d(1,2) = m1.d(1,2) - m2.d(1,2);
    d(1,3) = m1.d(1,3) - m2.d(1,3);
    d(2,0) = m1.d(2,0) - m2.d(2,0);
    d(2,1) = m1.d(2,1) - m2.d(2,1);
    d(2,2) = m1.d(2,2) - m2.d(2,2);
    d(2,3) = m1.d(2,3) - m2.d(2,3);
    d(3,0) = m1.d(3,0) - m2.d(3,0);
    d(3,1) = m1.d(3,1) - m2.d(3,1);
    d(3,2) = m1.d(3,2) - m2.d(3,2);
    d(3,3) = m1.d(3,3) - m2.d(3,3);
    return Matrix4x4(d);
}

inline Matrix4x4 operator*(const Matrix4x4 &m1, const Matrix4x4 &m2)
{
    return Matrix4x4(Internal::Matrix4x4Data(m1.d * m2.d));
}

inline Point2D operator*(const Matrix4x4 &matrix, const Point2D &point)
{
    qreal xin, yin;
    qreal x, y, w;
    xin = point.d[0];
    yin = point.d[1];
    if (matrix.d.mState == Internal::Matrix4x4Data::IDENTITY) {
        return point;
    } else if (matrix.d.mState == Internal::Matrix4x4Data::TRANS) {
        return Point2D(qRound(xin + matrix.d(3,0)),
                       qRound(yin + matrix.d(3,1)));
    } else if (matrix.d.mState == (Internal::Matrix4x4Data::TRANS | Internal::Matrix4x4Data::AFFINE)) {
        return Point2D(qRound(xin * matrix.d(0,0) + matrix.d(3,0)),
                       qRound(yin * matrix.d(1,1) + matrix.d(3,1)));
    } else if (matrix.d.mState == Internal::Matrix4x4Data::AFFINE) {
        return Point2D(qRound(xin * matrix.d(0,0)),
                       qRound(yin * matrix.d(1,1)));
    } else {
        x = xin * matrix.d(0,0) +
            yin * matrix.d(1,0) +
            matrix.d(3,0);
        y = xin * matrix.d(0,1) +
            yin * matrix.d(1,1) +
            matrix.d(3,1);
        w = xin * matrix.d(0,3) +
            yin * matrix.d(1,3) +
            matrix.d(3,3);
        if (w == 1.0f)
            return Point2D(x, y);
        else
            return Point2D(x / w, y / w);
    }
}

inline Point2D operator*(const Point2D &point, const Matrix4x4 &matrix)
{
    qreal xin, yin;
    qreal x, y, w;
    xin = point.d[0];
    yin = point.d[1];
    x = xin * matrix.d(0,0) +
        yin * matrix.d(0,1) +
        matrix.d(0,3);
    y = xin * matrix.d(1,0) +
        yin * matrix.d(1,1) +
        matrix.d(1,3);
    w = xin * matrix.d(3,0) +
        yin * matrix.d(3,1) +
        matrix.d(3,3);
    if (w == 1.0f) {
        return Point2D(qreal(x), qreal(y));
    } else {
        return Point2D(qreal(x / w), qreal(y / w));
    }
}

inline Point3D operator*(const Matrix4x4 &matrix, const Point3D &point)
{
    real x, y, z, w;
    x = point.d[0] * matrix.d(0,0) +
        point.d[1] * matrix.d(0,1) +
        point.d[2] * matrix.d(0,2) +
        matrix.d(0,3);
    y = point.d[0] * matrix.d(1,0) +
        point.d[1] * matrix.d(1,1) +
        point.d[2] * matrix.d(1,2) +
        matrix.d(1,3);
    z = point.d[0] * matrix.d(2,0) +
        point.d[1] * matrix.d(2,1) +
        point.d[2] * matrix.d(2,2) +
        matrix.d(2,3);
    w = point.d[0] * matrix.d(3,0) +
        point.d[1] * matrix.d(3,1) +
        point.d[2] * matrix.d(3,2) +
        matrix.d(3,3);
    if (w == 1.0f)
        return Point3D(x, y, z);
    else
        return Point3D(x / w, y / w, z / w);
}

inline Point3D operator*(const Point3D &point, const Matrix4x4 &matrix)
{
    qreal x, y, z, w;
    if (matrix.d.mState == Internal::Matrix4x4Data::IDENTITY) {
        return point;
    } else if (matrix.d.mState == Internal::Matrix4x4Data::TRANS) {
        return Point3D(point.d[0] + matrix.d(3,0),
                       point.d[1] + matrix.d(3,1),
                       point.d[2] + matrix.d(3,2));
    } else if (matrix.d.mState == (Internal::Matrix4x4Data::TRANS | Internal::Matrix4x4Data::AFFINE)) {
        return Point3D(point.d[0] * matrix.d(0,0) + matrix.d(3,0),
                       point.d[1] * matrix.d(1,1) + matrix.d(3,1),
                       point.d[2] * matrix.d(2,2) + matrix.d(3,2));
    } else if (matrix.d.mState == Internal::Matrix4x4Data::AFFINE) {
        return Point3D(point.d[0] * matrix.d(0,0),
                       point.d[1] * matrix.d(1,1),
                       point.d[2] * matrix.d(2,2));
    } else {
        x = point.d[0] * matrix.d(0,0) +
            point.d[1] * matrix.d(1,0) +
            point.d[2] * matrix.d(2,0) +
            matrix.d(3,0);
        y = point.d[0] * matrix.d(0,1) +
            point.d[1] * matrix.d(1,1) +
            point.d[2] * matrix.d(2,1) +
            matrix.d(3,1);
        z = point.d[0] * matrix.d(0,2) +
            point.d[1] * matrix.d(1,2) +
            point.d[2] * matrix.d(2,2) +
            matrix.d(3,2);
        w = point.d[0] * matrix.d(0,3) +
            point.d[1] * matrix.d(1,3) +
            point.d[2] * matrix.d(2,3) +
            matrix.d(3,3);
        if (w == 1.0f)
            return Point3D(x, y, z);
        else
            return Point3D(x / w, y / w, z / w);
    }
}

inline Point4D operator*(const Matrix4x4& matrix, const Point4D& point)
{
    real x, y, z, w;
    x = point.d[0] * matrix.d(0,0) +
        point.d[1] * matrix.d(1,0) +
        point.d[2] * matrix.d(2,0) +
        point.d[3] * matrix.d(3,0);
    y = point.d[0] * matrix.d(0,1) +
        point.d[1] * matrix.d(1,1) +
        point.d[2] * matrix.d(2,1) +
        point.d[3] * matrix.d(3,1);
    z = point.d[0] * matrix.d(0,2) +
        point.d[1] * matrix.d(1,2) +
        point.d[2] * matrix.d(2,2) +
        point.d[3] * matrix.d(3,2);
    w = point.d[0] * matrix.d(0,3) +
        point.d[1] * matrix.d(1,3) +
        point.d[2] * matrix.d(2,3) +
        point.d[3] * matrix.d(3,3);
    return Point4D(x, y, z, w);
}

inline Point4D operator*(const Point4D& point, const Matrix4x4& matrix)
{
    real x, y, z, w;
    x = point.d[0] * matrix.d(0,0) +
        point.d[1] * matrix.d(0,1) +
        point.d[2] * matrix.d(0,2) +
        point.d[3] * matrix.d(0,3);
    y = point.d[0] * matrix.d(1,0) +
        point.d[1] * matrix.d(1,1) +
        point.d[2] * matrix.d(1,2) +
        point.d[3] * matrix.d(1,3);
    z = point.d[0] * matrix.d(2,0) +
        point.d[1] * matrix.d(2,1) +
        point.d[2] * matrix.d(2,2) +
        point.d[3] * matrix.d(2,3);
    w = point.d[0] * matrix.d(3,0) +
        point.d[1] * matrix.d(3,1) +
        point.d[2] * matrix.d(3,2) +
        point.d[3] * matrix.d(3,3);
    return Point4D(x, y, z, w);
}

// TODO: Check this.  This was taken from QMatrix4x4::mapVector().
// I'm not sure it was the correct implementation to use.
inline Vector3D operator*(const Vector3D &vector, const Matrix4x4 &matrix)
{
    if (matrix.d.mState == Internal::Matrix4x4Data::IDENTITY ||
        matrix.d.mState == Internal::Matrix4x4Data::TRANS) {
        return vector;
    } else if (matrix.d.mState == Internal::Matrix4x4Data::AFFINE ||
               matrix.d.mState == (Internal::Matrix4x4Data::TRANS | Internal::Matrix4x4Data::AFFINE)) {
        return Vector3D(
            vector.d[0] * matrix.d(0,0),
            vector.d[1] * matrix.d(1,1),
            vector.d[2] * matrix.d(2,2));
    } else {
        return Vector3D(
            vector.d[0] * matrix.d(0,0) +
            vector.d[1] * matrix.d(1,0) +
            vector.d[2] * matrix.d(2,0),
            vector.d[0] * matrix.d(0,1) +
            vector.d[1] * matrix.d(1,1) +
            vector.d[2] * matrix.d(2,1),
            vector.d[1] * matrix.d(0,2) +
            vector.d[2] * matrix.d(1,2) +
            vector.d[3] * matrix.d(2,2));
    }
}

inline QPoint operator*(const Matrix4x4& matrix, const QPoint& point)
{
    qreal xin, yin;
    qreal x, y, w;
    xin = point.x();
    yin = point.y();
    if (matrix.d.mState == Internal::Matrix4x4Data::IDENTITY) {
        return point;
    } else if (matrix.d.mState == Internal::Matrix4x4Data::TRANS) {
        return QPoint(qRound(xin + matrix.d(3,0)),
                      qRound(yin + matrix.d(3,1)));
    } else if (matrix.d.mState == (Internal::Matrix4x4Data::TRANS | Internal::Matrix4x4Data::AFFINE)) {
        return QPoint(qRound(xin * matrix.d(0,0) + matrix.d(3,0)),
                      qRound(yin * matrix.d(1,1) + matrix.d(3,1)));
    } else if (matrix.d.mState == Internal::Matrix4x4Data::AFFINE) {
        return QPoint(qRound(xin * matrix.d(0,0)),
                      qRound(yin * matrix.d(1,1)));
    } else {
        x = xin * matrix.d(0,0) +
            yin * matrix.d(1,0) +
            matrix.d(3,0);
        y = xin * matrix.d(0,1) +
            yin * matrix.d(1,1) +
            matrix.d(3,1);
        w = xin * matrix.d(0,3) +
            yin * matrix.d(1,3) +
            matrix.d(3,3);
        if (w == 1.0f)
            return QPoint(qRound(x), qRound(y));
        else
            return QPoint(qRound(x / w), qRound(y / w));
    }
}

inline QPoint operator*(const QPoint& point, const Matrix4x4& matrix)
{
    real xin, yin;
    real x, y, w;
    xin = point.x();
    yin = point.y();
    x = xin * matrix.d(0,0) +
        yin * matrix.d(0,1) +
        matrix.d(0,3);
    y = xin * matrix.d(1,0) +
        yin * matrix.d(1,1) +
        matrix.d(1,3);
    w = xin * matrix.d(3,0) +
        yin * matrix.d(3,1) +
        matrix.d(3,3);
    if (w == 1.0f)
        return QPoint(qRound(x), qRound(y));
    else
        return QPoint(qRound(x / w), qRound(y / w));
}

inline QPointF operator*(const Matrix4x4& matrix, const QPointF& point)
{
    qreal xin, yin;
    qreal x, y, w;
    xin = point.x();
    yin = point.y();
    if (matrix.d.mState == Internal::Matrix4x4Data::IDENTITY) {
        return point;
    } else if (matrix.d.mState == Internal::Matrix4x4Data::TRANS) {
        return QPoint(qRound(xin + matrix.d(3,0)),
                      qRound(yin + matrix.d(3,1)));
    } else if (matrix.d.mState == (Internal::Matrix4x4Data::TRANS | Internal::Matrix4x4Data::AFFINE)) {
        return QPoint(qRound(xin * matrix.d(0,0) + matrix.d(3,0)),
                      qRound(yin * matrix.d(1,1) + matrix.d(3,1)));
    } else if (matrix.d.mState == Internal::Matrix4x4Data::AFFINE) {
        return QPoint(qRound(xin * matrix.d(0,0)),
                      qRound(yin * matrix.d(1,1)));
    } else {
        x = xin * matrix.d(0,0) +
            yin * matrix.d(1,0) +
            matrix.d(3,0);
        y = xin * matrix.d(0,1) +
            yin * matrix.d(1,1) +
            matrix.d(3,1);
        w = xin * matrix.d(0,3) +
            yin * matrix.d(1,3) +
            matrix.d(3,3);
        if (w == 1.0f)
            return QPointF(x, y);
        else
            return QPointF(x / w, y / w);
    }
}

inline QPointF operator*(const QPointF& point, const Matrix4x4& matrix)
{
    qreal xin, yin;
    qreal x, y, w;
    xin = point.x();
    yin = point.y();
    x = xin * matrix.d(0,0) +
        yin * matrix.d(0,1) +
        matrix.d(0,3);
    y = xin * matrix.d(1,0) +
        yin * matrix.d(1,1) +
        matrix.d(1,3);
    w = xin * matrix.d(3,0) +
        yin * matrix.d(3,1) +
        matrix.d(3,3);
    if (w == 1.0f) {
        return QPointF(qreal(x), qreal(y));
    } else {
        return QPointF(qreal(x / w), qreal(y / w));
    }
}

inline Matrix4x4 operator-(const Matrix4x4& matrix)
{
    Internal::Matrix4x4Data md;
    md(0,0) = -matrix.d(0,0);
    md(0,1) = -matrix.d(0,1);
    md(0,2) = -matrix.d(0,2);
    md(0,3) = -matrix.d(0,3);
    md(1,0) = -matrix.d(1,0);
    md(1,1) = -matrix.d(1,1);
    md(1,2) = -matrix.d(1,2);
    md(1,3) = -matrix.d(1,3);
    md(2,0) = -matrix.d(2,0);
    md(2,1) = -matrix.d(2,1);
    md(2,2) = -matrix.d(2,2);
    md(2,3) = -matrix.d(2,3);
    md(3,0) = -matrix.d(3,0);
    md(3,1) = -matrix.d(3,1);
    md(3,2) = -matrix.d(3,2);
    md(3,3) = -matrix.d(3,3);
    return Matrix4x4(md);
}

inline Matrix4x4 operator*(const Matrix4x4& matrix, real factor)
{
    Internal::Matrix4x4Data md;
    md(0,0) = matrix.d(0,0) * factor;
    md(0,1) = matrix.d(0,1) * factor;
    md(0,2) = matrix.d(0,2) * factor;
    md(0,3) = matrix.d(0,3) * factor;
    md(1,0) = matrix.d(1,0) * factor;
    md(1,1) = matrix.d(1,1) * factor;
    md(1,2) = matrix.d(1,2) * factor;
    md(1,3) = matrix.d(1,3) * factor;
    md(2,0) = matrix.d(2,0) * factor;
    md(2,1) = matrix.d(2,1) * factor;
    md(2,2) = matrix.d(2,2) * factor;
    md(2,3) = matrix.d(2,3) * factor;
    md(3,0) = matrix.d(3,0) * factor;
    md(3,1) = matrix.d(3,1) * factor;
    md(3,2) = matrix.d(3,2) * factor;
    md(3,3) = matrix.d(3,3) * factor;
    return Matrix4x4(md);
}

inline Matrix4x4 operator*(real factor, const Matrix4x4& matrix)
{
    Internal::Matrix4x4Data md;
    md(0,0) = matrix.d(0,0) * factor;
    md(0,1) = matrix.d(0,1) * factor;
    md(0,2) = matrix.d(0,2) * factor;
    md(0,3) = matrix.d(0,3) * factor;
    md(1,0) = matrix.d(1,0) * factor;
    md(1,1) = matrix.d(1,1) * factor;
    md(1,2) = matrix.d(1,2) * factor;
    md(1,3) = matrix.d(1,3) * factor;
    md(2,0) = matrix.d(2,0) * factor;
    md(2,1) = matrix.d(2,1) * factor;
    md(2,2) = matrix.d(2,2) * factor;
    md(2,3) = matrix.d(2,3) * factor;
    md(3,0) = matrix.d(3,0) * factor;
    md(3,1) = matrix.d(3,1) * factor;
    md(3,2) = matrix.d(3,2) * factor;
    md(3,3) = matrix.d(3,3) * factor;
    return Matrix4x4(md);
}

inline bool qFuzzyCompare(const Matrix4x4& m1, const Matrix4x4& m2)
{
    return
        ::qFuzzyCompare(m1.d(0,0), m2.d(0,0)) &&
        ::qFuzzyCompare(m1.d(0,1), m2.d(0,1)) &&
        ::qFuzzyCompare(m1.d(0,2), m2.d(0,2)) &&
        ::qFuzzyCompare(m1.d(0,3), m2.d(0,3)) &&
        ::qFuzzyCompare(m1.d(1,0), m2.d(1,0)) &&
        ::qFuzzyCompare(m1.d(1,1), m2.d(1,1)) &&
        ::qFuzzyCompare(m1.d(1,2), m2.d(1,2)) &&
        ::qFuzzyCompare(m1.d(1,3), m2.d(1,3)) &&
        ::qFuzzyCompare(m1.d(2,0), m2.d(2,0)) &&
        ::qFuzzyCompare(m1.d(2,1), m2.d(2,1)) &&
        ::qFuzzyCompare(m1.d(2,2), m2.d(2,2)) &&
        ::qFuzzyCompare(m1.d(2,3), m2.d(2,3)) &&
        ::qFuzzyCompare(m1.d(3,0), m2.d(3,0)) &&
        ::qFuzzyCompare(m1.d(3,1), m2.d(3,1)) &&
        ::qFuzzyCompare(m1.d(3,2), m2.d(3,2)) &&
        ::qFuzzyCompare(m1.d(3,3), m2.d(3,3));
}

inline void Matrix4x4::scale(const Vector3D &vector)
{
    real vx = vector.d[0];
    real vy = vector.d[1];
    real vz = vector.d[2];
    if (d.mState == Internal::Matrix4x4Data::IDENTITY) {
        d(0,0) = vx;
        d(1,1) = vy;
        d(2,2) = vz;
        d.mState = Internal::Matrix4x4Data::AFFINE;
    } else if (d.mState == Internal::Matrix4x4Data::AFFINE ||
               d.mState == (Internal::Matrix4x4Data::AFFINE | Internal::Matrix4x4Data::TRANS)) {
        d(0,0) *= vx;
        d(1,1) *= vy;
        d(2,2) *= vz;
    } else if (d.mState == Internal::Matrix4x4Data::TRANS) {
        d(0,0) = vx;
        d(1,1) = vy;
        d(2,2) = vz;
        d.mState |= Internal::Matrix4x4Data::AFFINE;
    } else {
        d(0,0) *= vx;
        d(0,1) *= vx;
        d(0,2) *= vx;
        d(0,3) *= vx;
        d(1,0) *= vy;
        d(1,1) *= vy;
        d(1,2) *= vy;
        d(1,3) *= vy;
        d(2,0) *= vz;
        d(2,1) *= vz;
        d(2,2) *= vz;
        d(2,3) *= vz;
        d.mState = Internal::Matrix4x4Data::FULL;
    }
}

inline void Matrix4x4::translate(const Vector3D &vector)
{
    real vx = vector.d[0];
    real vy = vector.d[1];
    real vz = vector.d[2];
    if (d.mState == Internal::Matrix4x4Data::IDENTITY) {
        d(3,0) = vx;
        d(3,1) = vy;
        d(3,2) = vz;
        d.mState = Internal::Matrix4x4Data::TRANS;
    } else if (d.mState == Internal::Matrix4x4Data::TRANS) {
        d(3,0) += vx;
        d(3,1) += vy;
        d(3,2) += vz;
    } else if (d.mState == Internal::Matrix4x4Data::AFFINE) {
        d(3,0) = d(0,0) * vx;
        d(3,1) = d(1,1) * vy;
        d(3,2) = d(2,2) * vz;
        d.mState |= Internal::Matrix4x4Data::TRANS;
    } else if (d.mState == (Internal::Matrix4x4Data::AFFINE | Internal::Matrix4x4Data::TRANS)) {
        d(3,0) += d(0,0) * vx;
        d(3,1) += d(1,1) * vy;
        d(3,2) += d(2,2) * vz;
    } else {
        d(3,0) += d(0,0) * vx + d(1,0) * vy + d(2,0) * vz;
        d(3,1) += d(0,1) * vx + d(1,1) * vy + d(2,1) * vz;
        d(3,2) += d(0,2) * vx + d(1,2) * vy + d(2,2) * vz;
        d(3,3) += d(0,3) * vx + d(1,3) * vy + d(2,3) * vz;
        if (d.mState == Internal::Matrix4x4Data::ORTHOGONAL)
            d.mState |= Internal::Matrix4x4Data::TRANS;
        else if (d.mState != (Internal::Matrix4x4Data::ORTHOGONAL | Internal::Matrix4x4Data::TRANS))
            d.mState = Internal::Matrix4x4Data::FULL;
    }
}

inline void Matrix4x4::rotate(real angle, const Vector3D &vector)
{
    rotate(angle, vector.d[0], vector.d[1], vector.d[2]);
}

inline void Matrix4x4::scale(real x, real y)
{
    if (d.mState == Internal::Matrix4x4Data::IDENTITY) {
        d(0,0) = x;
        d(1,1) = y;
        d.mState = Internal::Matrix4x4Data::AFFINE;
    } else if (d.mState == Internal::Matrix4x4Data::AFFINE ||
               d.mState == (Internal::Matrix4x4Data::AFFINE | Internal::Matrix4x4Data::TRANS)) {
        d(0,0) *= x;
        d(1,1) *= y;
    } else if (d.mState == Internal::Matrix4x4Data::TRANS) {
        d(0,0) = x;
        d(1,1) = y;
        d.mState |= Internal::Matrix4x4Data::AFFINE;
    } else {
        d(0,0) *= x;
        d(0,1) *= x;
        d(0,2) *= x;
        d(0,3) *= x;
        d(1,0) *= y;
        d(1,1) *= y;
        d(1,2) *= y;
        d(1,3) *= y;
        d.mState = Internal::Matrix4x4Data::FULL;
    }
}

inline void Matrix4x4::scale(real x, real y, real z)
{
    if (d.mState == Internal::Matrix4x4Data::IDENTITY) {
        d(0,0) = x;
        d(1,1) = y;
        d(2,2) = z;
        d.mState = Internal::Matrix4x4Data::AFFINE;
    } else if (d.mState == Internal::Matrix4x4Data::AFFINE ||
               d.mState == (Internal::Matrix4x4Data::AFFINE | Internal::Matrix4x4Data::ORTHOGONAL)) {
        d(0,0) *= x;
        d(1,1) *= y;
        d(2,2) *= z;
    } else if (d.mState == Internal::Matrix4x4Data::ORTHOGONAL) {
        d(0,0) = x;
        d(1,1) = y;
        d(2,2) = z;
        d.mState |= Internal::Matrix4x4Data::AFFINE;
    } else {
        d(0,0) *= x;
        d(0,1) *= x;
        d(0,2) *= x;
        d(0,3) *= x;
        d(1,0) *= y;
        d(1,1) *= y;
        d(1,2) *= y;
        d(1,3) *= y;
        d(2,0) *= z;
        d(2,1) *= z;
        d(2,2) *= z;
        d(2,3) *= z;
        d.mState = Internal::Matrix4x4Data::FULL;
    }
}

inline void Matrix4x4::scale(real factor)
{
    if (d.mState == Internal::Matrix4x4Data::IDENTITY) {
        d(0,0) = factor;
        d(1,1) = factor;
        d(2,2) = factor;
        d.mState = Internal::Matrix4x4Data::AFFINE;
    } else if (d.mState == Internal::Matrix4x4Data::AFFINE ||
               d.mState == (Internal::Matrix4x4Data::AFFINE | Internal::Matrix4x4Data::TRANS)) {
        d(0,0) *= factor;
        d(1,1) *= factor;
        d(2,2) *= factor;
    } else if (d.mState == Internal::Matrix4x4Data::TRANS) {
        d(0,0) = factor;
        d(1,1) = factor;
        d(2,2) = factor;
        d.mState |= Internal::Matrix4x4Data::AFFINE;
    } else {
        d(0,0) *= factor;
        d(0,1) *= factor;
        d(0,2) *= factor;
        d(0,3) *= factor;
        d(1,0) *= factor;
        d(1,1) *= factor;
        d(1,2) *= factor;
        d(1,3) *= factor;
        d(2,0) *= factor;
        d(2,1) *= factor;
        d(2,2) *= factor;
        d(2,3) *= factor;
        d.mState = Internal::Matrix4x4Data::FULL;
    }
}

inline void Matrix4x4::translate(real x, real y)
{
    if (d.mState == Internal::Matrix4x4Data::IDENTITY) {
        d(3,0) = x;
        d(3,1) = y;
        d.mState = Internal::Matrix4x4Data::TRANS;
    } else if (d.mState == Internal::Matrix4x4Data::TRANS) {
        d(3,0) += x;
        d(3,1) += y;
    } else if (d.mState == Internal::Matrix4x4Data::AFFINE) {
        d(3,0) = d(0,0) * x;
        d(3,1) = d(1,1) * y;
        d(3,2) = 0.;
        d.mState |= Internal::Matrix4x4Data::TRANS;
    } else if (d.mState == (Internal::Matrix4x4Data::AFFINE | Internal::Matrix4x4Data::TRANS)) {
        d(3,0) += d(0,0) * x;
        d(3,1) += d(1,1) * y;
    } else {
        d(3,0) += d(0,0) * x + d(1,0) * y;
        d(3,1) += d(0,1) * x + d(1,1) * y;
        d(3,2) += d(0,2) * x + d(1,2) * y;
        d(3,3) += d(0,3) * x + d(1,3) * y;
        if (d.mState == Internal::Matrix4x4Data::ORTHOGONAL)
            d.mState |= Internal::Matrix4x4Data::TRANS;
        else if (d.mState != (Internal::Matrix4x4Data::ORTHOGONAL | Internal::Matrix4x4Data::TRANS))
            d.mState = Internal::Matrix4x4Data::FULL;
    }
}

inline void Matrix4x4::translate(real x, real y, real z)
{
    if (d.mState == Internal::Matrix4x4Data::IDENTITY) {
        d(3,0) = x;
        d(3,1) = y;
        d(3,2) = z;
        d.mState = Internal::Matrix4x4Data::TRANS;
    } else if (d.mState == Internal::Matrix4x4Data::TRANS) {
        d(3,0) += x;
        d(3,1) += y;
        d(3,2) += z;
    } else if (d.mState == Internal::Matrix4x4Data::AFFINE) {
        d(3,0) = d(0,0) * x;
        d(3,1) = d(1,1) * y;
        d(3,2) = d(2,2) * z;
        d.mState |= Internal::Matrix4x4Data::TRANS;
    } else if (d.mState == (Internal::Matrix4x4Data::AFFINE | Internal::Matrix4x4Data::TRANS)) {
        d(3,0) += d(0,0) * x;
        d(3,1) += d(1,1) * y;
        d(3,2) += d(2,2) * z;
    } else {
        d(3,0) += d(0,0) * x + d(1,0) * y + d(2,0) * z;
        d(3,1) += d(0,1) * x + d(1,1) * y + d(2,1) * z;
        d(3,2) += d(0,2) * x + d(1,2) * y + d(2,2) * z;
        d(3,3) += d(0,3) * x + d(1,3) * y + d(2,3) * z;
        if (d.mState == Internal::Matrix4x4Data::ORTHOGONAL)
            d.mState |= Internal::Matrix4x4Data::TRANS;
        else if (d.mState != (Internal::Matrix4x4Data::ORTHOGONAL | Internal::Matrix4x4Data::TRANS))
            d.mState = Internal::Matrix4x4Data::FULL;
    }
}

inline void Matrix4x4::rotate(real angle, real x, real y, real z)
{
    if (angle == 0.0f)
        return;
    Matrix4x4 m;
    real c, s, ic;
    if (angle == 90.0f || angle == -270.0f) {
        s = 1.0f;
        c = 0.0f;
    } else if (angle == -90.0f || angle == 270.0f) {
        s = -1.0f;
        c = 0.0f;
    } else if (angle == 180.0f || angle == -180.0f) {
        s = 0.0f;
        c = -1.0f;
    } else {
        real a = angle * M_PI / 180.0f;
        c = qCos(a);
        s = qSin(a);
    }
    bool quick = false;
    if (x == 0.0f) {
        if (y == 0.0f) {
            if (z != 0.0f) {
                // Rotate around the Z axis.
                m.setToIdentity();
                m.d(0,0) = c;
                m.d(1,1) = c;
                if (z < 0.0f) {
                    m.d(1,0) = s;
                    m.d(0,1) = -s;
                } else {
                    m.d(1,0) = -s;
                    m.d(0,1) = s;
                }
                m.d.mState = Internal::Matrix4x4Data::FULL;
                quick = true;
            }
        } else if (z == 0.0f) {
            // Rotate around the Y axis.
            m.setToIdentity();
            m.d(0,0) = c;
            m.d(2,2) = c;
            if (y < 0.0f) {
                m.d(2,0) = -s;
                m.d(0,2) = s;
            } else {
                m.d(2,0) = s;
                m.d(0,2) = -s;
            }
            m.d.mState = Internal::Matrix4x4Data::FULL;
            quick = true;
        }
    } else if (y == 0.0f && z == 0.0f) {
        // Rotate around the X axis.
        m.setToIdentity();
        m.d(1,1) = c;
        m.d(2,2) = c;
        if (x < 0.0f) {
            m.d(2,1) = s;
            m.d(1,2) = -s;
        } else {
            m.d(2,1) = -s;
            m.d(1,2) = s;
        }
        m.d.mState = Internal::Matrix4x4Data::FULL;
        quick = true;
    }
    if (!quick) {
        real len = x * x + y * y + z * z;
        if (!qFuzzyIsNull(len - 1.0f) && !qFuzzyIsNull(len)) {
            len = qSqrt(len);
            x /= len;
            y /= len;
            z /= len;
        }
        ic = 1.0f - c;
        m.d(0,0) = x * x * ic + c;
        m.d(1,0) = x * y * ic - z * s;
        m.d(2,0) = x * z * ic + y * s;
        m.d(3,0) = 0.0f;
        m.d(0,1) = y * x * ic + z * s;
        m.d(1,1) = y * y * ic + c;
        m.d(2,1) = y * z * ic - x * s;
        m.d(3,1) = 0.0f;
        m.d(0,2) = x * z * ic - y * s;
        m.d(1,2) = y * z * ic + x * s;
        m.d(2,2) = z * z * ic + c;
        m.d(3,2) = 0.0f;
        m.d(0,3) = 0.0f;
        m.d(1,3) = 0.0f;
        m.d(2,3) = 0.0f;
        m.d(3,3) = 1.0f;
    }
    int state = d.mState;
    *this *= m;
    if (state != Internal::Matrix4x4Data::IDENTITY)
        d.mState = state | Internal::Matrix4x4Data::ORTHOGONAL;
    else
        d.mState = Internal::Matrix4x4Data::ORTHOGONAL;
}

inline void Matrix4x4::rotate(const Quaternion &quaternion)
{
    Q_ASSERT(false && "Not implemented yet.");
}

inline void Matrix4x4::ortho(const QRect &rect)
{
    // Note: rect.right() and rect.bottom() subtract 1 in QRect,
    // which gives the location of a pixel within the rectangle,
    // instead of the extent of the rectangle.  We want the extent.
    // QRectF expresses the extent properly.
    ortho(rect.x(), rect.x() + rect.width(), rect.y() + rect.height(), rect.y(), -1.0f, 1.0f);
}

inline void Matrix4x4::ortho(const QRectF &rect)
{
    ortho(rect.left(), rect.right(), rect.bottom(), rect.top(), -1.0f, 1.0f);
}

inline void Matrix4x4::ortho(real left, real right, real bottom, real top, real nearPlane, real farPlane)
{
    // Bail out if the projection volume is zero-sized.
    if (left == right || bottom == top || nearPlane == farPlane)
        return;

    // Construct the projection.
    real width = right - left;
    real invheight = top - bottom;
    real clip = farPlane - nearPlane;
    if (clip == 2.0f && (nearPlane + farPlane) == 0.0f) {
        // We can express this projection as a translate and scale
        // which will be more efficient to modify with further
        // transformations than producing a "General" matrix.
        translate(Vector3D(-(left + right) / width, -(top + bottom) / invheight, 0.0f));
        scale(Vector3D(2.0f / width, 2.0f / invheight, -1.0f));
        return;
    }
    Internal::Matrix4x4Data d;
    d(0,0) = 2.0f / width;
    d(1,0) = 0.0f;
    d(2,0) = 0.0f;
    d(3,0) = -(left + right) / width;
    d(0,1) = 0.0f;
    d(1,1) = 2.0f / invheight;
    d(2,1) = 0.0f;
    d(3,1) = -(top + bottom) / invheight;
    d(0,2) = 0.0f;
    d(1,2) = 0.0f;
    d(2,2) = -2.0f / clip;
    d(3,2) = -(nearPlane + farPlane) / clip;
    d(0,3) = 0.0f;
    d(1,3) = 0.0f;
    d(2,3) = 0.0f;
    d(3,3) = 1.0f;

    // Apply the projection.
    this->d *= d;
    return;
}

inline void Matrix4x4::frustum(real left, real right, real bottom, real top, real nearPlane, real farPlane)
{
    // Bail out if the projection volume is zero-sized.
    if (left == right || bottom == top || nearPlane == farPlane)
        return;

    // Construct the projection.
    Internal::Matrix4x4Data d;
    real width = right - left;
    real invheight = top - bottom;
    real clip = farPlane - nearPlane;
    d(0,0) = 2.0f * nearPlane / width;
    d(1,0) = 0.0f;
    d(2,0) = (left + right) / width;
    d(3,0) = 0.0f;
    d(0,1) = 0.0f;
    d(1,1) = 2.0f * nearPlane / invheight;
    d(2,1) = (top + bottom) / invheight;
    d(3,1) = 0.0f;
    d(0,2) = 0.0f;
    d(1,2) = 0.0f;
    d(2,2) = -(nearPlane + farPlane) / clip;
    d(3,2) = -2.0f * nearPlane * farPlane / clip;
    d(0,3) = 0.0f;
    d(1,3) = 0.0f;
    d(2,3) = -1.0f;
    d(3,3) = 0.0f;

    // Apply the projection.
    this->d *= d;
}

inline void Matrix4x4::perspective(real angle, real aspect, real nearPlane, real farPlane)
{
    // Bail out if the projection volume is zero-sized.
    if (nearPlane == farPlane || aspect == 0.0f)
        return;

    // Construct the projection.
    Internal::Matrix4x4Data d;
    real radians = (angle / 2.0f) * M_PI / 180.0f;
    real sine = qSin(radians);
    if (sine == 0.0f)
        return;
    real cotan = qCos(radians) / sine;
    real clip = farPlane - nearPlane;
    d(0,0) = cotan / aspect;
    d(1,0) = 0.0f;
    d(2,0) = 0.0f;
    d(3,0) = 0.0f;
    d(0,1) = 0.0f;
    d(1,1) = cotan;
    d(2,1) = 0.0f;
    d(3,1) = 0.0f;
    d(0,2) = 0.0f;
    d(1,2) = 0.0f;
    d(2,2) = -(nearPlane + farPlane) / clip;
    d(3,2) = -(2.0f * nearPlane * farPlane) / clip;
    d(0,3) = 0.0f;
    d(1,3) = 0.0f;
    d(2,3) = -1.0f;
    d(3,3) = 0.0f;

    // Apply the projection.
    this->d *= d;
}

inline void Matrix4x4::lookAt(const Vector3D &eye, const Vector3D &center, const Vector3D &up)
{
    Vector3D forward = (center - eye).normalized();
    Vector3D side = forward.crossProduct(up).normalized();
    Vector3D upVector = side.crossProduct(forward);

    Internal::Matrix4x4Data d;
    d(0,0) = side.x();
    d(1,0) = side.y();
    d(2,0) = side.z();
    d(3,0) = 0.0f;
    d(0,1) = upVector.x();
    d(1,1) = upVector.y();
    d(2,1) = upVector.z();
    d(3,1) = 0.0f;
    d(0,2) = -forward.x();
    d(1,2) = -forward.y();
    d(2,2) = -forward.z();
    d(3,2) = 0.0f;
    d(0,3) = 0.0f;
    d(1,3) = 0.0f;
    d(2,3) = 0.0f;
    d(3,3) = 1.0f;

    this->d *= d;
    translate(-eye);
}

inline void Matrix4x4::flipCoordinates()
{
    if (d.mState == Internal::Matrix4x4Data::AFFINE ||
        d.mState == (Internal::Matrix4x4Data::AFFINE | Internal::Matrix4x4Data::TRANS)) {
        d(1,1) = -d(1,1);
        d(2,2) = -d(2,2);
    } else if (d.mState == Internal::Matrix4x4Data::TRANS) {
        d(1,1) = -d(1,1);
        d(2,2) = -d(2,2);
        d.mState |= Internal::Matrix4x4Data::AFFINE;
    } else if (d.mState == Internal::Matrix4x4Data::IDENTITY) {
        d(1,1) = -1.0f;
        d(2,2) = -1.0f;
        d.mState = Internal::Matrix4x4Data::AFFINE;
    } else {
        d(1,0) = -d(1,0);
        d(1,1) = -d(1,1);
        d(1,2) = -d(1,2);
        d(1,3) = -d(1,3);
        d(2,0) = -d(2,0);
        d(2,1) = -d(2,1);
        d(2,2) = -d(2,2);
        d(2,3) = -d(2,3);
        d.mState = Internal::Matrix4x4Data::FULL;
    }
}

inline void Matrix4x4::copyDataTo(real *values) const
{
    for (int row = 0; row < 4; ++row)
        for (int col = 0; col < 4; ++col)
            values[row * 4 + col] = real(d(col,row));
}

//inline Matrix2x2 Matrix4x4::toAffine() const
//{
//    Q_ASSERT(false && "Not implemented yet.");

////    return QMatrix(m[0][0], m[0][1],
////                   m[1][0], m[1][1],
////                   m[3][0], m[3][1]);
//}

//inline Transform3D Matrix4x4::toTransform() const
//{
//    Q_ASSERT(false && "Not implemented yet.");

////    return QTransform(m[0][0], m[0][1], m[0][3],
////                      m[1][0], m[1][1], m[1][3],
////                      m[3][0], m[3][1], m[3][3]);
//}

//inline Transform3D Matrix4x4::toTransform(real distanceToPlane) const
//{
//    Q_UNUSED(distanceToPlane);
//    Q_ASSERT(false && "Not implemented yet.");

////    if (distanceToPlane == 1024.0f) {
////        // Optimize the common case with constants.
////        return QTransform(m[0][0], m[0][1],
////                                m[0][3] - m[0][2] * inv_dist_to_plane,
////                          m[1][0], m[1][1],
////                                m[1][3] - m[1][2] * inv_dist_to_plane,
////                          m[3][0], m[3][1],
////                                m[3][3] - m[3][2] * inv_dist_to_plane);
////    } else if (distanceToPlane != 0.0f) {
////        // The following projection matrix is pre-multiplied with "matrix":
////        //      | 1 0 0 0 |
////        //      | 0 1 0 0 |
////        //      | 0 0 1 0 |
////        //      | 0 0 d 1 |
////        // where d = -1 / distanceToPlane.  After projection, row 3 and
////        // column 3 are dropped to form the final QTransform.
////        qreal d = 1.0f / distanceToPlane;
////        return QTransform(m[0][0], m[0][1], m[0][3] - m[0][2] * d,
////                          m[1][0], m[1][1], m[1][3] - m[1][2] * d,
////                          m[3][0], m[3][1], m[3][3] - m[3][2] * d);
////    } else {
////        // Orthographic projection: drop row 3 and column 3.
////        return QTransform(m[0][0], m[0][1], m[0][3],
////                          m[1][0], m[1][1], m[1][3],
////                          m[3][0], m[3][1], m[3][3]);
////    }
//}

inline QPoint Matrix4x4::map(const QPoint &point) const
{
    return *this * point;
}

inline QPointF Matrix4x4::map(const QPointF &point) const
{
    return *this * point;
}

inline Point2D Matrix4x4::map(const Point2D &point) const
{
    return *this * point;
}

inline Point3D Matrix4x4::map(const Point3D &point) const
{
    return *this * point;
}

inline Point4D Matrix4x4::map(const Point4D &point) const
{
    return *this * point;
}

// TODO: Check this if the operator* implementation changes.
inline Vector3D Matrix4x4::map(const Vector3D &vector) const
{
    return vector * *this;
}

inline QRect Matrix4x4::map(const QRect &rect) const
{
    if (d.mState == (Internal::Matrix4x4Data::TRANS | Internal::Matrix4x4Data::AFFINE) ||
        d.mState == Internal::Matrix4x4Data::AFFINE) {
        qreal x = rect.x() * d(0,0) + d(3,0);
        qreal y = rect.y() * d(1,1) + d(3,1);
        qreal w = rect.width() * d(0,0);
        qreal h = rect.height() * d(1,1);
        if (w < 0) {
            w = -w;
            x -= w;
        }
        if (h < 0) {
            h = -h;
            y -= h;
        }
        return QRect(qRound(x), qRound(y), qRound(w), qRound(h));
    } else if (d.mState == Internal::Matrix4x4Data::TRANS)
        return QRect(qRound(rect.x() + d(3,0)),
                     qRound(rect.y() + d(3,1)),
                     rect.width(), rect.height());

    QPoint tl = map(rect.topLeft());
    QPoint tr = map(QPoint(rect.x() + rect.width(), rect.y()));
    QPoint bl = map(QPoint(rect.x(), rect.y() + rect.height()));
    QPoint br = map(QPoint(rect.x() + rect.width(),
                           rect.y() + rect.height()));

    int xmin = qMin(qMin(tl.x(), tr.x()), qMin(bl.x(), br.x()));
    int xmax = qMax(qMax(tl.x(), tr.x()), qMax(bl.x(), br.x()));
    int ymin = qMin(qMin(tl.y(), tr.y()), qMin(bl.y(), br.y()));
    int ymax = qMax(qMax(tl.y(), tr.y()), qMax(bl.y(), br.y()));

    return QRect(xmin, ymin, xmax - xmin, ymax - ymin);
}

inline QRectF Matrix4x4::map(const QRectF &rect) const
{
    if (d.mState == (Internal::Matrix4x4Data::TRANS | Internal::Matrix4x4Data::AFFINE) ||
        d.mState == Internal::Matrix4x4Data::AFFINE) {
        qreal x = rect.x() * d(0,0) + d(3,0);
        qreal y = rect.y() * d(1,1) + d(3,1);
        qreal w = rect.width() * d(0,0);
        qreal h = rect.height() * d(1,1);
        if (w < 0) {
            w = -w;
            x -= w;
        }
        if (h < 0) {
            h = -h;
            y -= h;
        }
        return QRectF(x, y, w, h);
    } else if (d.mState == Internal::Matrix4x4Data::TRANS)
        return rect.translated(d(3,0), d(3,1));

    QPointF tl = map(rect.topLeft()); QPointF tr = map(rect.topRight());
    QPointF bl = map(rect.bottomLeft()); QPointF br = map(rect.bottomRight());

    qreal xmin = qMin(qMin(tl.x(), tr.x()), qMin(bl.x(), br.x()));
    qreal xmax = qMax(qMax(tl.x(), tr.x()), qMax(bl.x(), br.x()));
    qreal ymin = qMin(qMin(tl.y(), tr.y()), qMin(bl.y(), br.y()));
    qreal ymax = qMax(qMax(tl.y(), tr.y()), qMax(bl.y(), br.y()));

    return QRectF(QPointF(xmin, ymin), QPointF(xmax, ymax));
}

} // namespace Geometry

#endif // GEOMETRY_MATRIX4X4_H
