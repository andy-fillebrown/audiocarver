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

#ifndef GEOMETRY_GLOBAL_H
#define GEOMETRY_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(GEOMETRY_LIB)
#  define GEOMETRY_EXPORT Q_DECL_EXPORT
#else
#  define GEOMETRY_EXPORT Q_DECL_IMPORT
#endif

namespace Geometry {

typedef float real;

const real TOLERANCE = 0.0009;

} // namespace Geometry

#endif // GEOMETRY_GLOBAL_H
