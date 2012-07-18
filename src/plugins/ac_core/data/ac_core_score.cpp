/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2012 Andrew Fillebrown.
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

#include "ac_core_score.h"

#include <mi_idatabase.h>
#include <mi_idataobjectfactory.h>

#include <mi_core_scopeddatachange.h>

namespace Ac {
namespace Core {

using namespace Mi::Core;

static Score *instance = 0;

Score *Score::instance()
{
    return Core::instance;
}

IAggregator *Score::init()
{
    IDataObjectFactory *factory = query<IDataObjectFactory>(IDatabase::instance());
    _tracks = factory->create(Ac::TrackListItem);
    _gridSettings = factory->create(Ac::GridSettingsItem);
    _projectSettings = factory->create(Ac::ProjectSettingsItem);
    _viewSettings = factory->create(Ac::ViewSettingsItem);
    ScoreObject::init();
    return Core::instance = this;
}

Score::~Score()
{
    delete _viewSettings;
    delete _projectSettings;
    delete _gridSettings;
    delete _tracks;
}

bool Score::setLength(qreal length)
{
    length = qMax(qreal(1.0f), length);
    if (_length == length)
        return false;
    ScopedDataChange data_change(this, Ac::LengthRole);
    _length = length;
    return true;
}

bool Score::setStartTime(qreal time)
{
    time = qBound(qreal(0.0f), time, length());
    if (_startTime == time)
        return false;
    ScopedDataChange data_change(this, Ac::StartTimeRole);
    _startTime = time;
    return true;
}

IAggregate *Score::ModelData::init()
{
    return ScoreObject::ModelData::init();
}

IAggregate *Score::ModelItem::init()
{
    return ScoreObject::ModelItem::init();
}

} // namespace Core
} // namespace Ac




//#include <ac_ientity.h>
//#include <ac_graphicsitem.h>
//#include <ac_gridline.h>
//#include <ac_gridsettings.h>
//#include <ac_iplaycursor.h>
//#include <ac_projectsettings.h>
//#include <ac_track.h>
//#include <ac_viewsettings.h>

//#include <mi_uniquelynamedobjectlist.h>

//#include <QTimer>

//template <class T> class TrackList : public UniquelyNamedObjectTList<T>
//{
//public:
//    TrackList(QObject *parent = 0);

//    void insert(int i, Object *object)
//    {
//        int suffix = 1;
//        if ("Track" == object->name()) {
//            while (this->hasChild(QString("Track.%1").arg(suffix)))
//                ++suffix;
//            object->setName(QString("Track.%1").arg(suffix));
//        }
//        UniquelyNamedObjectTList<T>::insert(i, object);
//    }
//};

//template <class T> class TrackListPrivate : public ObjectTListPrivate<T>
//{
//    Q_DECLARE_PUBLIC_TEMPLATE(TrackList)

//public:
//    TrackListPrivate(TrackList<T> *q)
//        :   ObjectTListPrivate<T>(q)
//    {}

//    void endInsertObjects()
//    {
//        ObjectTListPrivate<T>::endInsertObjects();
//        updateZValues();
//    }

//    void endRemoveObjects()
//    {
//        ObjectTListPrivate<T>::endRemoveObjects();
//        updateZValues();
//    }

//    void updateZValues()
//    {
//        Q_Q_T(TrackList);
//        const int n = q->count();
//        for (int i = 0;  i < n;  ++i)
//            q->at(i)->setZValue(qreal(n - i));
//    }
//};

//template <class T> inline TrackList<T>::TrackList(QObject *parent)
//    :   UniquelyNamedObjectTList<T>(*(new TrackListPrivate<T>(this)), parent)
//{}

//class PlayCursorImplementation
//        :   public IPlayCursor
//        ,   public IEntity
//{
//public:
//    Score *q;

//    PlayCursorImplementation(Score *q)
//        :   q(q)
//    {}

