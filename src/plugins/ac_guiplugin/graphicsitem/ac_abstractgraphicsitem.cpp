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

#include "ac_abstractgraphicsitem.h"
#include <ac_scenemanager.h>
#include <ac_score.h>
#include <mi_fontsettings.h>
#include <mi_object.h>
#include <QFont>
#include <QFontMetrics>
#include <QGraphicsItem>

const AcScore *AcAbstractGraphicsItemPrivate::score() const
{
    return AcScore::instance();
}

const QFont AcAbstractGraphicsItemPrivate::font() const
{
    MiFontSettings *fontSettings = score()->fontSettings();
    return QFont(fontSettings->family(), fontSettings->pointSize());
}

const QFontMetrics &AcAbstractGraphicsItemPrivate::fontMetrics() const
{
    return AcSceneManager::instance()->fontMetrics();
}

const QGraphicsScene *AcAbstractGraphicsItemPrivate::pitchScene() const
{
    return AcSceneManager::instance()->scene(PitchScene);
}

const QGraphicsScene *AcAbstractGraphicsItemPrivate::volumeScene() const
{
    return AcSceneManager::instance()->scene(VolumeScene);
}

const QGraphicsScene *AcAbstractGraphicsItemPrivate::timeLabelScene() const
{
    return AcSceneManager::instance()->scene(TimeLabelScene);
}

const QGraphicsScene *AcAbstractGraphicsItemPrivate::pitchLabelScene() const
{
    return AcSceneManager::instance()->scene(PitchLabelScene);
}

const QGraphicsScene *AcAbstractGraphicsItemPrivate::volumeLabelScene() const
{
    return AcSceneManager::instance()->scene(VolumeLabelScene);
}

AcAbstractGraphicsItem::~AcAbstractGraphicsItem()
{
    delete d_ptr;
}

bool AcAbstractGraphicsItem::isVisible() const
{
    for (int i = 0;  i < SceneTypeCount;  ++i)
        if (sceneItem(SceneType(i))->isVisible())
            return true;
    return false;
}

void AcAbstractGraphicsItem::show()
{
    for (int i = 0;  i < SceneTypeCount;  ++i) {
        QGraphicsItem *item = sceneItem(SceneType(i));
        if (item)
            item->show();
    }
}

void AcAbstractGraphicsItem::hide()
{
    for (int i = 0;  i < SceneTypeCount;  ++i) {
        QGraphicsItem *item = sceneItem(SceneType(i));
        if (item)
            item->hide();
    }
}

void AcAbstractGraphicsItem::addItem(AcAbstractGraphicsItem *item)
{
    for (int i = 0;  i < SceneTypeCount;  ++i) {
        QGraphicsItem *parentSceneItem = sceneItem(SceneType(i));
        QGraphicsItem *sceneItem = item->sceneItem(SceneType(i));
        if (parentSceneItem && sceneItem)
            sceneItem->setParentItem(parentSceneItem);
    }
}

void AcAbstractGraphicsItem::setDataObject(MiObject *object)
{
    MiObject *dataObject = this->dataObject();
    Q_DISCONNECT(dataObject);
    if (object) {
        Q_CONNECT(object, SIGNAL(changed(int)), this, SLOT(updateDataObject(int)));
        for (int i = 0;  i < object->propertyCount();  ++i)
            updateDataObject(i);
    } else
        hide();
}
