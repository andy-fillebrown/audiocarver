/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2013 Andrew Fillebrown.
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

#ifndef AC_GUI_TRACKVIEW_H
#define AC_GUI_TRACKVIEW_H

#include <QTreeView>

class TrackViewPrivate;
class TrackView : public QTreeView
{
    Q_OBJECT

    TrackViewPrivate *d;

public:
    static TrackView *instance();

    TrackView(QWidget *parent = 0);

    void setRootIndex(const QModelIndex &index)
    {
        QTreeView::setRootIndex(model()->index(0, 0, index));
    }

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void dropEvent(QDropEvent *event);
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);

private slots:
    void update();
};

#endif
