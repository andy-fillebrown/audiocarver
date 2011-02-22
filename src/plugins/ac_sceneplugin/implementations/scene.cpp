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

#include "scene.h"

using namespace AudioCarver;
using namespace AudioCarver::Internal;

SceneImpl::SceneImpl()
{
}

SceneImpl::~SceneImpl()
{
}

void SceneImpl::drawStaticGL(const QRectF &frustum)
{
    Q_UNUSED(frustum);
}

void SceneImpl::drawModelGL(const QRectF &frustum)
{
    Q_UNUSED(frustum);
}

void SceneImpl::drawDelegateGL(const QRectF &frustum)
{
    Q_UNUSED(frustum);
}

void SceneImpl::drawAnimationGL(const QRectF &frustum, qreal timeDelta)
{
    Q_UNUSED(frustum);
    Q_UNUSED(timeDelta);
}
