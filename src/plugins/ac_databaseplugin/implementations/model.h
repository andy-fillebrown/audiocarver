/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2010 Andrew Fillebrown.
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

#ifndef AC_MODEL_H
#define AC_MODEL_H

#include <gldatabaseplugin/interfaces/iglmodel.h>

namespace AudioCarver {
namespace Internal {

class ModelImpl : public GLDatabase::IGLModel
{
public:
    ModelImpl();
    virtual ~ModelImpl();

    virtual void drawStaticGL(const QRectF &frustum);
    virtual void drawTransientGL(const QRectF &frustum);
    virtual void drawAnimatedGL(const QRectF &frustum, qreal timeDelta);
};

} // namespace Internal
} // namespace AudioCarver

#endif // AC_MODEL_H