//    // IPlayCursor
//    qreal playCursorPosition() const
//    {
//        return q->startTime();
//    }

//    void dragPlayCursorTo(qreal position)
//    {
//        q->setPlaybackTime(position - q->startTime());
//    }

//    void setPlayCursorPosition(qreal position)
//    {
//        q->setStartTime(position);
//    }

//    // IEntity
//    const PointList &points() const
//    {
//        static PointList points;
//        return points;
//    }

//    void pushPoints(const PointList &points)
//    {
//        Q_UNUSED(points);
//    }

//    void popPoints()
//    {}

//    void setPoints(const PointList &points)
//    {
//        Q_UNUSED(points);
//    }

//    void highlight()
//    {
//        q->highlightPlayCursor();
//    }

//    void unhighlight()
//    {
//        q->unhighlightPlayCursor();
//    }

//    bool intersects(const QRectF &rect) const
//    {
//        const qreal play_cursor_time = q->playCursorTime();
//        return rect.left() <= play_cursor_time && play_cursor_time <= rect.right();
//    }

//    bool isVisible() const
//    {
//        return true;
//    }

//    QList<IEntity*> subEntities(int sceneType) const
//    {
//        Q_UNUSED(sceneType);
//        return QList<IEntity*>();
//    }

//    // IUnknown
//    void *query(int type) const
//    {
//        switch (type) {
//        case Ac::PlayCursorInterface:
//            return objectToInterface_cast<IPlayCursor>(this);
//        case Ac::EntityInterface:
//            return objectToInterface_cast<IEntity>(this);
//        default:
//            return 0;
//        }
//    }
//};

//ScorePrivate::ScorePrivate(Score *q)
//    :   ScoreObjectPrivate(q)
//    ,   length(128.0f)
//    ,   startTime(0.0f)
//    ,   playCursorTime(0.0f)
//    ,   tracks(0)
//    ,   gridSettings(0)
//    ,   viewSettings(0)
//    ,   projectSettings(0)
//    ,   playCursorImplementation(new PlayCursorImplementation(q))
//    ,   timeLabelPlayCursor(0)
//    ,   pitchPlayCursor(0)
//    ,   controlPlayCursor(0)
//    ,   playCursorTimer(0)
//{
//    for (int i = 0;  i < Ac::SceneTypeCount;  ++i)
//        mainGraphicsItems.insert(Ac::SceneType(i), new GraphicsRootItem);
//    unitXGraphicsItems.insert(Ac::PitchScene, new GraphicsItem(mainGraphicsItems[Ac::PitchScene]));
//    unitXGraphicsItems.insert(Ac::ControlScene, new GraphicsItem(mainGraphicsItems[Ac::ControlScene]));
//    unitYGraphicsItems.insert(Ac::PitchScene, new GraphicsItem(mainGraphicsItems[Ac::PitchScene]));
//    unitXGraphicsItems[Ac::PitchScene]->setTransform(QTransform::fromScale(length, 1.0f));
//    unitXGraphicsItems[Ac::ControlScene]->setTransform(QTransform::fromScale(length, 1.0f));
//    unitYGraphicsItems[Ac::PitchScene]->setTransform(QTransform::fromScale(1.0f, 127.0f));
//}

//void ScorePrivate::init()
//{
//    tracks = new TrackList<Track>(q_ptr);
//    gridSettings = new GridSettings(q_ptr);
//    viewSettings = new ViewSettings(q_ptr);
//    projectSettings = new ProjectSettings(q_ptr);

//    timeLabelPlayCursor = new QGraphicsLineItem(mainGraphicsItems.value(Ac::TimeLabelScene));
//    pitchPlayCursor = new QGraphicsLineItem(unitYGraphicsItems.value(Ac::PitchScene));
//    controlPlayCursor = new QGraphicsLineItem(mainGraphicsItems.value(Ac::ControlScene));

