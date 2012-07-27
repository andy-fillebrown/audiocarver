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

#include "ac_gui_pitchlabelview.h"

#include <ac_gui_viewmanager.h>

#include <mi_idatabase.h>
#include <mi_imodel.h>
#include <mi_imodelitem.h>

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
{
    setStyleSheet("QFrame {"
                  "border-top: 0px solid palette(shadow);"
                  "border-bottom: 1px solid palette(shadow);"
                  "border-left: 0px solid palette(shadow);"
                  "border-right: 1px solid palette(shadow);"
                  "}");
}

PitchLabelView::~PitchLabelView()
{
    delete d;
}

IModelList *PitchLabelView::gridLineList() const
{
    return query<IModel>(IDatabase::instance())->rootItem()->findList(Ac::PitchGridLineItem);
}

qreal PitchLabelView::sceneHeight() const
{
    return qreal(127.0f) / ViewManager::instance()->scale(Ac::PitchScaleRole);
}