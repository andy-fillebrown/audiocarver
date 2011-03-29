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

#include "ac_mainwidget.h"

#include <ac_graphicsscene.h>

#include <mi_graphicsview.h>

#include <QLayout>

using namespace Private;

namespace Private {

class AcMainWidgetData
{
public:
    AcMainWidget *q;
    AcGraphicsScene *scene;

    QGridLayout *layout;
    MiGraphicsView *topLeft;
    MiGraphicsView *topRight;
    MiGraphicsView *bottomLeft;
    MiGraphicsView *sceneView;

    AcMainWidgetData(AcMainWidget *q)
        :   q(q)
        ,   scene(new AcGraphicsScene(q))
        ,   layout(new QGridLayout(q))
        ,   topLeft(new MiGraphicsView(0, q))
        ,   topRight(new MiGraphicsView(0, q))
        ,   bottomLeft(new MiGraphicsView(0, q))
        ,   sceneView(new MiGraphicsView(scene, q))
    {
        layout->setContentsMargins(QMargins());
        layout->setSpacing(0);
        layout->addWidget(topLeft, 0, 0);
        layout->addWidget(topRight, 0, 1);
        layout->addWidget(bottomLeft, 1, 0);
        layout->addWidget(sceneView, 1, 1);

        topLeft->setMinimumSize(128, 128);
        topLeft->setMaximumSize(128, 128);

        topRight->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        topRight->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        topRight->setMinimumHeight(128);
        topRight->setMaximumHeight(128);

        bottomLeft->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        bottomLeft->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        bottomLeft->setMinimumWidth(128);
        bottomLeft->setMaximumWidth(128);

        sceneView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        sceneView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    }
};

} // namespace Private

static AcMainWidget *instance = 0;

AcMainWidget::AcMainWidget(QWidget *parent)
    :   QWidget(parent)
    ,   d(new AcMainWidgetData(this))
{
    ::instance = this;
}

AcMainWidget::~AcMainWidget()
{
    delete d;
}

AcMainWidget *AcMainWidget::instance()
{
    return ::instance;
}
