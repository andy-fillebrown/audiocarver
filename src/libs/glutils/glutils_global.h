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

#ifndef GLUTILS_GLOBAL_H
#define GLUTILS_GLOBAL_H

#include <utils/utils_global.h>

#include <gmtl/AxisAngle.h>
#include <gmtl/Generate.h>
#include <gmtl/MatrixOps.h>
#include <gmtl/Plane.h>
#include <gmtl/Point.h>
#include <gmtl/Vec.h>

#include <QtOpenGL/qgl.h>
#include <QtCore/QDebug>
#include <QtCore/qmath.h>

#if defined(GLUTILS_LIB)
#  define GLUTILS_EXPORT Q_DECL_EXPORT
#else
#  define GLUTILS_EXPORT Q_DECL_IMPORT
#endif

#define Q_CHECK_GLERROR \
{ \
    GLenum e = glGetError(); \
    if (e != GL_NO_ERROR) \
        qDebug() << qPrintable( \
                QString("GL error in \'%1\'\n%2(%3): %4") \
                    .arg(Q_FUNC_INFO) \
                    .arg(__FILE__) \
                    .arg(__LINE__) \
                    .arg(GL::errorString(e)) \
            ); \
    Q_ASSERT(e == GL_NO_ERROR); \
}

namespace GL {

typedef quint16 index;
typedef float real;

typedef gmtl::AxisAngle<real> AxisAngle;
typedef gmtl::Matrix<real, 4, 4> Matrix;
typedef gmtl::Point<real, 3> Point;
typedef gmtl::Vec<real, 3> Vector;

typedef gmtl::LineSeg<real> LineSegment;
typedef gmtl::Plane<real> Plane;
typedef gmtl::Ray<real> Ray;

namespace Constants {

const Vector axisX(1.0f, 0.0f, 0.0f);
const Vector axisY(0.0f, 1.0f, 0.0f);
const Vector axisZ(0.0f, 0.0f, 1.0f);

const Plane planeXY(axisZ, 0.0f);
const Plane planeXZ(axisY, 0.0f);
const Plane planeYZ(axisX, 0.0f);

} // namespace Constants

inline void ortho(Matrix &m, real left, real right, real bottom, real top, real nearPlane, real farPlane)
{
    // Early out if projection volume is zero-sized.
    if (left == right || bottom == top || nearPlane == farPlane)
        return;

    qreal width = right - left;
    qreal invheight = top - bottom;
    qreal clip = farPlane - nearPlane;

    real *d = m.mData;
    d[ 0] = 2.0f / width;
    d[ 4] = 0.0f;
    d[ 8] = 0.0f;
    d[12] = -(left + right) / width;
    d[ 1] = 0.0f;
    d[ 5] = 2.0f / invheight;
    d[ 9] = 0.0f;
    d[13] = -(top + bottom) / invheight;
    d[ 2] = 0.0f;
    d[ 6] = 0.0f;
    d[10] = -2.0f / clip;
    d[14] = -(nearPlane + farPlane) / clip;
    d[ 3] = 0.0f;
    d[ 7] = 0.0f;
    d[11] = 0.0f;
    d[15] = 1.0f;
}

inline void frustum(Matrix &m, real left, real right, real bottom, real top, real nearPlane, real farPlane)
{
    // Early out if projection volume is zero-sized.
    if (left == right || bottom == top || nearPlane == farPlane)
        return;

    qreal width = right - left;
    qreal invheight = top - bottom;
    qreal clip = farPlane - nearPlane;

    real *d = m.mData;
    d[ 0] = 2.0f * nearPlane / width;
    d[ 4] = 0.0f;
    d[ 8] = (left + right) / width;
    d[12] = 0.0f;
    d[ 1] = 0.0f;
    d[ 5] = 2.0f * nearPlane / invheight;
    d[ 9] = (top + bottom) / invheight;
    d[13] = 0.0f;
    d[ 2] = 0.0f;
    d[ 6] = 0.0f;
    d[10] = -(nearPlane + farPlane) / clip;
    d[14] = -2.0f * nearPlane * farPlane / clip;
    d[ 3] = 0.0f;
    d[ 7] = 0.0f;
    d[11] = -1.0f;
    d[15] = 0.0f;
}

inline void perspective(Matrix &m, real fov, real aspect, real nearPlane, real farPlane)
{
    // Early out if projection volume is zero-sized.
    if (nearPlane == farPlane || aspect == 0.0f)
        return;

    real radians = (fov / 2.0f) * M_PI / 180.0f;
    real sine = qSin(radians);
    if (sine == 0.0f)
        return;
    real cotan = qCos(radians) / sine;
    real clip = farPlane - nearPlane;

    real *d = m.mData;
    d[ 0] = cotan / aspect;
    d[ 4] = 0.0f;
    d[ 8] = 0.0f;
    d[12] = 0.0f;
    d[ 1] = 0.0f;
    d[ 5] = cotan;
    d[ 9] = 0.0f;
    d[13] = 0.0f;
    d[ 2] = 0.0f;
    d[ 6] = 0.0f;
    d[10] = -(nearPlane + farPlane) / clip;
    d[14] = -(2.0f * nearPlane * farPlane) / clip;
    d[ 3] = 0.0f;
    d[ 7] = 0.0f;
    d[11] = -1.0f;
    d[15] = 0.0f;
}

inline void lookAt(Matrix &m, const Point &eye, const Point &target, const Vector &upVec)
{
    Vector fwd = target - eye;
    gmtl::normalize(fwd);

    Vector side;
    gmtl::cross(side, fwd, upVec);
    gmtl::normalize(side);

    Vector up;
    gmtl::cross(up, side, fwd);

    real *d = m.mData;
    d[ 0] = side[0];
    d[ 4] = side[1];
    d[ 8] = side[2];
    d[12] = 0.0f;
    d[ 1] = up[0];
    d[ 5] = up[1];
    d[ 9] = up[2];
    d[13] = 0.0f;
    d[ 2] = -fwd[0];
    d[ 6] = -fwd[1];
    d[10] = -fwd[2];
    d[14] = 0.0f;
    d[ 3] = 0.0f;
    d[ 7] = 0.0f;
    d[11] = 0.0f;
    d[15] = 1.0f;

    Matrix trans;
    gmtl::setTrans(trans, -eye);
    m *= trans;
}

inline const char *errorString(GLenum errorCode)
{
    switch (errorCode) {
    case GL_INVALID_ENUM: return "invalid enum";
    case GL_INVALID_VALUE: return "invalid value";
    case GL_INVALID_OPERATION: return "invalid operation";
    case GL_STACK_OVERFLOW: return "stack overflow";
    case GL_OUT_OF_MEMORY: return "out of memory";
    default: return "unknown error";
    }
}

inline void pushState()
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    Q_CHECK_GLERROR;
}

