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

#include "ac_controlview.h"

#include <ac_graphicsscene.h>

#include <ac_model.h>

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
{}

ControlView::~ControlView()
{
    delete d;
}

qreal ControlView::sceneHeight() const
{
    return 1.0 / SceneManager::instance()->model()->viewSettingsIndex().data(Ac::ControlScaleRole).toReal();
}

QPointF ControlView::sceneCenter() const
{
    QModelIndex viewSettings = SceneManager::instance()->model()->viewSettingsIndex();
    return QPointF(viewSettings.data(Ac::TimePositionRole).toReal(), -viewSettings.data(Ac::ControlPositionRole).toReal());
}
