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

#ifndef AC_GUI_SCOREOBJECT_H
#define AC_GUI_SCOREOBJECT_H

#include "mi_core_aggregator.h"

#include "ac_ichildentity.h"
#include "ac_iparententity.h"

#include <ac_isubentity.h>

#include <mi_imodellist.h>

class QGraphicsItem;

namespace Ac {
namespace Gui {

class ScoreObject : public Mi::Core::Aggregator
{
    QMap<int, QGraphicsItem*> _mainGraphicsItems;
    QMap<int, QGraphicsItem*> _unitXGraphicsItems;
    QMap<int, QGraphicsItem*> _unitYGraphicsItems;

protected:
    ScoreObject()
    {}

    virtual IAggregator *init();

    const QMap<int, QGraphicsItem*> &mainGraphicsItems() const
    {
        return _mainGraphicsItems;
    }

    void setMainGraphicsItem(int sceneType, QGraphicsItem *item)
    {
        _mainGraphicsItems.insert(sceneType, item);
    }

    const QMap<int, QGraphicsItem*> &unitXGraphicsItems() const
    {
        return _unitXGraphicsItems;
    }

    void setUnitXGraphicsItem(int sceneType, QGraphicsItem *item)
    {
        _unitXGraphicsItems.insert(sceneType, item);
    }

    const QMap<int, QGraphicsItem*> &unitYGraphicsItems() const
    {
        return _unitYGraphicsItems;
    }

    void setUnitYGraphicsItem(int sceneType, QGraphicsItem *item)
    {
        _unitYGraphicsItems.insert(sceneType, item);
    }

    class ParentEntity : public IParentEntity
    {
        friend class ScoreObject;

        ScoreObject *_aggregator;
    protected:
        ParentEntity(ScoreObject *aggregator)
            :   _aggregator(aggregator)
        {}

        virtual IAggregate *init();

        ScoreObject *a() const
        {
            return _aggregator;
        }

        // IParentEntity
        QList<ISubEntity*> subEntities(int sceneType) const
        {
            QList<ISubEntity*> sub_entities;
            switch (sceneType) {
            case PitchScene: {
                IModelItem *pitch_curve = query<IModelItem>(a())->findItem(PitchCurveItem);
                sub_entities.append(query<ISubEntity>(pitch_curve));
                break;
            }
            case ControlScene: {
                IModelList *control_curves = query<IModelItem>(a())->findList(ControlCurveItem);
                const int n = control_curves->count();
                for (int i = 0;  i < n;  ++i)
                    sub_entities.append(query<ISubEntity>(control_curves->at(i)));
                break;
            }
            default:
                break;
            }
            return sub_entities;
        }

        // IEntity
        QGraphicsItem *graphicsItem(int sceneType, int transformType) const
        {
            switch (transformType) {
            case MainTransform:
                return a()->mainGraphicsItems().value(sceneType);
            case UnitXTransform:
                return a()->unitXGraphicsItems().value(sceneType);
            case UnitYTransform:
                return a()->unitYGraphicsItems().value(sceneType);
            default:
                return 0;
            }
        }

        void update(int role);

        void highlight()
        {
            Q_ASSERT(false && "Not implemented yet.");
        }

        void unhighlight()
        {
            Q_ASSERT(false && "Not implemented yet.");
        }

        bool isVisible() const
        {
            Q_ASSERT(false && "Not implemented yet.");
            return false;
        }

        // IAggregate
        IAggregator *aggregator() const
        {
            return _aggregator;
        }
    };

    class ChildEntity : public IChildEntity
    {
        friend class ScoreObject;

        ScoreObject *_aggregator;

    protected:
        ChildEntity(ScoreObject *aggregator)
            :   _aggregator(aggregator)
        {}

        virtual IAggregate *init();

        ScoreObject *a() const
        {
            return _aggregator;
        }

        // IChildEntity
        IParentEntity *parentEntity() const
        {
            return query<IParentEntity>(query<IModelItem>(a())->parent());
        }

        // IAggregate
        IAggregator *aggregator() const
        {
            return _aggregator;
        }
    };

    // IAggregator
    IAggregate *createAggregate(int interfaceType)
    {
        switch (interfaceType) {
        case I::IParentEntity:
            return appendAggregate((new ParentEntity(this))->init());
        case I::IChildEntity:
            return appendAggregate((new ChildEntity(this))->init());
        default:
            return 0;
        }
    }
};

} // namespace Gui
} // namespace Ac

#endif // AC_GUI_SCOREOBJECT_H
