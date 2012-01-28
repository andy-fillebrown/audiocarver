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

#include <ac_colordelegate.h>
#include <ac_instrumentdelegate.h>
#include <ac_noteselectionmodel.h>
#include <ac_propertymodel.h>
#include <ac_recordbuttondelegate.h>
#include <ac_trackselectionmodel.h>

#include <QHeaderView>
#include <QKeyEvent>
#include <QScrollBar>
#include <QTableView>

class PropertyViewPrivate
{
public:
    PropertyView *q;
    PropertyModel *propertyModel;
    InstrumentDelegate *instrumentDelegate;
    ColorDelegate *colorDelegate;
    ToggleButtonDelegate *toggleButtonDelegate;
    RecordButtonDelegate *recordButtonDelegate;

    PropertyViewPrivate(PropertyView *q)
        :   q(q)
        ,   propertyModel(new PropertyModel(q))
        ,   instrumentDelegate(new InstrumentDelegate(q))
        ,   colorDelegate(new ColorDelegate(q))
        ,   toggleButtonDelegate(new ToggleButtonDelegate(q))
        ,   recordButtonDelegate(new RecordButtonDelegate(q))
    {
        instrumentDelegate->setCustomColumn(1);
        colorDelegate->setCustomColumn(1);
        toggleButtonDelegate->setCustomColumn(1);
        recordButtonDelegate->setCustomColumn(1);

        toggleButtonDelegate->setButtonColumnWidth(16);
        recordButtonDelegate->setButtonColumnWidth(16);
    }

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
    connect(d->propertyModel, SIGNAL(modelReset()), SLOT(updateDelegates()));

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

void PropertyView::keyReleaseEvent(QKeyEvent *event)
{
    if (Qt::Key_Escape == event->key()) {
        NoteSelectionModel::instance()->clear();
        TrackSelectionModel::instance()->clear();
    }

    QTableView::keyReleaseEvent(event);
}

void PropertyView::updateDelegates()
{
    const int row_count = model()->rowCount();
    for (int i = 0;  i < row_count;  ++i) {
        int role_type = model()->data(model()->index(i, 0), Mi::RoleTypeRole).toInt();
        switch (role_type) {
        case Ac::InstrumentRole:
            setItemDelegateForRow(i, d->instrumentDelegate);
            break;
        case Ac::ColorRole:
            setItemDelegateForRow(i, d->colorDelegate);
            break;
        case Ac::VisibilityRole:
            setItemDelegateForRow(i, d->toggleButtonDelegate);
            break;
        case Ac::RecordingRole:
            setItemDelegateForRow(i, d->recordButtonDelegate);
            break;
        default:
            setItemDelegateForRow(i, 0);
        }
    }
}
