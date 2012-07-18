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

#include "ac_core_gridsettings.h"

#include <mi_idatabase.h>
#include <mi_idataobjectfactory.h>

#include <mi_core_scopeddatachange.h>

using namespace Mi::Core;

namespace Ac {
namespace Core {

IAggregator *GridSettings::init()
{
    IDataObjectFactory *factory = query<IDataObjectFactory>(IDatabase::instance());
    _timeGridLines = factory->create(Ac::TimeGridLineListItem);
    _pitchGridLines = factory->create(Ac::PitchGridLineListItem);
    _controlGridLines = factory->create(Ac::ControlGridLineListItem);
    return DataObject::init();
}

GridSettings::~GridSettings()
{
    delete _controlGridLines;
    delete _pitchGridLines;
    delete _timeGridLines;
}

bool GridSettings::setSnapEnabled(bool enabled)
{
    if (_snapEnabled == enabled)
        return false;
    ScopedDataChange data_change(this, SnapEnabledRole);
    _snapEnabled = enabled;
    return true;
}

bool GridSettings::setGridSnapEnabled(bool enabled)
{
    if (_gridSnapEnabled == enabled)
        return false;
    ScopedDataChange data_change(this, GridSnapEnabledRole);
    _gridSnapEnabled = enabled;
    return true;
}

bool GridSettings::setTimeSnap(qreal snap)
{
    snap = qMax(qreal(0.0f), snap);
    if (_timeSnap == snap)
        return false;
    ScopedDataChange data_change(this, TimeSnapRole);
    _timeSnap = snap;
    return true;
}

bool GridSettings::setPitchSnap(qreal snap)
{
    snap = qMax(qreal(0.0f), snap);
    if (_pitchSnap == snap)
        return false;
    ScopedDataChange data_change(this, PitchSnapRole);
    _pitchSnap = snap;
    return true;
}

bool GridSettings::setControlSnap(qreal snap)
{
    snap = qMax(qreal(0.0f), snap);
    if (_controlSnap == snap)
        return false;
    ScopedDataChange data_change(this, ControlSnapRole);
    _controlSnap = snap;
    return true;
}

IAggregate *GridSettings::ModelData::init()
{
    return DataObject::ModelData::init();
}

IAggregate *GridSettings::ModelItem::init()
{
    return DataObject::ModelItem::init();
}

} // namespace Core
} // namespace Ac




//#include "ac_gridsettings.h"

//#include <ac_graphicsitem.h>
//#include <ac_gridline.h>
//#include <ac_score.h>

//GridSettingsPrivate::GridSettingsPrivate(GridSettings *q)
//    :   GraphicsParentPrivate(q)
//    ,   snapEnabled(true)
//    ,   gridSnapEnabled(true)
//    ,   timeSnap(0.125f)
//    ,   pitchSnap(1.0f)
//    ,   controlSnap(0.125f)
//    ,   timeGridLines(0)
//    ,   pitchGridLines(0)
//    ,   controlGridLines(0)
//{
//    mainGraphicsItems.insert(Ac::ControlScene, new GraphicsItem);
//    mainGraphicsItems.insert(Ac::TimeLabelScene, new GraphicsItem);
//    mainGraphicsItems.insert(Ac::PitchLabelScene, new GraphicsItem);
//    mainGraphicsItems.insert(Ac::ControlLabelScene, new GraphicsItem);
//    unitXGraphicsItems.insert(Ac::PitchScene, new GraphicsItem);
//    unitXGraphicsItems.insert(Ac::ControlScene, new GraphicsItem);
//    unitYGraphicsItems.insert(Ac::PitchScene, new GraphicsItem);
//}

//void GridSettingsPrivate::init()
//{
//    timeGridLines = new ObjectTList<TimeGridLine>(q_ptr);
//    pitchGridLines = new ObjectTList<PitchGridLine>(q_ptr);
//    controlGridLines = new ObjectTList<ControlGridLine>(q_ptr);
//}

//GridSettingsPrivate::~GridSettingsPrivate()
//{
//    qDeleteAll(controlGridLines);
//    qDeleteAll(pitchGridLines);
//    qDeleteAll(timeGridLines);
//    delete controlGridLines;
//    delete pitchGridLines;
//    delete timeGridLines;
//}

//GraphicsParentPrivate *GridSettingsPrivate::graphicsParent() const
//{
//    Q_Q(const GridSettings);
//    Score *score = q->score();
//    return score ? score->d_func() : 0;
//}

//GridSettings::GridSettings(QObject *parent)
//    :   GraphicsParent(*(new GridSettingsPrivate(this)), parent)
//{
//    Q_D(GridSettings);
//    d->init();
//    setName("GridSettings");
//}

//Score *GridSettings::score() const
//{
//    return object_cast<Score>(QObject::parent());
//}

//bool GridSettings::isSnapEnabled() const
//{
//    Q_D(const GridSettings);
//    return d->snapEnabled;
//}