//    QVariant play_cursor_implementation = quintptr(playCursorImplementation);
//    timeLabelPlayCursor->setData(0, play_cursor_implementation);
//    pitchPlayCursor->setData(0, play_cursor_implementation);
//    controlPlayCursor->setData(0, play_cursor_implementation);

//    QPen cursorPen(QColor(Qt::green));
//    cursorPen.setCosmetic(true);
//    timeLabelPlayCursor->setPen(cursorPen);
//    pitchPlayCursor->setPen(cursorPen);
//    controlPlayCursor->setPen(cursorPen);

//    timeLabelPlayCursor->setLine(0.0f, -10.0f, 0.0f, 10.0f);
//    pitchPlayCursor->setLine(0.0f, -1.0f, 0.0f, 2.0f);
//    controlPlayCursor->setLine(0.0f, -1.0f, 0.0f, 2.0f);

//    playCursorTimer = new QTimer(q_ptr);
//    playCursorTimer->setSingleShot(true);
//}

//ScorePrivate::~ScorePrivate()
//{
//    delete controlPlayCursor;
//    delete pitchPlayCursor;
//    delete timeLabelPlayCursor;
//    delete playCursorImplementation;
//    delete projectSettings;
//    delete viewSettings;
//    delete gridSettings;
//    qDeleteAll(tracks);
//    delete tracks;
//}

//void ScorePrivate::updateLength()
//{
//    foreach (QGraphicsItem *item, unitXGraphicsItems)
//        item->setTransform(QTransform::fromScale(length, 1.0f));
//}

//void ScorePrivate::setPlayCursorTime(qreal time)
//{
//    if (time < 0.0f)
//        time = 0.0f;
//    if (timeLabelPlayCursor->pos().x() == time)
//        return;
//    timeLabelPlayCursor->setPos(time, 0.0f);
//    pitchPlayCursor->setPos(time, 0.0f);
//    controlPlayCursor->setPos(time, 0.0f);
//}

//static Score *instance = 0;

//Score::Score(QObject *parent)
//    :   ScoreObject(*(new ScorePrivate(this)), parent)
//{
//    Q_D(Score);
//    ::instance = this;
//    setName("Score");
//    d->init();
//    d->setModel(object_cast<IModel>(parent));
//    connect(d->playCursorTimer, SIGNAL(timeout()), SLOT(updatePlayCursor()));
//}

//Score *Score::instance()
//{
//    return ::instance;
//}

//qreal Score::length() const
//{
//    Q_D(const Score);
//    return d->length;
//}

//void Score::setLength(qreal length)
//{
//    Q_D(Score);
//    if (length < 1.0f)
//        length = 1.0f;
//    if (d->length == length)
//        return;
//    d->beginChangeData();
//    d->length = length;
//    d->updateLength();
//    d->endChangeData();
//    if (length <= d->startTime)
//        setStartTime(0.0f);
//}

//qreal Score::startTime() const
//{
//    Q_D(const Score);
//    return d->startTime;
//}

//void Score::setStartTime(qreal time)
//{
//    Q_D(Score);
//    if (time < 0.0f)
//        time = 0.0f;
//    if (d->length < time)
//        time = d->length;
//    if (d->startTime == time)
//        return;
//    d->beginChangeData();
//    d->startTime = time;
//    d->setPlayCursorTime(time);
//    d->playCursorTime = 0.0f;
//    d->endChangeData();
//}

//qreal Score::playCursorTime() const
//{
//    Q_D(const Score);
//    return d->startTime + d->playCursorTime;
//}

//void Score::setPlaybackTime(qreal time)
//{
//    Q_D(Score);
//    if (time + d->startTime < 0.0f)
//        time = -d->startTime;
//    if (d->length < time + d->startTime)
//        time = d->length - d->startTime;
//    d->playCursorTime = time;
//    d->playCursorTimer->start();
//}

