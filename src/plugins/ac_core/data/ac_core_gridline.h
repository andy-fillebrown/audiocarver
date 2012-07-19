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

#ifndef AC_CORE_GRIDLINE_H
#define AC_CORE_GRIDLINE_H

#include "mi_core_dataobject.h"

#include <ac_core_namespace.h>

#include <mi_core_utils.h>

namespace Ac {
namespace Core {

class AC_CORE_EXPORT GridLine : public Mi::Core::DataObject
{
    enum { RoleCount = 4 };

    qreal _location;
    QString _label;
    int _priority;
    int _color;

protected:
    enum {
        RoleCountOffset = DataObject::TotalRoleCount,
        TotalRoleCount = RoleCountOffset + RoleCount
    };

    GridLine()
        :   _location(0.0f)
        ,   _priority(0)
        ,   _color(Ac::lightGray)
    {}

    IAggregator *init();

    qreal location() const
    {
        return _location;
    }

    bool setLocation(qreal location);

    QString label() const
    {
        return _label;
    }

    bool setLabel(const QString &label);

    int priority() const
    {
        return _priority;
    }

    bool setPriority(int priority);

    int color() const
    {
        return _color;
    }

    bool setColor(int color);

    class AC_CORE_EXPORT ModelData : public DataObject::ModelData
    {
        friend class GridLine;

        GridLine *a() const
        {
            return static_cast<GridLine*>(DataObject::ModelData::a());
        }

    protected:
        ModelData(GridLine *aggregator)
            :   DataObject::ModelData(aggregator)
        {}

        IAggregate *init();

        // IModelData
        int roleCount() const
        {
            return TotalRoleCount;
        }

        int roleAt(int i) const
        {
            switch (i - RoleCountOffset) {
            case 0:
                return LocationRole;
            case 1:
                return LabelRole;
            case 2:
                return PriorityRole;
            case 3:
                return ColorRole;
            default:
                return DataObject::ModelData::roleAt(i);
            }
        }

        QVariant getVariant(int role) const
        {
            switch (role) {
            case LocationRole:
                return a()->location();
            case LabelRole:
                return a()->label();
            case PriorityRole:
                return a()->priority();
            case ColorRole:
                return Mi::Core::intToColorString(a()->color());
            default:
                return DataObject::ModelData::getVariant(role);
            }
        }

        bool setVariant(const QVariant &data, int role)
        {
            switch (role) {
            case LocationRole:
                return a()->setLocation(qvariant_cast<qreal>(data));
            case LabelRole:
                return a()->setLabel(qvariant_cast<QString>(data));
            case PriorityRole:
                return a()->setPriority(qvariant_cast<int>(data));
            case ColorRole:
                return a()->setColor(Mi::Core::colorStringToInt(qvariant_cast<QString>(data)));
            default:
                return DataObject::ModelData::setVariant(data, role);
            }
        }
    };

    class AC_CORE_EXPORT ModelItem : public DataObject::ModelItem
    {
    protected:
        ModelItem(GridLine *aggregator)
            :   DataObject::ModelItem(aggregator)
        {}

        IAggregate *init();

        // IModelItem
        bool isTypeOfItem(int itemType) const
        {
            if (GridLineItem == itemType)
                return true;
            return DataObject::ModelItem::isTypeOfItem(itemType);
        }
    };

    // IAggregator
    IAggregate *createAggregate(int interfaceType)
    {
        switch (interfaceType) {
        case I::IModelData:
            return appendAggregate((new ModelData(this))->init());
        default:
            return DataObject::createAggregate(interfaceType);
        }
    }
};

class AC_CORE_EXPORT TimeGridLine : public GridLine
{
    friend class DataObjectFactory;

protected:
    TimeGridLine()
    {}

    IAggregator *init();

    class AC_CORE_EXPORT ModelItem : public GridLine::ModelItem
    {
        friend class TimeGridLine;

    protected:
        ModelItem(TimeGridLine *aggregator)
            :   GridLine::ModelItem(aggregator)
        {}

        IAggregate *init();

        int itemType() const
        {
            return TimeGridLineItem;
        }

        bool isTypeOfItem(int itemType) const
        {
            if (TimeGridLineItem == itemType)
                return true;
            return GridLine::ModelItem::isTypeOfItem(itemType);
        }
    };

    // IAggregator
    IAggregate *createAggregate(int interfaceType)
    {
        switch (interfaceType) {
        case I::IModelItem:
            return appendAggregate((new ModelItem(this))->init());
        default:
            return GridLine::createAggregate(interfaceType);
        }
    }
};

class AC_CORE_EXPORT PitchGridLine : public GridLine
{
    friend class DataObjectFactory;

protected:
    PitchGridLine()
    {}

    IAggregator *init();

    class AC_CORE_EXPORT ModelItem : public GridLine::ModelItem
    {
        friend class PitchGridLine;

    protected:
        ModelItem(PitchGridLine *aggregator)
            :   GridLine::ModelItem(aggregator)
        {}

        IAggregate *init();

        int itemType() const
        {
            return PitchGridLineItem;
        }

        bool isTypeOfItem(int itemType) const
        {
            if (PitchGridLineItem == itemType)
                return true;
            return GridLine::ModelItem::isTypeOfItem(itemType);
        }
    };

    // IAggregator
    IAggregate *createAggregate(int interfaceType)
    {
        switch (interfaceType) {
        case I::IModelItem:
            return appendAggregate((new ModelItem(this))->init());
        default:
            return GridLine::createAggregate(interfaceType);
        }
    }
};

class AC_CORE_EXPORT ControlGridLine : public GridLine
{
    friend class DataObjectFactory;

protected:
    ControlGridLine()
    {}

