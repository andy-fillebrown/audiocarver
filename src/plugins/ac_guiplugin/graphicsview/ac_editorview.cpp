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

#include "ac_editorview.h"

class AcEditorViewPrivate
{
public:
    QPointF center;

    AcEditorViewPrivate()
    {}

    virtual ~AcEditorViewPrivate()
    {}
};

AcEditorView::AcEditorView(QGraphicsScene *scene, QWidget *parent)
    :   AcGraphicsView(scene, parent)
    ,   d(new AcEditorViewPrivate)
{}

AcEditorView::~AcEditorView()
{
    delete d;
}

const QPointF &AcEditorView::center() const
{
    return d->center;
}

void AcEditorView::setCenter(const QPointF &center)
{
    QPointF prevCtr = d->center;
    centerOn(center);
    d->center = mapToScene(rect().center());
    if (d->center != prevCtr)
        updateViewSettings();
}

void AcEditorView::setCenter(qreal x, qreal y)
{
    setCenter(QPointF(x, y));
}

void AcEditorView::updateCenter()
{
    setCenter(mapToScene(rect().center()));
}
