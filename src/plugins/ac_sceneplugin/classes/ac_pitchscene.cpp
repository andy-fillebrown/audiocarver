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

#include "ac_pitchscene.h"
#include <QGraphicsTextItem>

using namespace Private;

namespace Private {

class AcPitchSceneData
{
public:
    QFont font;
    QFontMetrics fontMetrics;
    QList<QGraphicsTextItem*> pitchTextItems;

    AcPitchSceneData()
        :   font("Arial", 8)
        ,   fontMetrics(font)
    {}

    void initPitchTextItems()
    {
        QGraphicsScene *pitchScene = AcPitchScene::instance();
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

    void updatePitchTextItem(QGraphicsTextItem *textItem, qreal scaleY = 1.0f)
    {
        QString text = textItem->toPlainText();
        QRect textRect = fontMetrics.boundingRect(text);
        textItem->setPos(20.0f - textRect.width(), ((127.0f - text.toDouble()) * scaleY) - (textRect.height() / 1.5));
    }
};

} // namespace Private

static AcPitchScene *instance = 0;

AcPitchScene::AcPitchScene(QObject *parent)
    :   AcGraphicsScene(parent)
    ,   d(new AcPitchSceneData)
{
    ::instance = this;
    d->initPitchTextItems();
}

AcPitchScene::~AcPitchScene()
{
    delete d;
}

AcPitchScene *AcPitchScene::instance()
{
    return ::instance;
}

void AcPitchScene::setSceneScaleY(qreal scaleY)
{
    foreach (QGraphicsTextItem *textItem, d->pitchTextItems)
        d->updatePitchTextItem(textItem, scaleY);
}

void AcPitchScene::updateScoreProperty(const QString &propertyName)
{
    Q_UNUSED(propertyName);
}
