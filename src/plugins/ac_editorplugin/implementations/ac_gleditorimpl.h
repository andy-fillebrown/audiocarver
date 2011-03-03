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

#ifndef AC_GLEDITORIMPL_H
#define AC_GLEDITORIMPL_H

#include <gleditorplugin/interfaces/igleditor.h>

namespace AudioCarver {
namespace Internal {
class GLEditorImplPrivate;

class GLEditorImpl : public GLEditor::IGLEditor
{
    Q_OBJECT

public:
    GLEditorImpl();
    virtual ~GLEditorImpl();

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

    virtual void windowSplitHorizontal();
    virtual void windowSplitVertical();
    virtual void windowRemoveCurrentSplit();
    virtual void windowRemoveAllSplits();
};

} // namespace Internal
} // namespace AudioCarver

#endif // AC_GLEDITORIMPL_H
