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

#include "ac_pitchview.h"

#include <ac_viewmanager.h>

class PitchViewPrivate
{
public:
    PitchView *q;

    PitchViewPrivate(PitchView *q)
        :   q(q)
    {}

    virtual ~PitchViewPrivate()
    {}
};

PitchView::PitchView(QGraphicsScene *scene, QWidget *parent)
    :   GraphicsHView(scene, parent)
    ,   d(new PitchViewPrivate(this))
{
    setStyleSheet("QFrame {"
                  "border-top: 0px solid palette(shadow);"
                  "border-bottom: 1px solid black;"
                  "border-left: 1px solid palette(shadow);"
                  "border-right: 1px solid palette(shadow);"
                  "}");
}

PitchView::~PitchView()
{
    delete d;
}

qreal PitchView::sceneHeight() const
{
    return 127.0f / ViewManager::instance()->scale(Ac::PitchScaleRole);
}

QPointF PitchView::sceneCenter() const
{
    ViewManager *vm = ViewManager::instance();
    return QPointF(vm->position(Ac::TimePositionRole), -vm->position(Ac::PitchPositionRole));
}
