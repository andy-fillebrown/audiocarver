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

#ifndef AC_GUI_PITCHLABELVIEW_H
#define AC_GUI_PITCHLABELVIEW_H

#include "ac_gui_labelview.h"
#include "ac_gui_namespace.h"

class PitchLabelViewPrivate;
class PitchLabelView : public LabelVView
{
    Q_OBJECT

    PitchLabelViewPrivate *d;

public:
    PitchLabelView(QGraphicsScene *scene = 0, QWidget *parent = 0);
    ~PitchLabelView();

protected:
    IModelItem *gridLineList() const;

    int sceneType() const { return Ac::PitchLabelScene; }
    qreal sceneHeight() const;

    int positionRoleY() const { return Ac::PitchPositionRole; }
    int scaleRoleY() const { return Ac::PitchScaleRole; }
};

#endif
