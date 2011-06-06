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

#include "ac_pitchview.h"

#include <ac_score.h>
#include <ac_scoreview.h>
#include <ac_viewsettings.h>

#include <QGraphicsTextItem>

using namespace Private;

namespace Private {

class AcPitchViewData
{
public:
    QFont font;
    QFontMetrics fontMetrics;
    QList<QGraphicsTextItem*> pitchTextItems;

    AcPitchViewData()
        :   font("Arial", 8)
        ,   fontMetrics(font)
    {}

    void initPitchTextItems()
    {
        QGraphicsScene *pitchScene = AcPitchView::instance()->scene();
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
        AcViewSettings *viewSettings = AcScore::instance()->viewSettings();

        QString s = textItem->toPlainText();
        QRect rect = fontMetrics.boundingRect(s);
        textItem->setPos(20.0f - rect.width(), (qAbs(s.toDouble() - 127.0f) * viewSettings->scaleY()) - (rect.height() / 1.5));
    }

    void updatePitchScene()
    {
        AcPitchView *pitchView = AcPitchView::instance();
        QGraphicsScene *pitchScene = pitchView->scene();
        AcScoreView *scoreView = AcScoreView::instance();
        AcViewSettings *viewSettings = AcScore::instance()->viewSettings();

        const qreal scaleX = viewSettings->scaleX();
        const qreal scaleY = viewSettings->scaleY();

        QPointF topLeft = scoreView->mapToScene(scoreView->rect().topLeft());
        QPointF bottomRight = scoreView->mapToScene(scoreView->rect().bottomRight());

        topLeft.rx() *= scaleX;
        topLeft.ry() *= scaleY;
        bottomRight.rx() *= scaleX;
        bottomRight.ry() *= scaleY;

        pitchScene->setSceneRect(0.0f, topLeft.y(), 10.0f, bottomRight.y() - topLeft.y());
        pitchView->centerOn(5.0f, scoreView->center().y() * scaleY);

        foreach (QGraphicsTextItem *textItem, pitchTextItems)
            updatePitchTextItem(textItem);
    }
};

} // namespace Private

static AcPitchView *instance = 0;

AcPitchView::AcPitchView(QGraphicsScene *scene, QWidget *parent)
    :   AcGraphicsView(scene, parent)
    ,   d(new AcPitchViewData)
{
    ::instance = this;

    d->initPitchTextItems();
}

AcPitchView::~AcPitchView()
{
    delete d;
}

AcPitchView *AcPitchView::instance()
{
    return ::instance;
}

void AcPitchView::update()
{
    d->updatePitchScene();
}

void AcPitchView::updateViewSettings(const QString &propertyName)
{
    d->updatePitchScene();
}