//void GridSettings::setSnapEnabled(bool enabled)
//{
//    Q_D(GridSettings);
//    if (d->snapEnabled == enabled)
//        return;
//    d->beginChangeData();
//    d->snapEnabled = enabled;
//    d->endChangeData();
//}

//bool GridSettings::isGridSnapEnabled() const
//{
//    Q_D(const GridSettings);
//    return d->gridSnapEnabled;
//}

//void GridSettings::setGridSnapEnabled(bool enabled)
//{
//    Q_D(GridSettings);
//    if (d->gridSnapEnabled == enabled)
//        return;
//    d->beginChangeData();
//    d->gridSnapEnabled = enabled;
//    d->endChangeData();
//}

//qreal GridSettings::timeSnap() const
//{
//    Q_D(const GridSettings);
//    return d->timeSnap;
//}

//void GridSettings::setTimeSnap(qreal snap)
//{
//    Q_D(GridSettings);
//    if (snap < 0.0f)
//        snap = 0.0f;
//    if (d->timeSnap == snap)
//        return;
//    d->beginChangeData();
//    d->timeSnap = snap;
//    d->endChangeData();
//}

//qreal GridSettings::pitchSnap() const
//{
//    Q_D(const GridSettings);
//    return d->pitchSnap;
//}

//void GridSettings::setPitchSnap(qreal snap)
//{
//    Q_D(GridSettings);
//    if (snap < 0.0f)
//        snap = 0.0f;
//    if (d->pitchSnap == snap)
//        return;
//    d->beginChangeData();
//    d->pitchSnap = snap;
//    d->endChangeData();
//}

//qreal GridSettings::controlSnap() const
//{
//    Q_D(const GridSettings);
//    return d->controlSnap;
//}

//void GridSettings::setControlSnap(qreal snap)
//{
//    Q_D(GridSettings);
//    if (snap < 0.0f)
//        snap = 0.0f;
//    if (d->controlSnap == snap)
//        return;
//    d->beginChangeData();
//    d->controlSnap = snap;
//    d->endChangeData();
//}

//ObjectTList<TimeGridLine> *GridSettings::timeGridLines() const
//{
//    Q_D(const GridSettings);
//    return d->timeGridLines;
//}

//ObjectTList<PitchGridLine> *GridSettings::pitchGridLines() const
//{
//    Q_D(const GridSettings);
//    return d->pitchGridLines;
//}

//ObjectTList<ControlGridLine> *GridSettings::controlGridLines() const
//{
//    Q_D(const GridSettings);
//    return d->controlGridLines;
//}

//void GridSettings::clear()
//{
//    Q_D(GridSettings);
//    d->controlGridLines->clear();
//    d->pitchGridLines->clear();
//    d->timeGridLines->clear();
//    d->controlSnap = 0.125f;
//    d->pitchSnap = 1.0f;
//    d->timeSnap = 0.125f;
//    d->gridSnapEnabled = true;
//    d->snapEnabled = true;
//}

//int GridSettings::modelItemIndex(const IModelItem *item) const
//{
//    Q_D(const GridSettings);
//    if (d->timeGridLines == item)
//        return 0;
//    if (d->pitchGridLines == item)
//        return 1;
//    if (d->controlGridLines == item)
//        return 2;
//    return Object::modelItemIndex(item);
//}

//IModelItem *GridSettings::modelItemAt(int i) const
//{
//    switch (i) {
//    case 0:
//        return timeGridLines();
//    case 1:
//        return pitchGridLines();
//    case 2:
//        return controlGridLines();
//    default:
//        return 0;
//    }
//}

//IModelItem *GridSettings::findModelItemList(int type) const
//{
//    switch (type) {
//    case Ac::TimeGridLineItem:
//        return timeGridLines();
//    case Ac::PitchGridLineItem:
//        return pitchGridLines();
//    case Ac::ControlGridLineItem:
//        return controlGridLines();
//    default:
//        return 0;
//    }
//}

//QVariant GridSettings::data(int role) const
//{
//    switch (role) {
//    case Ac::SnapEnabledRole:
//        return isSnapEnabled();
//    case Ac::GridSnapEnabledRole:
//        return isGridSnapEnabled();
//    case Ac::TimeSnapRole:
//        return timeSnap();
//    case Ac::PitchSnapRole:
//        return pitchSnap();
//    case Ac::ControlSnapRole:
//        return controlSnap();
//    default:
//        return GraphicsParent::data(role);
//    }
//}

//bool GridSettings::setData(const QVariant &value, int role)
//{
//    switch (role) {
//    case Ac::SnapEnabledRole:
//        setSnapEnabled(value.toBool());
//        return true;
//    case Ac::GridSnapEnabledRole:
//        setGridSnapEnabled(value.toBool());
//        return true;
//    case Ac::TimeSnapRole:
//        setTimeSnap(value.toReal());
//        return true;
//    case Ac::PitchSnapRole:
//        setPitchSnap(value.toReal());
//        return true;
//    case Ac::ControlSnapRole:
//        setControlSnap(value.toReal());
//        return true;
//    default:
//        return GraphicsParent::setData(value, role);
//    }
//}
