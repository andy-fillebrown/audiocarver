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

#include "ac_graphicsitem.h"
#include <ac_scenemanager.h>
#include <QGraphicsItem>

bool AcGraphicsItem::isVisible() const
{
    for (int i = 0;  i < SceneTypeCount;  ++i)
        if (sceneItem(SceneType(i))->isVisible())
            return true;
    return false;
}

void AcGraphicsItem::show()
{
    for (int i = 0;  i < SceneTypeCount;  ++i) {
        QGraphicsItem *item = sceneItem(SceneType(i));
        if (item)
            item->show();
    }
}

void AcGraphicsItem::hide()
{
    for (int i = 0;  i < SceneTypeCount;  ++i) {
        QGraphicsItem *item = sceneItem(SceneType(i));
        if (item)
            item->hide();
    }
}

void AcGraphicsItem::addItem(AcGraphicsItem *item)
{
    for (int i = 0;  i < SceneTypeCount;  ++i) {
        QGraphicsItem *parentSceneItem = sceneItem(SceneType(i));
        QGraphicsItem *sceneItem = item->sceneItem(SceneType(i));
        if (parentSceneItem && sceneItem)
            sceneItem->setParentItem(parentSceneItem);
    }
}

const AcSceneManager *AcGraphicsItemPrivate::sceneManager() const
{
    return AcSceneManager::instance();
}

const QGraphicsScene *AcGraphicsItemPrivate::pitchScene() const
{
    return sceneManager()->scene(PitchScene);
}

const QGraphicsScene *AcGraphicsItemPrivate::volumeScene() const
{
    return sceneManager()->scene(VolumeScene);
}

const QGraphicsScene *AcGraphicsItemPrivate::timeLabelScene() const
{
    return sceneManager()->scene(TimeLabelScene);
}

const QGraphicsScene *AcGraphicsItemPrivate::pitchLabelScene() const
{
    return sceneManager()->scene(PitchLabelScene);
}

const QGraphicsScene *AcGraphicsItemPrivate::volumeLabelScene() const
{
    return sceneManager()->scene(VolumeLabelScene);
}

const QFont &AcGraphicsItemPrivate::font() const
{
    return sceneManager()->font();
}

const QFontMetrics &AcGraphicsItemPrivate::fontMetrics() const
{
    return sceneManager()->fontMetrics();
}
