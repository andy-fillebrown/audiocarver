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

#include "ac_gui_timelabelview.h"
#include "ac_gui_graphicsviewmanager.h"
#include <idatabase.h>
#include <imodel.h>
#include <imodelitemlist.h>
#include <QModelIndex>

using namespace Ac;

static const QCursor &zoomCursor()
{
    static QCursor cursor(QPixmap(":/ac_gui/images/zoom-h-cursor.png"));
    return cursor;
}

class TimeLabelViewPrivate
{
public:
    TimeLabelView *q;

    TimeLabelViewPrivate(TimeLabelView *q)
        :   q(q)
    {}

    virtual ~TimeLabelViewPrivate()
    {}
};

TimeLabelView::TimeLabelView(QGraphicsScene *scene, QWidget *parent)
    :   LabelView(scene, parent)
    ,   d(new TimeLabelViewPrivate(this))
{
    setStyleSheet("QFrame {"
                  "border-top: 0px solid palette(shadow);"
                  "border-bottom: 1px solid palette(shadow);"
                  "border-left: 1px solid palette(shadow);"
                  "border-right: 1px solid palette(shadow);"
                  "}");
}

TimeLabelView::~TimeLabelView()
{
    delete d;
}

IModelItem *TimeLabelView::gridLineList() const
{
    return IDatabase::instance()->rootItem()->findList(TimeGridLineItem);
}

qreal TimeLabelView::sceneWidth() const
{
    const GraphicsViewManager *vm = GraphicsViewManager::instance();
    return vm->scoreLength() / vm->scale(TimeScaleRole);
}

QPointF TimeLabelView::sceneCenter() const
{
    const GraphicsViewManager *vm = GraphicsViewManager::instance();
    return QPointF(vm->position(TimePositionRole), qreal(0.0f));
}

void TimeLabelView::zoomStarting()
{
    setCursor(zoomCursor());
}
