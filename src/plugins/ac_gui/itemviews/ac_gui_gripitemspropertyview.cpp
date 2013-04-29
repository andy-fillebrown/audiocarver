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

#include "ac_gui_gripitemspropertyview.h"
#include "ac_gui_doubledelegate.h"
#include "ac_gui_gripselectionmodel.h"
#include "ac_gui_togglebuttondelegate.h"
#include <QHeaderView>

class GripItemsPropertyViewPrivate
{
public:
    GripItemsPropertyView *q;
    GripSelectionModel *gripItemsPropertyModel;
    DoubleDelegate *timeDelegate;
    DoubleDelegate *valueDelegate;
    ToggleButtonDelegate *curveButtonDelegate;
    QList<int> minColumnWidths;
    uint isResizing : 1;

    GripItemsPropertyViewPrivate(GripItemsPropertyView *q)
        :   q(q)
        ,   gripItemsPropertyModel(new GripSelectionModel(q))
        ,   timeDelegate(new DoubleDelegate(q))
        ,   valueDelegate(new DoubleDelegate(q))
        ,   curveButtonDelegate(new ToggleButtonDelegate(q))
        ,   isResizing(false)
    {
        timeDelegate->setCustomColumn(2);
        valueDelegate->setCustomColumn(3);
        curveButtonDelegate->setCustomColumn(4);
        curveButtonDelegate->setButtonColumnWidth(16);
    }
};

GripItemsPropertyView::GripItemsPropertyView(QWidget *parent)
    :   PropertyView(parent)
    ,   d(new GripItemsPropertyViewPrivate(this))
{
    setModel(d->gripItemsPropertyModel);
    connect(model(), SIGNAL(layoutChanged()), SLOT(updateColumnWidths()));
    setItemDelegateForColumn(2, d->timeDelegate);
    setItemDelegateForColumn(3, d->valueDelegate);
    setItemDelegateForColumn(4, d->curveButtonDelegate);
    QHeaderView *h_header = horizontalHeader();
    h_header->hideSection(0);
    connect(h_header, SIGNAL(sectionResized(int,int,int)), SLOT(updateMinimumColumnWidth(int,int,int)));
    for (int i = 0;  i < model()->columnCount();  ++i)
        d->minColumnWidths.append(-1);
}

GripItemsPropertyView::~GripItemsPropertyView()
{
    delete d;
}

void GripItemsPropertyView::updateColumnWidths()
{
    d->isResizing = true;
    for (int i = 1;  i < model()->columnCount() - 1;  ++i) {
        resizeColumnToContents(i);
        if (columnWidth(i) < d->minColumnWidths.at(i))
            setColumnWidth(i, d->minColumnWidths.at(i));
        else
            d->minColumnWidths[i] = columnWidth(i);
    }

    // The last column is not automatically resizing correctly.
    // Set the last column's width to zero to make it resize correctly.
    setColumnWidth(model()->columnCount() - 1, 0);

    // Keep the view from shifting to the left.
    horizontalHeader()->setOffset(0);

    d->isResizing = false;
}

void GripItemsPropertyView::updateMinimumColumnWidth(int column, int oldWidth, int width)
{
    if (d->isResizing)
        return;
    d->minColumnWidths[column] = width;
}
