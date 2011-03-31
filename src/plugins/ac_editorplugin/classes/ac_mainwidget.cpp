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
#include <ac_score.h>
#include <ac_viewsettings.h>

#include <mi_graphicsview.h>

#include <QApplication>
#include <QLayout>
#include <QWheelEvent>

using namespace Private;

namespace Private {

class AcMainWidgetData
{
public:
    AcMainWidget *q;
    AcViewSettings *viewSettings;
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
        topRight->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        topRight->setMinimumHeight(128);
        topRight->setMaximumHeight(128);

        bottomLeft->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        bottomLeft->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        bottomLeft->setMinimumWidth(128);
        bottomLeft->setMaximumWidth(128);

        sceneView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        sceneView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        AcScore *score = AcScore::instance();
        viewSettings = qobject_cast<AcViewSettings*>(score->findObject("ViewSettings"));
    }

    void updateViewTransform()
    {
        sceneView->setTransform(QTransform::fromTranslate(viewSettings->positionX(), viewSettings->positionY()));
        sceneView->setTransform(QTransform::fromScale(viewSettings->scaleX(), viewSettings->scaleY()), true);
    }
};

} // namespace Private

static AcMainWidget *instance = 0;

AcMainWidget::AcMainWidget(QWidget *parent)
    :   QWidget(parent)
    ,   d(new AcMainWidgetData(this))
{
    ::instance = this;
    connect(d->viewSettings, SIGNAL(propertyChanged(int)), SLOT(updateViewSettings(int)));
}

AcMainWidget::~AcMainWidget()
{
    delete d;
}

AcMainWidget *AcMainWidget::instance()
{
    return ::instance;
}

qreal AcMainWidget::positionX() const
{
    return d->viewSettings->positionX();
}

void AcMainWidget::setPositionX(qreal positionX)
{
    d->viewSettings->setPositionX(positionX);
}

qreal AcMainWidget::positionY() const
{
    return d->viewSettings->positionY();
}

void AcMainWidget::setPositionY(qreal positionY)
{
    d->viewSettings->setPositionY(positionY);
}

qreal AcMainWidget::scaleX() const
{
    return d->viewSettings->scaleX();
}

void AcMainWidget::setScaleX(qreal scaleX)
{
    d->viewSettings->setScaleX(scaleX);
}

qreal AcMainWidget::scaleY() const
{
    return d->viewSettings->scaleY();
}

void AcMainWidget::setScaleY(qreal scaleY)
{
    d->viewSettings->setScaleY(scaleY);
}

void AcMainWidget::wheelEvent(QWheelEvent *event)
{
    if (QApplication::keyboardModifiers() & Qt::ControlModifier) {
        qreal scale = event->delta() < 0 ? 0.8f : 1.25f;
        if (QApplication::keyboardModifiers() & Qt::ShiftModifier)
            setScaleX(scale * scaleX());
        else
            setScaleY(scale * scaleY());
    } else {
        qreal offset = event->delta() < 0 ? 10.0f : -10.0f;
        if (QApplication::keyboardModifiers() & Qt::ShiftModifier)
            setPositionX(positionX() + offset);
        else
            setPositionY(positionY() + offset);
    }
    event->accept();
}

void AcMainWidget::updateViewSettings(int propertyIndex)
{
    const QString propName = d->viewSettings->propertyName(propertyIndex);
    if (propName == "scaleX"
            || propName == "scaleY"
            || propName == "positionX"
            || propName == "positionY")
        d->updateViewTransform();
}