//void Score::highlightPlayCursor()
//{
//    Q_D(Score);
//    QPen pen = d->timeLabelPlayCursor->pen();
//    pen.setWidth(2);
//    d->timeLabelPlayCursor->setPen(pen);
//    d->pitchPlayCursor->setPen(pen);
//    d->controlPlayCursor->setPen(pen);
//}

//void Score::unhighlightPlayCursor()
//{
//    Q_D(Score);
//    QPen pen = d->timeLabelPlayCursor->pen();
//    pen.setWidth(1);
//    d->timeLabelPlayCursor->setPen(pen);
//    d->pitchPlayCursor->setPen(pen);
//    d->controlPlayCursor->setPen(pen);
//}

//ObjectTList<Track> *Score::tracks() const
//{
//    Q_D(const Score);
//    return d->tracks;
//}

//GridSettings *Score::gridSettings() const
//{
//    Q_D(const Score);
//    return d->gridSettings;
//}

//ViewSettings *Score::viewSettings() const
//{
//    Q_D(const Score);
//    return d->viewSettings;
//}

//ProjectSettings *Score::projectSettings() const
//{
//    Q_D(const Score);
//    return d->projectSettings;
//}

//QGraphicsItem *Score::sceneItem(int type) const
//{
//    Q_D(const Score);
//    return d->mainGraphicsItems[type];
//}

//void Score::clear()
//{
//    Q_D(Score);
//    emit aboutToBeReset();
//    d->projectSettings->clear();
//    d->viewSettings->clear();
//    d->gridSettings->clear();
//    d->tracks->clear();
//    d->length = 128.0f;
//    d->startTime = 0.0f;
//    emit reset();
//}

//int Score::modelItemIndex(const IModelItem *item) const
//{
//    Q_D(const Score);
//    if (d->tracks == item)
//        return ScoreObject::ModelItemCount;
//    if (d->gridSettings == item)
//        return ScoreObject::ModelItemCount + 1;
//    if (d->viewSettings == item)
//        return ScoreObject::ModelItemCount + 2;
//    if (d->projectSettings == item)
//        return ScoreObject::ModelItemCount + 3;
//    return ScoreObject::modelItemIndex(item);
//}

//IModelItem *Score::modelItemAt(int i) const
//{
//    switch (i - ScoreObject::ModelItemCount) {
//    case 0:
//        return tracks();
//    case 1:
//        return gridSettings();
//    case 2:
//        return viewSettings();
//    case 3:
//        return projectSettings();
//    default:
//        return ScoreObject::modelItemAt(i);
//    }
//}

//IModelItem *Score::findModelItem(int type) const
//{
//    switch (type) {
//    case Ac::GridSettingsItem:
//        return gridSettings();
//    case Ac::ViewSettingsItem:
//        return viewSettings();
//    case Ac::ProjectSettingsItem:
//        return projectSettings();
//    default:
//        return ScoreObject::findModelItem(type);
//    }
//}

//IModelItem *Score::findModelItemList(int type) const
//{
//    switch (type) {
//    case Ac::TrackItem:
//        return tracks();
//    default:
//        return ScoreObject::findModelItemList(type);
//    }
//}

//QVariant Score::data(int role) const
//{
//    switch (role) {
//    case Ac::StartTimeRole:
//        return startTime();
//    default:
//        return ScoreObject::data(role);
//    }
//}

//bool Score::setData(const QVariant &value, int role)
//{
//    switch (role) {
//    case Ac::LengthRole:
//        setLength(value.toReal());
//        return true;
//    case Ac::StartTimeRole:
//        setStartTime(value.toReal());
//        return true;
//    case Ac::PlaybackTimeRole:
//        setPlaybackTime(value.toReal());
//        return true;
//    default:
//        return ScoreObject::setData(value, role);
//    }
//}

//void Score::updatePlayCursor()
//{
//    Q_D(Score);
//    d->setPlayCursorTime(d->startTime + d->playCursorTime);
//}
