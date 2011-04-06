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
#include <QGraphicsPathItem>
#include <QLayout>
#include <QWheelEvent>

using namespace Private;

namespace Private {

class AcMainWidgetData
{
public:
    AcMainWidget *q;
    AcViewSettings *viewSettings;
    MiGraphicsScene *timeScene;
    MiGraphicsScene *pitchScene;
    AcGraphicsScene *scoreScene;

    QGridLayout *layout;
    MiGraphicsView *topLeft;
    MiGraphicsView *timeSceneView;
    MiGraphicsView *pitchSceneView;
    MiGraphicsView *scoreSceneView;

    QPointF sceneViewCenter;

    QGraphicsPathItem *pitchLineItem;
    QGraphicsPathItem *pitchTextItem;

    AcMainWidgetData(AcMainWidget *q)
        :   q(q)
        ,   timeScene(new MiGraphicsScene(q))
        ,   pitchScene(new MiGraphicsScene(q))
        ,   scoreScene(new AcGraphicsScene(q))
        ,   layout(new QGridLayout(q))
        ,   topLeft(new MiGraphicsView(0, q))
        ,   timeSceneView(new MiGraphicsView(timeScene, q))
        ,   pitchSceneView(new MiGraphicsView(pitchScene, q))
        ,   scoreSceneView(new MiGraphicsView(scoreScene, q))
        ,   pitchLineItem(0)
        ,   pitchTextItem(0)
    {
        layout->setContentsMargins(QMargins());
        layout->setSpacing(0);
        layout->addWidget(topLeft, 0, 0);
        layout->addWidget(timeSceneView, 0, 1);
        layout->addWidget(pitchSceneView, 1, 0);
        layout->addWidget(scoreSceneView, 1, 1);

        topLeft->setMinimumSize(128, 128);
        topLeft->setMaximumSize(128, 128);

        timeSceneView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        timeSceneView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        timeSceneView->setMinimumHeight(128);
        timeSceneView->setMaximumHeight(128);

        pitchSceneView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        pitchSceneView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        pitchSceneView->setMinimumWidth(128);
        pitchSceneView->setMaximumWidth(128);
        pitchSceneView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

        scoreSceneView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scoreSceneView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        AcScore *score = AcScore::instance();
        viewSettings = qobject_cast<AcViewSettings*>(score->findObject("ViewSettings"));

        updateViewCenter();
    }

    void updateViewCenter()
    {
        sceneViewCenter = scoreSceneView->mapToScene(scoreSceneView->rect().center());
        updatePitchScene();
    }

    void updateViewTransform()
    {
        scoreSceneView->setTransform(QTransform::fromScale(viewSettings->scaleX(), viewSettings->scaleY()));
        updatePitchScene();
    }

    void updatePitchScene()
    {
        const qreal scaleX = viewSettings->scaleX();
        const qreal scaleY = viewSettings->scaleY();

        QPointF topLeft = scoreSceneView->mapToScene(scoreSceneView->rect().topLeft());
        QPointF bottomRight = scoreSceneView->mapToScene(scoreSceneView->rect().bottomRight());

        topLeft.rx() *= scaleX;
        topLeft.ry() *= scaleY;
        bottomRight.rx() *= scaleX;
        bottomRight.ry() *= scaleY;

        pitchScene->setSceneRect(0.0f, topLeft.y(), 10.0f, bottomRight.y() - topLeft.y());
        pitchSceneView->centerOn(5.0f, sceneViewCenter.y() * scaleY);

        if (pitchLineItem)
            pitchScene->removeItem(pitchLineItem);
        QPainterPath pitchLines;
        pitchLines.moveTo(0.0f, qAbs(0.0f - 127.0f) * scaleY);
        pitchLines.lineTo(10.0f, qAbs(0.0f - 127.0f) * scaleY);
        pitchLines.moveTo(0.0f, qAbs(60.0f - 127.0f) * scaleY);
        pitchLines.lineTo(10.0f, qAbs(60.0f - 127.0f) * scaleY);
        pitchLines.moveTo(0.0f, qAbs(127.0f - 127.0f) * scaleY);
        pitchLines.lineTo(10.0f, qAbs(127.0f - 127.0f) * scaleY);
        pitchLineItem = pitchScene->addPath(pitchLines);

        if (pitchTextItem)
            pitchScene->removeItem(pitchTextItem);
        QPainterPath pitchText;
        QFont font("Courier");
        QFontMetrics metrics(font);
        QString s;
        QRect rect;
        s = "0.0";
        rect = metrics.boundingRect(s);
        pitchText.addText(11.0f, (qAbs(0.0f - 127.0f) * scaleY) - rect.center().y(), font, s);
        s = "60.0";
        rect = metrics.boundingRect(s);
        pitchText.addText(11.0f, (qAbs(60.0f - 127.0f) * scaleY) - rect.center().y(), font, s);
        s = "127.0";
        rect = metrics.boundingRect(s);
        pitchText.addText(11.0f, (qAbs(127.0f - 127.0f) * scaleY) - rect.center().y(), font, s);
        pitchTextItem = pitchScene->addPath(pitchText);
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
    return d->sceneViewCenter.x();
}

void AcMainWidget::setPositionX(qreal positionX)
{
    const qreal prevX = d->sceneViewCenter.x();
    d->scoreSceneView->centerOn(positionX, d->sceneViewCenter.y());
    d->updateViewCenter();
    if (d->sceneViewCenter.x() != prevX)
        d->viewSettings->setPositionX(d->sceneViewCenter.x());
}

qreal AcMainWidget::positionY() const
{
    return d->sceneViewCenter.y();
}

void AcMainWidget::setPositionY(qreal positionY)
{
    const qreal prevY = d->sceneViewCenter.y();
    d->scoreSceneView->centerOn(d->sceneViewCenter.x(), positionY);
    d->updateViewCenter();
    if (d->sceneViewCenter.y() != prevY)
        d->viewSettings->setPositionY(d->sceneViewCenter.y());
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

void AcMainWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    d->updateViewCenter();
}

void AcMainWidget::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    d->updateViewCenter();
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
        int offset = event->delta() < 0 ? 10 : -10;
        if (QApplication::keyboardModifiers() & Qt::ShiftModifier)
            setPositionX(positionX() - offset);
        else
            setPositionY(positionY() + offset);
    }
    event->accept();
}

void AcMainWidget::updateViewSettings(int propertyIndex)
{
    const QString propName = d->viewSettings->propertyName(propertyIndex);
    if (propName == "scaleX" || propName == "scaleY")
        d->updateViewTransform();
}
