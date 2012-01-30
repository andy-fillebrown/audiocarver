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

#include "ac_gridlineview.h"

#include <ac_gridlinemodel.h>

#include <ac_namespace.h>

#include <mi_imodel.h>
#include <mi_imodelitem.h>

#include <QHeaderView>

GridLineView::GridLineView(QWidget *parent)
    :   QTableView(parent)
{
    horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
}

TimeLineView::TimeLineView(QWidget *parent)
    :   GridLineView(parent)
{
    GridLineModel *m = new GridLineModel(this);
    m->setGridLineType(Ac::TimeGridLineItem);
    setModel(m);
}

PitchLineView::PitchLineView(QWidget *parent)
    :   GridLineView(parent)
{
    GridLineModel *m = new GridLineModel(this);
    m->setGridLineType(Ac::PitchGridLineItem);
    setModel(m);
}

ControlLineView::ControlLineView(QWidget *parent)
    :   GridLineView(parent)
{
    GridLineModel *m = new GridLineModel(this);
    m->setGridLineType(Ac::ControlGridLineItem);
    setModel(m);
}
