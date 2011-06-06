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
    MiGraphicsScene *volumeScene;

    QGridLayout *layout;
    MiGraphicsView *timeView;
    MiGraphicsView *pitchView;
    MiGraphicsView *scoreView;
    MiGraphicsView *volumeView;
    MiGraphicsView *topLeft;
    MiGraphicsView *bottomLeft;

    QPointF viewCenter;

    QFont font;
    QFontMetrics fontMetrics;
    QList<QGraphicsTextItem*> pitchTextItems;

    AcMainWidgetData(AcMainWidget *q)
        :   q(q)
        ,   timeScene(new MiGraphicsScene(q))
        ,   pitchScene(new MiGraphicsScene(q))
        ,   scoreScene(new AcGraphicsScene(q))
        ,   volumeScene(new MiGraphicsScene(q))
        ,   layout(new QGridLayout(q))
        ,   timeView(new MiGraphicsView(timeScene, q))
        ,   pitchView(new MiGraphicsView(pitchScene, q))
        ,   scoreView(new MiGraphicsView(scoreScene, q))
        ,   volumeView(new MiGraphicsView(volumeScene, q))
        ,   topLeft(new MiGraphicsView(0, q))
        ,   bottomLeft(new MiGraphicsView(0, q))
        ,   font("Arial", 8)
        ,   fontMetrics(font)
    {
        layout->setContentsMargins(QMargins(0, 0, 0, 0));
        layout->setSpacing(0);
        layout->addWidget(topLeft, 0, 0);
        layout->addWidget(timeView, 0, 1);
        layout->addWidget(pitchView, 1, 0);
        layout->addWidget(scoreView, 1, 1);
        layout->addWidget(bottomLeft, 2, 0);
        layout->addWidget(volumeView, 2, 1);

        const int sideWidth = 64;
        const int sideHeight = 64;
        const int volumeHeight = 192;

        timeView->setFixedHeight(sideHeight);
        timeView->setFrameShape(QFrame::NoFrame);
        timeView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        timeView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        pitchView->setFixedWidth(sideWidth);
        pitchView->setFrameShape(QFrame::NoFrame);
        pitchView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        pitchView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        scoreView->setFrameShape(QFrame::Box);
        scoreView->setFrameShadow(QFrame::Sunken);
        scoreView->setLineWidth(1);
        scoreView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scoreView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        volumeView->setFixedHeight(volumeHeight);
        volumeView->setFrameShape(QFrame::Box);
        volumeView->setFrameShadow(QFrame::Sunken);
        volumeView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        volumeView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

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

        QPointF topLeft = scoreView->mapToScene(scoreView->rect().topLeft());
        QPointF bottomRight = scoreView->mapToScene(scoreView->rect().bottomRight());

        topLeft.rx() *= scaleX;
        topLeft.ry() *= scaleY;
        bottomRight.rx() *= scaleX;
        bottomRight.ry() *= scaleY;

        pitchScene->setSceneRect(0.0f, topLeft.y(), 10.0f, bottomRight.y() - topLeft.y());
        pitchView->centerOn(5.0f, viewCenter.y() * scaleY);

        foreach (QGraphicsTextItem *textItem, pitchTextItems)
            updatePitchTextItem(textItem);
    }

    void updateViewCenter()
    {
        viewCenter = scoreView->mapToScene(scoreView->rect().center());
        updatePitchScene();
    }

    void updateViewTransform()
    {
        scoreView->setTransform(QTransform::fromScale(viewSettings->scaleX(), viewSettings->scaleY()));
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
    return d->viewCenter.x();
}

void AcMainWidget::setPositionX(qreal positionX)
{
    const qreal prevX = d->viewCenter.x();
    d->scoreView->centerOn(positionX, d->viewCenter.y());
    d->updateViewCenter();
    if (d->viewCenter.x() != prevX)
        d->viewSettings->setPositionX(d->viewCenter.x());
}

qreal AcMainWidget::positionY() const
{
    return d->viewCenter.y();
}

void AcMainWidget::setPositionY(qreal positionY)
{
    const qreal prevY = d->viewCenter.y();
    d->scoreView->centerOn(d->viewCenter.x(), positionY);
    d->updateViewCenter();
    if (d->viewCenter.y() != prevY)
        d->viewSettings->setPositionY(d->viewCenter.y());
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
