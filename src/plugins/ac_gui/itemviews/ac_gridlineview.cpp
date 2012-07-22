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

#include <mi_imodel.h>
#include <mi_imodelitem.h>

#include <ac_colordelegate.h>
#include <ac_gridlinemodel.h>
#include <ac_gui_namespace.h>
#include <ac_lengthdelegate.h>

#include <QHeaderView>

using namespace Ac::Core;

GridLineView::GridLineView(QWidget *parent)
    :   QTableView(parent)
{
    setSelectionBehavior(SelectRows);
    horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);

    LengthDelegate *position_delegate = new LengthDelegate(this);
    position_delegate->setCustomColumn(0);
    setItemDelegateForColumn(0, position_delegate);

    ColorDelegate *color_delegate = new ColorDelegate(this);
    color_delegate->setCustomColumn(3);
    setItemDelegateForColumn(3, color_delegate);
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
