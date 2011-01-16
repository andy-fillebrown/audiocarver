/**************************************************************************
**
** This file is part of Qt Creator
**
** Copyright (c) 2010 Nokia Corporation and/or its subsidiary(-ies).
**
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** Commercial Usage
**
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
**
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at http://qt.nokia.com/contact.
**
**************************************************************************/

#ifndef UTILS3D_GLOBAL_H
#define UTILS3D_GLOBAL_H

#include <utils/utils_global.h>

#include <QtCore/QDebug>

#include <QtOpenGL/qgl.h>

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

#endif // UTILS3D_GLOBAL_H
