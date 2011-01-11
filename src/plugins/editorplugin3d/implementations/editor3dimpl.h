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

#ifndef EDITOR3DIMPL_H
#define EDITOR3DIMPL_H

#include <editorplugin3d/interfaces/ieditor3d.h>

namespace Editor3D {

class Editor3DImpl : public Editor3D::IEditor3D
{
    Q_OBJECT

public:
    Editor3DImpl();
    virtual ~Editor3DImpl();

    virtual IViewport3D *currentViewport() const = 0;

    virtual void viewAll();
    virtual void viewFront();
    virtual void viewSide();
    virtual void viewBottom();
    virtual void viewZoom();
    virtual void viewPan();
    virtual void viewRotate();
    virtual void viewParallel();
    virtual void viewPerspective();
    virtual void viewScaleIncreaseX();
    virtual void viewScaleDecreaseX();
    virtual void viewScaleIncreaseZ();
    virtual void viewScaleDecreaseZ();
    virtual void viewTransparencyNone();
    virtual void viewTransparencyScreen();
    virtual void viewTransparencyFull();
};

} // namespace Editor3D

#endif // EDITOR3DIMPL_H
