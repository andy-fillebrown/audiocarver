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

#ifndef AC_GUIDEFS_H
#define AC_GUIDEFS_H

#include <mi_coredefs.h>

// ISUBENTITY

#define Q_ISUBENTITY(ClassIsCurve, ClassSceneType) \
    Q_IAGGREGATE_BASE(SubEntity) \
    \
        IParentEntity *parentEntity() const \
        { \
            return query<IParentEntity>(a()->parent()); \
        } \
    \
        bool isCurve() const \
        { \
            return ClassIsCurve; \
        } \
    \
        int sceneType() const \
        { \
            return ClassSceneType; \
        }

#endif // AC_GUIDEFS_H
