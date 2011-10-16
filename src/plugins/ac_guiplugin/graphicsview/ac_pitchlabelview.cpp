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

#include "ac_pitchlabelview.h"

#include <ac_viewmanager.h>

#include <ac_model.h>

class PitchLabelViewPrivate
{
public:
    PitchLabelViewPrivate()
    {}

    virtual ~PitchLabelViewPrivate()
    {}
};

PitchLabelView::PitchLabelView(QGraphicsScene *scene, QWidget *parent)
    :   LabelVView(scene, parent)
    ,   d(new PitchLabelViewPrivate)
{}

PitchLabelView::~PitchLabelView()
{
    delete d;
}

QModelIndex PitchLabelView::gridLineListIndex() const
{
    return ViewManager::instance()->model()->pitchGridLineListIndex();
}

qreal PitchLabelView::sceneHeight() const
{
    return 127.0 / ViewManager::instance()->scale(Ac::PitchScaleRole);
}

QPointF PitchLabelView::sceneCenter() const
{
    return QPointF(0.5f, -ViewManager::instance()->position(Ac::PitchPositionRole));
}

QPointF PitchLabelView::sceneOffset() const
{
    return QPointF(0.0f, 10.0f / (height() / sceneHeight()));
}
