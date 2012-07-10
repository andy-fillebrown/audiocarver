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

#ifndef AC_COREGLOBAL_H
#define AC_COREGLOBAL_H

#include <mi_coreglobal.h>

#if defined(AC_CORE_LIBRARY)
#  define AC_CORE_EXPORT Q_DECL_EXPORT
#else
#  define AC_CORE_EXPORT Q_DECL_IMPORT
#endif

#endif // AC_COREGLOBAL_H
