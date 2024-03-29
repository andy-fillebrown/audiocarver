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

#include "ac_gui_propertyview.h"
#include <QHeaderView>
#include <QKeyEvent>
#include <QScrollBar>
#include <QTableView>

using namespace Qt;

PropertyView::PropertyView(QWidget *parent)
    :   QTableView(parent)
{
    setHorizontalScrollBarPolicy(ScrollBarAlwaysOff);
    QHeaderView *v_header = verticalHeader();
    v_header->setDefaultSectionSize(v_header->minimumSectionSize());
    v_header->hide();
    QHeaderView *h_header = horizontalHeader();
    h_header->setSectionsClickable(false);
    h_header->setDefaultAlignment(AlignLeft);
    h_header->setHighlightSections(false);
    h_header->setStretchLastSection(true);
    h_header->resizeSections(QHeaderView::ResizeToContents);
}

void PropertyView::resizeEvent(QResizeEvent *event)
{
    const QAbstractItemModel *m = model();
    const QModelIndex root_index = rootIndex();

    // Get the row height (assuming all rows are the same height).
    const int row_h = rowHeight(0);

    // Update the vertical scrollbar range.
    const QWidget *vport = viewport();
    if (row_h)
        verticalScrollBar()->setRange(0, (((m->rowCount(root_index) + 1) * row_h) - vport->height()) / row_h);

    QTableView::resizeEvent(event);
}
