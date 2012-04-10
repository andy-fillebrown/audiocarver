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

#define Q_TD(Class) Class##Private<T> *const d = d_func()
#define Q_TQ(Class) Class<T> *const q = q_func()

#define Q_DECLARE_BASE_AGGREGATE(AggregateClass, AggregatorClass) \
    protected: \
        AggregatorClass *_a; \
        AggregatorClass *a() const { return _a; } \
        IAggregator *aggregator() const { return _a; } \
    public: \
        AggregateClass(AggregatorClass *aggregator) : _a(aggregator) {} \
        virtual IAggregate* _init();

#define Q_DECLARE_AGGREGATE(AggregateClass, AggregatorClass) \
        typedef AggregatorClass::Base::AggregateClass Base; \
    protected: \
        AggregateClass(AggregatorClass *aggregator) : AggregateClass::Base::AggregateClass(aggregator) {} \
        AggregatorClass *a() const { return cast<AggregatorClass>(_a); } \
    public: \
        IAggregate* _init();

#define Q_CREATE(Class) (new Class)->_init()
#define Q_CREATE_AGGREGATE(Class) Q_CREATE(Class(this))

#define Q_A(AggregatorClass) AggregatorClass *a = cast<AggregatorClass>(_a)

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

#ifdef Q_MI_NO_REINTERPRET_CAST
#   define mi_cast static_cast
#else
#   define mi_cast reinterpret_cast
#endif

template <typename T, typename Object>
T *cast(Object *object)
{
    return mi_cast<T*>(object);
}

template <typename T, typename Object>
const T *cast(const Object *object)
{
    return mi_cast<const T*>(object);
}

#define bitcountof(x) (8 * sizeof(x))

#define Q_FLOAT_MIN 1E-37
#define Q_FLOAT_MAX 1E+37

#endif // MI_GLOBAL_H
