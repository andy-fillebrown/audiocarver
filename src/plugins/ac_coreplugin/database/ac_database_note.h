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

#ifndef AC_DATABASE_NOTE_H
#define AC_DATABASE_NOTE_H

#include "ac_database_scoreobject.h"

namespace Database {

class AC_CORE_EXPORT Note : public ScoreObject
{
    friend class ObjectFactory;

    Q_IAGGREGATOR_DERIVED(Note, ScoreObject)

public:
    // AbstractScoreObject
    qreal length() const
    {
        const PointList &pts = pitchCurve()->points();
        return pts.last().pos.x() - pts.first().pos.x();
    }

protected:
    // IModelItem
    class AC_CORE_EXPORT ModelItem : public Base::ModelItem
    {
        Q_IMODELITEM_DERIVED
        Q_IMODELITEM_DERIVED__ITEMTYPE(Ac::NoteItem)
    };

    // IAggregator
    IAggregate *createAggregate(int interfaceType)
    {
        switch (interfaceType) {
        case I::IModelItem:
            return Q_NEW_AGGREGATE(ModelItem);
        default:
            return Base::createAggregate(interfaceType);
        }
    }
};

} // namespace Database

//class AC_CORE_EXPORT Note : public AbstractScoreDataObject
//{
//public:
//    enum { Type = Ac::NoteItem };

//    explicit Note(QObject *parent = 0);

//    Track *track() const;

//    void setColor(const QColor &color);

//    // ScoreObject
//    qreal length() const;
//    void updatePoints();

//    // IEntity
//    bool isSubEntity() const { return false; }
//    const PointList &points() const;
//    void pushPoints(const PointList &points);
//    void popPoints();
//    void setPoints(const PointList &points);
//    void highlight();
//    void unhighlight();
//    bool intersects(const QRectF &) const { return false; }
//    bool isVisible() const;

//    QList<IEntity*> subEntities(int sceneType) const;

//    // IModelItem
//    int type() const { return Type; }

//    QVariant data(int role) const
//    {
//        if (Ac::VisibilityRole == role)
//            return isVisible();
//        return ScoreObject::data(role);
//    }

//    // IUnknown
//    void *query(int type) const
//    {
//        switch (type) {
//        case Ac::EntityInterface:
//            return objectToInterface_cast<IEntity>(this);
//        default:
//            return ScoreObject::query(type);
//        }
//    }

//private:
//    Q_DECLARE_PRIVATE(Note)
//};

#endif // AC_DATABASE_NOTE_H
