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

#ifndef MI_GLOBAL_H
#define MI_GLOBAL_H

#include <qglobal.h>
#include <QDebug>

#if defined(MI_CORE_LIBRARY)
#  define MI_CORE_EXPORT Q_DECL_EXPORT
#else
#  define MI_CORE_EXPORT Q_DECL_IMPORT
#endif

#if defined(MI_GUI_LIBRARY)
#  define MI_GUI_EXPORT Q_DECL_EXPORT
#else
#  define MI_GUI_EXPORT Q_DECL_IMPORT
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

#define Q_DECLARE_PRIVATE_TEMPLATE(Class) \
    inline Class##Private<T> *d_func() { return reinterpret_cast<Class##Private<T>*>(qGetPtrHelper(d_ptr)); } \
    inline const Class##Private<T> *d_func() const { return reinterpret_cast<const Class##Private<T>*>(qGetPtrHelper(d_ptr)); } \
    friend class Class##Private<T>;

#define Q_DECLARE_PUBLIC_TEMPLATE(Class) \
    inline Class<T> *q_func() { return static_cast<Class<T>*>(this->q_ptr); } \
    inline const Class<T> *q_func() const { return static_cast<const Class<T>*>(this->q_ptr); } \
    friend class Class<T>;

#define Q_D_T(Class) Class##Private<T> *const d = d_func()
#define Q_Q_T(Class) Class<T> *const q = q_func()

template <typename Container, typename LessThan>
void qSort(Container &c, LessThan lessThan)
{
    qSort(c.begin(), c.end(), lessThan);
}

template <typename T, typename Object>
T *object_cast(Object *object)
{
    return qobject_cast<T*>(object);
}

template <typename T, typename Object>
T *object_cast(const Object *object)
{
    return qobject_cast<T*>(object);
}

#define bitsizeof(x) (8 * sizeof(x))

#define Q_FLOAT_MIN 1E-37
#define Q_FLOAT_MAX 1E+37

#endif // MI_GLOBAL_H
