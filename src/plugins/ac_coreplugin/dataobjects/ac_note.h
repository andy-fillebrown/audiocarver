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

#ifndef AC_NOTE_H
#define AC_NOTE_H

#include <ac_ientity.h>

#include <ac_scoreobject.h>

class Track;

class NotePrivate;
class AC_CORE_EXPORT Note : public ScoreObject
        ,   public IEntity
{
    Q_OBJECT
    Q_PROPERTY(qreal length READ length WRITE setLength)

public:
    explicit Note(QObject *parent = 0);

    qreal length() const;
    void setLength(qreal length);

    Track *track() const;

    // IEntity
    bool isSubEntity() const { return false; }
    PointList points() const;
    void setPoints(const PointList &points, Ac::DragState dragState = Ac::NotDragging);
    void highlight();
    void unhighlight();

    // IModelItem
    Ac::ItemType type() const { return Ac::NoteItem; }
    bool setData(const QVariant &value, int role);

    // IUnknown
    void *query(int type) const
    {
        switch (type) {
        case Ac::EntityInterface:
            return Q_I(IEntity);
        default:
            return ScoreObject::query(type);
        }
    }

private:
    Q_DISABLE_COPY(Note)
    Q_DECLARE_PRIVATE(Note)
};

#endif // AC_NOTE_H