inline void popState()
{
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glPopAttrib();

    Q_CHECK_GLERROR;
}


template <typename T>
inline void traceMatrix(T *m)
{
    qDebug() << QString("%1, %2, %3, %4").arg(m[ 0]).arg(m[ 1]).arg(m[ 2]).arg(m[ 3]);
    qDebug() << QString("%1, %2, %3, %4").arg(m[ 4]).arg(m[ 5]).arg(m[ 6]).arg(m[ 7]);
    qDebug() << QString("%1, %2, %3, %4").arg(m[ 8]).arg(m[ 9]).arg(m[10]).arg(m[11]);
    qDebug() << QString("%1, %2, %3, %4").arg(m[12]).arg(m[13]).arg(m[14]).arg(m[15]);
}

inline void traceModelViewMatrix()
{
    GL::real m[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, m);

    qDebug() << "";
    qDebug() << "gl model view:";
    traceMatrix(m);
}

inline void traceProjectionMatrix()
{
    GL::real m[16];
    glGetFloatv(GL_PROJECTION_MATRIX, m);

    qDebug() << "";
    qDebug() << "gl projection:";
    traceMatrix(m);
}

inline void traceViewport()
{
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);

    qDebug() << "";
    qDebug() << "gl viewport:";
    qDebug() << QString("%1, %2, %3 %4")
                .arg(viewport[0])
                .arg(viewport[1])
                .arg(viewport[2])
                .arg(viewport[3]);
}

inline void traceTransformations()
{
    qDebug() << "";
    traceModelViewMatrix();
    traceProjectionMatrix();
    traceViewport();
    qDebug() << "";
}

} // namespace GL

#endif // GLUTILS_GLOBAL_H
