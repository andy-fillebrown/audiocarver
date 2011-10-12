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

#include "ac_controllabelview.h"

#include <ac_graphicsscene.h>

#include <ac_model.h>

class ControlLabelViewPrivate
{
public:
    ControlLabelViewPrivate()
    {}

    virtual ~ControlLabelViewPrivate()
    {}
};

ControlLabelView::ControlLabelView(QGraphicsScene *scene, QWidget *parent)
    :   GraphicsView(scene, parent)
    ,   d(new ControlLabelViewPrivate)
{}

ControlLabelView::~ControlLabelView()
{
    delete d;
}

QPointF ControlLabelView::sceneCenter() const
{
    Model *model = SceneManager::instance()->model();
    QModelIndex viewSettings = model->viewSettingsIndex();
    qreal y = viewSettings.data(Ac::TimePositionRole).toReal();
    return QPointF(0.5f, -y);
}
