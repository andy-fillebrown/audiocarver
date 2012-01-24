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

#include "ac_propertyview.h"

#include <ac_noteselectionmodel.h>
#include <ac_propertymodel.h>
#include <ac_trackselectionmodel.h>

#include <QHeaderView>
#include <QScrollBar>
#include <QTableView>

class PropertyViewPrivate
{
public:
    PropertyView *q;
    PropertyModel *propertyModel;

    PropertyViewPrivate(PropertyView *q)
        :   q(q)
        ,   propertyModel(new PropertyModel(q))
    {}

    void init()
    {
        propertyModel->appendSelectionModel(TrackSelectionModel::instance());
        propertyModel->appendSelectionModel(NoteSelectionModel::instance());
    }
};

PropertyView::PropertyView(QWidget *parent)
    :   QTableView(parent)
    ,   d(new PropertyViewPrivate(this))
{
    d->init();
    setModel(d->propertyModel);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QHeaderView *v_header = verticalHeader();
    v_header->setDefaultSectionSize(v_header->minimumSectionSize());
    v_header->hideSection(0);
    v_header->hide();

    QHeaderView *h_header = horizontalHeader();
    h_header->setClickable(false);
    h_header->setDefaultAlignment(Qt::AlignLeft);
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
