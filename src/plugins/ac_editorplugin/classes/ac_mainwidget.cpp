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
    AcGraphicsScene *scoreScene;
    MiGraphicsScene *timeScene;
    MiGraphicsScene *pitchScene;
    MiGraphicsScene *volumeScene;

    QGridLayout *layout;
    MiGraphicsView *scoreSceneView;
    MiGraphicsView *timeSceneView;
    MiGraphicsView *pitchSceneView;
    MiGraphicsView *volumeSceneView;
    MiGraphicsView *topLeft;
    MiGraphicsView *bottomLeft;

    QPointF sceneViewCenter;

    QFont font;
    QFontMetrics fontMetrics;
    QList<QGraphicsTextItem*> pitchTextItems;

    AcMainWidgetData(AcMainWidget *q)
        :   q(q)
        ,   scoreScene(new AcGraphicsScene(q))
        ,   timeScene(new MiGraphicsScene(q))
        ,   pitchScene(new MiGraphicsScene(q))
        ,   volumeScene(new MiGraphicsScene(q))
        ,   layout(new QGridLayout(q))
        ,   scoreSceneView(new MiGraphicsView(scoreScene, q))
        ,   timeSceneView(new MiGraphicsView(timeScene, q))
        ,   pitchSceneView(new MiGraphicsView(pitchScene, q))
        ,   volumeSceneView(new MiGraphicsView(volumeScene, q))
        ,   topLeft(new MiGraphicsView(0, q))
        ,   bottomLeft(new MiGraphicsView(0, q))
        ,   font("Arial", 8)
        ,   fontMetrics(font)
    {
        layout->setContentsMargins(QMargins(0, 0, 0, 0));
        layout->setSpacing(0);
        layout->addWidget(topLeft, 0, 0);
        layout->addWidget(timeSceneView, 0, 1);
        layout->addWidget(pitchSceneView, 1, 0);
        layout->addWidget(scoreSceneView, 1, 1);
        layout->addWidget(bottomLeft, 2, 0);
        layout->addWidget(volumeSceneView, 2, 1);

        const int sideWidth = 64;
        const int sideHeight = 64;
        const int volumeHeight = 128;

        scoreSceneView->setFrameShape(QFrame::Box);
        scoreSceneView->setFrameShadow(QFrame::Sunken);
        scoreSceneView->setLineWidth(1);
        scoreSceneView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scoreSceneView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        timeSceneView->setFixedHeight(sideHeight);
        timeSceneView->setFrameShape(QFrame::NoFrame);
        timeSceneView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        timeSceneView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        pitchSceneView->setFixedWidth(sideWidth);
        pitchSceneView->setFrameShape(QFrame::NoFrame);
        pitchSceneView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        pitchSceneView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        volumeSceneView->setFixedHeight(volumeHeight);
        volumeSceneView->setFrameShape(QFrame::Box);
        volumeSceneView->setFrameShadow(QFrame::Sunken);
        volumeSceneView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        volumeSceneView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        topLeft->setFixedSize(sideWidth, sideHeight);
        topLeft->setFrameShape(QFrame::NoFrame);

        bottomLeft->setFixedSize(sideWidth, volumeHeight);
        bottomLeft->setFrameShape(QFrame::NoFrame);

        AcScore *score = AcScore::instance();
        viewSettings = qobject_cast<AcViewSettings*>(score->findObject("ViewSettings"));

        initPitchTextItems();
        updateViewCenter();
    }

    void initPitchTextItems()
    {
        QGraphicsTextItem *textItem = 0;

        textItem = pitchScene->addText("0.0", font);
        pitchTextItems.append(textItem);

        textItem = pitchScene->addText("60.0", font);
        pitchTextItems.append(textItem);

        textItem = pitchScene->addText("127.0", font);
        pitchTextItems.append(textItem);

        foreach (QGraphicsTextItem *textItem, pitchTextItems)
            updatePitchTextItem(textItem);
    }

    void updatePitchTextItem(QGraphicsTextItem *textItem)
    {
        QString s = textItem->toPlainText();
        QRect rect = fontMetrics.boundingRect(s);
        textItem->setPos(20.0f - rect.width(), (qAbs(s.toDouble() - 127.0f) * viewSettings->scaleY()) - (rect.height() / 1.5));
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

        foreach (QGraphicsTextItem *textItem, pitchTextItems)
            updatePitchTextItem(textItem);
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
