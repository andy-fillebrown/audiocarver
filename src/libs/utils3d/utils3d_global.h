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

#ifndef UTILS3D_GLOBAL_H
#define UTILS3D_GLOBAL_H

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

#if defined(UTILS3D_LIB)
#  define UTILS3D_EXPORT Q_DECL_EXPORT
#else
#  define UTILS3D_EXPORT Q_DECL_IMPORT
#endif

#define Q_CHECK_GLERROR \
{ \
    GLenum e = glGetError(); \
    if (e != GL_NO_ERROR) \
        qDebug() << qPrintable( \
                QString("GL error in member function \'%1\'\n%2(%3): %4") \
                    .arg(Q_FUNC_INFO) \
                    .arg(__FILE__) \
                    .arg(__LINE__) \
                    .arg(qglErrorString(e)) \
            ); \
    Q_ASSERT(e == GL_NO_ERROR); \
}

namespace GL {

typedef float real;

typedef gmtl::AxisAngle<real> AxisAngle;
typedef gmtl::Matrix<real, 4, 4> Matrix;
typedef gmtl::Point<real, 3> Point;
typedef gmtl::Vec<real, 3> Vector;

typedef gmtl::LineSeg<real> LineSegment;
typedef gmtl::Plane<real> Plane;
typedef gmtl::Ray<real> Ray;

const Vector xAxis(1.0f, 0.0f, 0.0f);
const Vector yAxis(0.0f, 1.0f, 0.0f);
const Vector zAxis(0.0f, 0.0f, 1.0f);

const Plane xyPlane(zAxis, 0.0f);
const Plane xzPlane(yAxis, 0.0f);
const Plane yzPlane(xAxis, 0.0f);

inline void perspective(Matrix &m, real fov, real aspect, real nearPlane, real farPlane)
{
    gmtl::identity(m);

    // Bail out if the projection volume is zero-sized.
    if (nearPlane == farPlane || aspect == 0.0f)
        return;

    // Construct the projection.
    real radians = (fov / 2.0f) * M_PI / 180.0f;
    real sine = qSin(radians);
    if (sine == 0.0f)
        return;
    real cotan = qCos(radians) / sine;
    real clip = farPlane - nearPlane;
    m(0,0) = cotan / aspect;
    m(0,1) = 0.0f;
    m(0,2) = 0.0f;
    m(0,3) = 0.0f;
    m(1,0) = 0.0f;
    m(1,1) = cotan;
    m(1,2) = 0.0f;
    m(1,3) = 0.0f;
    m(2,0) = 0.0f;
    m(2,1) = 0.0f;
    m(2,2) = -(nearPlane + farPlane) / clip;
    m(2,3) = -(2.0f * nearPlane * farPlane) / clip;
    m(3,0) = 0.0f;
    m(3,1) = 0.0f;
    m(3,2) = -1.0f;
    m(3,3) = 0.0f;
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

    m(0,0) = side[0];
    m(0,1) = side[1];
    m(0,2) = side[2];
    m(0,3) = 0.0f;
    m(1,0) = up[0];
    m(1,1) = up[1];
    m(1,2) = up[2];
    m(1,3) = 0.0f;
    m(2,0) = -fwd[0];
    m(2,1) = -fwd[1];
    m(2,2) = -fwd[2];
    m(2,3) = 0.0f;
    m(3,0) = 0.0f;
    m(3,1) = 0.0f;
    m(3,2) = 0.0f;
    m(3,3) = 1.0f;

    Matrix trans;
    gmtl::setTrans(trans, -eye);

    m *= trans;
}

} // namespace GL

inline const char *qglErrorString(GLenum errorCode)
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

inline void qglPushState()
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    Q_CHECK_GLERROR;
}

inline void qglPopState()
{
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glPopAttrib();

    Q_CHECK_GLERROR;
}


template <typename T>
inline void qglTraceMatrix(T *m)
{
    qDebug() << QString("%1, %2, %3, %4").arg(m[0]).arg(m[1]).arg(m[2]).arg(m[3]);
    qDebug() << QString("%1, %2, %3, %4").arg(m[4]).arg(m[5]).arg(m[6]).arg(m[7]);
    qDebug() << QString("%1, %2, %3, %4").arg(m[8]).arg(m[9]).arg(m[10]).arg(m[11]);
    qDebug() << QString("%1, %2, %3, %4").arg(m[12]).arg(m[13]).arg(m[14]).arg(m[15]);
}

inline void qglTraceModelViewMatrix()
{
    GL::real m[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, m);

    qDebug() << "";
    qDebug() << "gl model view:";
    qglTraceMatrix(m);
}

inline void qglTraceProjectionMatrix()
{
    GL::real m[16];
    glGetFloatv(GL_PROJECTION_MATRIX, m);

    qDebug() << "";
    qDebug() << "gl projection:";
    qglTraceMatrix(m);
}

inline void qglTraceViewport()
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

inline void qglTraceTransformations()
{
    qDebug() << "";
    qglTraceModelViewMatrix();
    qglTraceProjectionMatrix();
    qglTraceViewport();
    qDebug() << "";
}

#endif // UTILS3D_GLOBAL_H
