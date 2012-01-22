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

#ifndef AC_SCORE_H
#define AC_SCORE_H

#include <ac_scoreobject.h>

class GridSettings;
class ProjectSettings;
class Track;
class ViewSettings;

class QGraphicsItem;

class Score;
class ScorePrivate : public ScoreObjectPrivate
{
public:
    qreal length;
    ObjectTList<Track> *tracks;
    GridSettings *gridSettings;
    ViewSettings *viewSettings;
    ProjectSettings *projectSettings;

    ScorePrivate(Score *q);
    void init();
    ~ScorePrivate();

    void updateGraphicsParent() {}
    void updateLength();
};

class AC_CORE_EXPORT Score : public ScoreObject
{
    Q_OBJECT
    Q_PROPERTY(qreal length READ length WRITE setLength)

public:
    enum { Type = Ac::ScoreItem };
    enum { ModelItemCount = ScoreObject::ModelItemCount + 4 };

    explicit Score(QObject *parent = 0);

    static Score *instance();

    ObjectTList<Track> *tracks() const;
    GridSettings *gridSettings() const;
    ViewSettings *viewSettings() const;
    ProjectSettings *projectSettings() const;

    QGraphicsItem *sceneItem(int type) const;

    void clear();

    // Properties
    qreal length() const;
    void setLength(qreal length);

    // IModelItem
    int type() const { return Type; }
    int modelItemCount() const { return ModelItemCount; }
    int modelItemIndex(const IModelItem *item) const;
    IModelItem *modelItemAt(int i) const;
    IModelItem *findModelItem(int type) const;
    IModelItem *findModelItemList(int type) const;

    int persistentRoleAt(int i) const
    {
        if (staticMetaObject.propertyOffset() == i)
            return Ac::LengthRole;
        return ScoreObject::persistentRoleAt(i);
    }

    bool setData(const QVariant &value, int role);

signals:
    void aboutToBeReset();
    void reset();

private:
    Q_DECLARE_PRIVATE(Score)

    friend class GridSettingsPrivate;
    friend class TrackPrivate;
};

#endif // AC_SCORE_H
