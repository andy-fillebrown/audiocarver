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

#ifndef IGLEDITOR_H
#define IGLEDITOR_H

#include <gleditorplugin/gleditor_global.h>

#include <QtCore/QObject>

namespace GLEditor {

class GLEDITOR_EXPORT IGLEditor : public QObject
{
    Q_OBJECT

public:
    IGLEditor();
    virtual ~IGLEditor();

    virtual void viewAll() = 0;
    virtual void viewFront() = 0;
    virtual void viewSide() = 0;
    virtual void viewBottom() = 0;
    virtual void viewZoom() = 0;
    virtual void viewPan() = 0;
    virtual void viewRotate() = 0;
    virtual void viewParallel() = 0;
    virtual void viewPerspective() = 0;
    virtual void viewScaleIncreaseX() = 0;
    virtual void viewScaleDecreaseX() = 0;
    virtual void viewScaleIncreaseZ() = 0;
    virtual void viewScaleDecreaseZ() = 0;
    virtual void viewTransparencyNone() = 0;
    virtual void viewTransparencyScreen() = 0;
    virtual void viewTransparencyFull() = 0;

    virtual void windowSplitHorizontal() = 0;
    virtual void windowSplitVertical() = 0;
    virtual void windowRemoveCurrentSplit() = 0;
    virtual void windowRemoveAllSplits() = 0;
};

} // namespace GLEditor

#endif // IGLEDITOR_H
