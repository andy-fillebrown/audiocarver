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

#include "ac_trackview.h"

#include <QScrollBar>

void TrackView::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    int boxWidth = 24;
    int labelWidth = width() - (3 * boxWidth) - 2;
    setColumnWidth(0, boxWidth);
    setColumnWidth(1, labelWidth);
    setColumnWidth(2, boxWidth);
    setColumnWidth(3, boxWidth);
    QAbstractItemModel *m = model();
    QModelIndex root_index = rootIndex();
    int rowH = rowHeight(m->index(0, 0, root_index));
    if (rowH)
        verticalScrollBar()->setRange(0, (((m->rowCount(root_index) + 1) * rowH) - viewport()->height()) / rowH);
}
