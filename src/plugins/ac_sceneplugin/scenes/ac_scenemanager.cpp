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

#include "ac_scenemanager.h"
#include <ac_barline.h>
#include <ac_controlscene.h>
#include <ac_graphicsbarlineitem.h>
#include <ac_graphicstuninglineitem.h>
#include <ac_graphicsvaluelineitem.h>
#include <ac_pitchscene.h>
#include <ac_score.h>
#include <ac_scorescene.h>
#include <ac_timescene.h>
#include <ac_tuningline.h>
#include <ac_valueline.h>
#include <ac_valuescene.h>
#include <ac_viewsettings.h>
#include <mi_font.h>
#include <mi_list.h>
#include <QFont>
#include <QFontMetrics>

using namespace Private;

namespace Private {

template <typename ObjectType, typename ItemType>
static void updateItemsHelper(const QList<ObjectType*> &objects, QList<ItemType*> &items, QObject *parent)
{
    for (int i = 0;  i < objects.count();  ++i) {
        if (items.count() <= i) {
            ItemType *item = new ItemType(objects[i], parent);
            items.append(item);
        } else
            items[i]->setDatabaseObject(objects[i]);
    }
    while (objects.count() < items.count()) {
        delete items.last();
        items.removeLast();
    }
}

template <typename T, typename ExpandRect>
static void updateItemVisibilitiesHelper(const QList<T*> &items, ExpandRect expandRect)
{
    int minPriority = 0x7fffffff;
    int prevPriority = 0;
    QRectF prevRect;
    foreach (T *item, items) {
        if (minPriority < item->priority())
            continue;
        QRectF curRect = item->labelRect();
        expandRect(curRect);
        if (prevRect.intersects(curRect))
            minPriority = qMax(prevPriority, item->priority());
        else {
            prevPriority = item->priority();
            prevRect = curRect;
        }
    }
    foreach (T *item, items) {
        if (item->priority() <= minPriority)
            item->show();
        else
            item->hide();
    }
}

static void expandTopLabelRect(QRectF &rect)
{
    rect.setWidth(3.0f * rect.width());
}

static void expandLeftLabelRect(QRectF &rect)
{
    rect.setTop(rect.top() - (1.5f * rect.height()));
}

class AcSceneManagerData
{
public:
    AcSceneManager *q;
    AcScoreScene *scoreScene;
    AcControlScene *controlScene;
    AcTimeScene *timeScene;
    AcPitchScene *pitchScene;
    AcValueScene *valueScene;
    QList<AcGraphicsBarLineItem*> barItems;
    QList<AcGraphicsTuningLineItem*> tuningItems;
    QList<AcGraphicsValueLineItem*> valueItems;
    QFontMetrics fontMetrics;

    AcSceneManagerData(AcSceneManager *q)
        :   q(q)
        ,   scoreScene(new AcScoreScene(q))
        ,   controlScene(new AcControlScene(q))
        ,   timeScene(new AcTimeScene(q))
        ,   pitchScene(new AcPitchScene(q))
        ,   valueScene(new AcValueScene(q))
        ,   fontMetrics(font())
    {}

    virtual ~AcSceneManagerData()
    {
        qDeleteAll(valueItems);
        qDeleteAll(tuningItems);
        qDeleteAll(barItems);
    }

    QFont font() const
    {
        const MiFont *fontSettings = AcScore::instance()->fontSettings();
        return QFont(fontSettings->family(), fontSettings->pointSize());
    }

    void init()
    {
        updateBarItems();
        updateTuningItems();
        updateValueItems();
        updateFontMetrics();
        updateBarItemVisibilities();
        updateTuningItemVisibilities();
        updateValueItemVisibilities();
    }

    void updateBarItems()
    {
        updateItemsHelper(AcScore::instance()->barLines().list(), barItems, q);
    }

    void updateTuningItems()
    {
        updateItemsHelper(AcScore::instance()->tuningLines().list(), tuningItems, q);
    }

    void updateValueItems()
    {
        updateItemsHelper(AcScore::instance()->valueLines().list(), valueItems, q);
    }

    void updateFontMetrics()
    {
        fontMetrics = QFontMetrics(font());
    }

    void updateBarItemVisibilities()
    {
        updateItemVisibilitiesHelper(barItems, expandTopLabelRect);
    }

    void updateTuningItemVisibilities()
    {
        updateItemVisibilitiesHelper(tuningItems, expandLeftLabelRect);
    }

    void updateValueItemVisibilities()
    {
        updateItemVisibilitiesHelper(valueItems, expandLeftLabelRect);
    }
};

} // namespace Private

AcSceneManager *instance = 0;

AcSceneManager::AcSceneManager(QObject *parent)
    :   QObject(parent)
    ,   d(new AcSceneManagerData(this))
{
    ::instance = this;
    d->init();
    AcScore *score = AcScore::instance();
    connect(score, SIGNAL(propertyChanged(QString)), SLOT(updateScoreProperty(QString)));
    connect(score->fontSettings(), SIGNAL(propertyChanged(QString)), SLOT(updateFontSettingsProperty(QString)));
    connect(score->viewSettings(), SIGNAL(propertyChanged(QString)), SLOT(updateViewSettingsProperty(QString)));
}

AcSceneManager::~AcSceneManager()
{
    delete d;
}

AcSceneManager *AcSceneManager::instance()
{
    return ::instance;
}

void AcSceneManager::updateScoreProperty(const QString &propertyName)
{
    if ("barLines" == propertyName) {
        d->updateBarItems();
        d->updateBarItemVisibilities();
    }
    else if ("tuningLines" == propertyName) {
        d->updateTuningItems();
        d->updateTuningItemVisibilities();
    }
    else if ("valueLines" == propertyName) {
        d->updateValueItems();
        d->updateValueItemVisibilities();
    }
}

void AcSceneManager::updateFontSettingsProperty(const QString &propertyName)
{
    Q_UNUSED(propertyName);
    d->updateFontMetrics();
    d->updateBarItemVisibilities();
    d->updateTuningItemVisibilities();
    d->updateValueItemVisibilities();
}

void AcSceneManager::updateViewSettingsProperty(const QString &propertyName)
{
    if ("timeScale" == propertyName)
        d->updateBarItemVisibilities();
    else if ("pitchScale" == propertyName)
        d->updateTuningItemVisibilities();
    else if ("valueScale" == propertyName)
        d->updateValueItemVisibilities();
}

QGraphicsScene *AcSceneManager::scoreScene() const
{
    return d->scoreScene;
}

QGraphicsScene *AcSceneManager::controlScene() const
{
    return d->controlScene;
}

QGraphicsScene *AcSceneManager::timeScene() const
{
    return d->timeScene;
}

QGraphicsScene *AcSceneManager::pitchScene() const
{
    return d->pitchScene;
}

QGraphicsScene *AcSceneManager::valueScene() const
{
    return d->valueScene;
}

const QFontMetrics &AcSceneManager::fontMetrics() const
{
    return d->fontMetrics;
}
