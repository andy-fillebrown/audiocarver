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

#ifndef AC_LABELVIEW_H
#define AC_LABELVIEW_H

#include <ac_graphicsview.h>

class LabelViewPrivate;

class QModelIndex;

class LabelView : public GraphicsView
{
    Q_OBJECT

public:
    LabelView(QGraphicsScene *scene = 0, QWidget *parent = 0);
    ~LabelView();

public slots:
    void dataChanged(const QModelIndex &topRight, const QModelIndex &bottomLeft);

protected:
    virtual QModelIndex gridLineListIndex() const = 0;

    void scoreDataChanged();

private:
    Q_DISABLE_COPY(LabelView)
    LabelViewPrivate *d;
    friend class LabelViewPrivate;
};

#endif // AC_LABELVIEW_H
