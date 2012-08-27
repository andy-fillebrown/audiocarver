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

#include "ac_gui_controlview.h"
#include "ac_gui_graphicsviewmanager.h"

using namespace Ac;

class ControlViewPrivate
{
public:
    ControlViewPrivate()
    {}

    virtual ~ControlViewPrivate()
    {}
};

ControlView::ControlView(QGraphicsScene *scene, QWidget *parent)
    :   GraphicsHView(scene, parent)
    ,   d(new ControlViewPrivate)
{
    setStyleSheet("QFrame {"
                  "border-top: 1px solid palette(shadow);"
                  "border-bottom: 1px solid palette(shadow);"
                  "border-left: 1px solid palette(shadow);"
                  "border-right: 1px solid palette(shadow);"
                  "}");
}

ControlView::~ControlView()
{
    delete d;
}

qreal ControlView::sceneHeight() const
{
    return qreal(1.0f) / GraphicsViewManager::instance()->scale(Ac::ControlScaleRole);
}

QPointF ControlView::sceneCenter() const
{
    GraphicsViewManager *vm = GraphicsViewManager::instance();
    return QPointF(vm->position(TimePositionRole), -vm->position(ControlPositionRole));
}
