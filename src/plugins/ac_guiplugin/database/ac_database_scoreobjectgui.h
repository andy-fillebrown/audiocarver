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

#ifndef AC_DATABASE_SCOREOBJECTGUI_H
#define AC_DATABASE_SCOREOBJECTGUI_H

#include "ac_database_scoreobject.h"

#include "ac_ichildentity.h"
#include "ac_iparententity.h"

#include <ac_isubentity.h>

class QGraphicsItem;

namespace Database {

namespace ScoreObjectGui
{
    void parentChanged(ScoreObject *scoreObject);

    class ParentEntity : public IParentEntity
    {
        ScoreObject *_aggregator;
        QMap<int, QGraphicsItem*> _mainGraphicsItems;
        QMap<int, QGraphicsItem*> _unitXGraphicsItems;
        QMap<int, QGraphicsItem*> _unitYGraphicsItems;

    public:
        ParentEntity(ScoreObject *aggregator)
            :   _aggregator(aggregator)
        {}

        virtual IAggregate *init();

        const QMap<int, QGraphicsItem*> &mainGraphicsItems() const
        {
            return _mainGraphicsItems;
        }

        const QMap<int, QGraphicsItem*> &unitXGraphicsItems() const
        {
            return _unitXGraphicsItems;
        }

        const QMap<int, QGraphicsItem*> &unitYGraphicsItems() const
        {
            return _unitYGraphicsItems;
        }

    protected:
        ScoreObject *a() const
        {
            return _aggregator;
        }

        void setMainGraphicsItem(int sceneType, QGraphicsItem *item)
        {
            _mainGraphicsItems.insert(sceneType, item);
        }

        void setUnitXGraphicsItem(int sceneType, QGraphicsItem *item)
        {
            _unitXGraphicsItems.insert(sceneType, item);
        }

        void setUnitYGraphicsItem(int sceneType, QGraphicsItem *item)
        {
            _unitYGraphicsItems.insert(sceneType, item);
        }

        // IParentEntity
        QList<ISubEntity*> subEntities(int sceneType) const
        {
            QList<ISubEntity*> sub_entities;
            switch (sceneType) {
            case Ac::PitchScene:
                sub_entities.append(query<ISubEntity>(a()->pitchCurve()));
                break;
            case Ac::ControlScene: {
                ObjectList *control_curves = a()->controlCurves();
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
        ScoreObject *_aggregator;

    public:
        ChildEntity(ScoreObject *aggregator)
            :   _aggregator(aggregator)
        {}

        virtual IAggregate *init();

    protected:
        ScoreObject *a() const
        {
            return _aggregator;
        }

        // IChildEntity
        IParentEntity *parentEntity() const
        {
            return query<IParentEntity>(a()->parent());
        }

        // IAggregate
        IAggregator *aggregator() const
        {
            return _aggregator;
        }
    };
}

} // namespace Database

#endif // AC_DATABASE_SCOREOBJECTGUI_H
