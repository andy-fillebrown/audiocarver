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

#include "ac_editor3dimpl.h"

using namespace AudioCarver;
using namespace AudioCarver::Internal;

Editor3DImpl::Editor3DImpl()
    :   _viewport(0)
{
}

Editor3DImpl::~Editor3DImpl()
{
    _viewport = 0;
}

Editor3D::IViewport3D *Editor3DImpl::currentViewport() const
{
    return _viewport;
}

void Editor3DImpl::setCurrentViewport(Editor3D::IViewport3D *viewport)
{
    _viewport = viewport;
}

void Editor3DImpl::viewAll()
{
    qDebug() << Q_FUNC_INFO;
}

void Editor3DImpl::viewFront()
{
    qDebug() << Q_FUNC_INFO;
}

void Editor3DImpl::viewSide()
{
    qDebug() << Q_FUNC_INFO;
}

void Editor3DImpl::viewBottom()
{
    qDebug() << Q_FUNC_INFO;
}

void Editor3DImpl::viewZoom()
{
    qDebug() << Q_FUNC_INFO;
}

void Editor3DImpl::viewPan()
{
    qDebug() << Q_FUNC_INFO;
}

void Editor3DImpl::viewRotate()
{
    qDebug() << Q_FUNC_INFO;
}

void Editor3DImpl::viewParallel()
{
    qDebug() << Q_FUNC_INFO;
}

void Editor3DImpl::viewPerspective()
{
    qDebug() << Q_FUNC_INFO;
}

void Editor3DImpl::viewScaleIncreaseX()
{
    qDebug() << Q_FUNC_INFO;
}

void Editor3DImpl::viewScaleDecreaseX()
{
    qDebug() << Q_FUNC_INFO;
}

void Editor3DImpl::viewScaleIncreaseZ()
{
    qDebug() << Q_FUNC_INFO;
}

void Editor3DImpl::viewScaleDecreaseZ()
{
    qDebug() << Q_FUNC_INFO;
}

void Editor3DImpl::viewTransparencyNone()
{
    qDebug() << Q_FUNC_INFO;
}

void Editor3DImpl::viewTransparencyScreen()
{
    qDebug() << Q_FUNC_INFO;
}

void Editor3DImpl::viewTransparencyFull()
{
    qDebug() << Q_FUNC_INFO;
}
