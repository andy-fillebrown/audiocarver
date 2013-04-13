/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2013 Andrew Fillebrown.
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

#include <QtGlobal>

#if defined(MI_CORE_LIBRARY)
#  define MI_CORE_EXPORT Q_DECL_EXPORT
#else
#  define MI_CORE_EXPORT Q_DECL_IMPORT
#endif

#define qobject_cast qobject_cast

template <typename Container, typename LessThan>
void qSort(Container &c, LessThan lessThan)
{
    qSort(c.begin(), c.end(), lessThan);
}

#define Q_FLOAT_MIN 1E-37
#define Q_FLOAT_MAX 1E+37

template <class T> void qDelete(T *&t)
{
    delete t;
    t = 0;
}

#endif
