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
class IPlayCursor;
class ProjectSettings;
class Track;
class ViewSettings;

class QGraphicsLineItem;

class QTimer;

class Score;
class ScorePrivate : public ScoreObjectPrivate
{
public:
    qreal length;
    qreal startTime;
    qreal playCursorTime;
    ObjectTList<Track> *tracks;
    GridSettings *gridSettings;
    ViewSettings *viewSettings;
    ProjectSettings *projectSettings;
    IPlayCursor *playCursorImplementation;
    QGraphicsLineItem *timeLabelPlayCursor;
    QGraphicsLineItem *pitchPlayCursor;
    QGraphicsLineItem *controlPlayCursor;
    QTimer *playCursorTimer;

    ScorePrivate(Score *q);
    void init();
    ~ScorePrivate();

    void updateGraphicsParent() {}
    void updateLength();
    void setPlayCursorTime(qreal time);
};

class AC_CORE_EXPORT Score : public ScoreObject
{
    Q_OBJECT
    Q_PROPERTY(qreal length READ length WRITE setLength)
    Q_PROPERTY(qreal startTime READ startTime WRITE setStartTime)

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
    qreal startTime() const;
    void setStartTime(qreal time);

    qreal playCursorTime() const;
    void setPlaybackTime(qreal time);
    void highlightPlayCursor();
    void unhighlightPlayCursor();

    // IModelItem
    int type() const { return Type; }
    int modelItemCount() const { return ModelItemCount; }
    int modelItemIndex(const IModelItem *item) const;
    IModelItem *modelItemAt(int i) const;
    IModelItem *findModelItem(int type) const;
    IModelItem *findModelItemList(int type) const;

    int persistentRoleAt(int i) const
    {
        switch (i - staticMetaObject.propertyOffset()) {
        case 0:
            return Ac::LengthRole;
        case 1:
            return Ac::StartTimeRole;
        default:
            return ScoreObject::persistentRoleAt(i);
        }
    }

    QVariant data(int role) const;
    bool setData(const QVariant &value, int role);

signals:
    void aboutToBeReset();
    void reset();

private slots:
    void updatePlayCursor();

private:
    Q_DECLARE_PRIVATE(Score)

    friend class GridSettingsPrivate;
    friend class TrackPrivate;
};

#endif // AC_SCORE_H
