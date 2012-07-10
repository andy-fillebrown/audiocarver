/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2012 Andrew Fillebrown.
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

#ifndef MI_CORE_GLOBAL_H
#define MI_CORE_GLOBAL_H

#include <QDebug>

#include <QtGlobal>

#if defined(MI_CORE_LIBRARY)
#  define MI_CORE_EXPORT Q_DECL_EXPORT
#else
#  define MI_CORE_EXPORT Q_DECL_IMPORT
#endif

inline void mi_assert(const char *assertion, const char *file, int line)
{
    qDebug("ASSERT: \"%s\" in file %s, line %d", assertion, file, line);
    qt_assert(assertion, file, line);
}

#ifdef USE_MI_ASSERT
#  ifdef Q_ASSERT
#    undef Q_ASSERT
#  endif
#  ifndef QT_NO_DEBUG
#    define Q_ASSERT(cond) ((!(cond)) ? mi_assert(#cond,__FILE__,__LINE__) : qt_noop())
#  else
#    define Q_ASSERT(cond) qt_noop()
#  endif
#endif

template <typename Container, typename LessThan>
void qSort(Container &c, LessThan lessThan)
{
    qSort(c.begin(), c.end(), lessThan);
}

#define Q_FLOAT_MIN 1E-37
#define Q_FLOAT_MAX 1E+37

#endif // MI_CORE_GLOBAL_H