    IAggregator *init();

    class AC_CORE_EXPORT ModelItem : public GridLine::ModelItem
    {
        friend class ControlGridLine;

    protected:
        ModelItem(ControlGridLine *aggregator)
            :   GridLine::ModelItem(aggregator)
        {}

        IAggregate *init();

        int itemType() const
        {
            return ControlGridLineItem;
        }

        bool isTypeOfItem(int itemType) const
        {
            if (ControlGridLineItem == itemType)
                return true;
            return GridLine::ModelItem::isTypeOfItem(itemType);
        }
    };

    // IAggregator
    IAggregate *createAggregate(int interfaceType)
    {
        switch (interfaceType) {
        case I::IModelItem:
            return appendAggregate((new ModelItem(this))->init());
        default:
            return GridLine::createAggregate(interfaceType);
        }
    }
};

} // namespace Core
} // namespace Ac

#endif // AC_CORE_GRIDLINE_H




//#ifndef AC_GRIDLINE_H
//#define AC_GRIDLINE_H

//#include <ac_graphicsitem.h>
//#include <ac_graphicsobject.h>

//#include <QColor>

//class GridSettings;

//class GridLinePrivate;
//class AC_CORE_EXPORT GridLine : public GraphicsObject
//{
//    Q_OBJECT
//    Q_PROPERTY(qreal location READ location WRITE setLocation)
//    Q_PROPERTY(QString label READ label WRITE setLabel)
//    Q_PROPERTY(int priority READ priority WRITE setPriority)
//    Q_PROPERTY(QColor color READ color WRITE setColor)

//public:
//    GridSettings *gridSettings() const;

//    virtual bool isVisible() const = 0;
//    void setVisibility(bool visible)
//    {
//        if (visible)
//            show();
//        else
//            hide();
//    }

//    virtual void show() = 0;
//    virtual void hide() = 0;

//    // Properties
//    qreal location() const;
//    void setLocation(qreal location);
//    const QString &label() const;
//    void setLabel(const QString &label);
//    int priority() const;
//    void setPriority(int priority);
//    const QColor &color() const;
//    void setColor(const QColor &color);

//    // IModelItem
//    int persistentRoleAt(int i) const
//    {
//        switch (i - staticMetaObject.propertyOffset()) {
//        case 0:
//            return Ac::LocationRole;
//        case 1:
//            return Ac::LabelRole;
//        case 2:
//            return Ac::PriorityRole;
//        case 3:
//            return Ac::ColorRole;
//        default:
//            return Object::persistentRoleAt(i);
//        }
//    }

//    QVariant data(int role) const
//    {
//        switch (role) {
//        case Ac::LocationRole:
//            return location();
//        case Ac::LabelRole:
//            return label();
//        case Ac::PriorityRole:
//            return priority();
//        case Ac::ColorRole:
//            return color();
//        case Ac::VisibilityRole:
//            return isVisible();
//        default:
//            return GraphicsObject::data(role);
//        }
//    }

//    bool setData(const QVariant &value, int role)
//    {
//        switch (role) {
//        case Ac::LocationRole:
//            setLocation(value.toReal());
//            break;
//        case Ac::LabelRole:
//            setLabel(value.toString());
//            break;
//        case Ac::PriorityRole:
//            setPriority(value.toInt());
//            break;
//        case Ac::ColorRole:
//            setColor(value.value<QColor>());
//            break;
//        case Ac::VisibilityRole:
//            setVisibility(value.toBool());
//            break;
//        default:
//            return GraphicsObject::setData(value, role);
//        }
//        return true;
//    }

//protected:
//    GridLine(GridLinePrivate &dd, QObject *parent);

//private:
//    Q_DECLARE_PRIVATE(GridLine)
//};

//class GridLinePrivate : public GraphicsObjectPrivate
//{
//    Q_DECLARE_PUBLIC(GridLine)

//public:
//    qreal location;
//    QString label;
//    int priority;
//    QColor color;

//    GridLinePrivate(GridLine *q);

//    GraphicsParentPrivate *graphicsParent() const;
//    virtual void updateGraphicsItems() = 0;
//};

//class TimeGridLinePrivate;
//class AC_CORE_EXPORT TimeGridLine : public GridLine
//{
//    Q_OBJECT

//public:
//    enum { Type = Ac::TimeGridLineItem };

//    TimeGridLine(QObject *parent = 0);

//    // GridLine
//    bool isVisible() const;
//    void show();
//    void hide();

//    // IModelItem
//    int type() const;

//private:
//    Q_DECLARE_PRIVATE(TimeGridLine)
//};

//class PitchGridLinePrivate;
//class AC_CORE_EXPORT PitchGridLine : public GridLine
//{
//    Q_OBJECT

//public:
//    enum { Type = Ac::PitchGridLineItem };

//    PitchGridLine(QObject *parent = 0);

//    // GridLine
//    bool isVisible() const;
//    void show();
//    void hide();

//    // IModelItem
//    int type() const;

//private:
//    Q_DECLARE_PRIVATE(PitchGridLine)
//};

//class ControlGridLinePrivate;
//class AC_CORE_EXPORT ControlGridLine : public GridLine
//{
//    Q_OBJECT

//public:
//    enum { Type = Ac::ControlGridLineItem };

//    ControlGridLine(QObject *parent = 0);

//    // GridLine
//    bool isVisible() const;
//    void show();
//    void hide();

//    // IModelItem
//    int type() const;

//private:
//    Q_DECLARE_PRIVATE(ControlGridLine)
//};

//#endif // AC_GRIDLINE_H
