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

#ifndef ACSCORE_H
#define ACSCORE_H

#include <acscoreobject.h>

class Track;

class QGraphicsItem;

class Score;
class ScorePrivate : public ScoreObjectPrivate

{
public:
    qreal length;
    ObjectList<Track> *tracks;

    ScorePrivate(Score *q);
    void init();
    ~ScorePrivate();

    void updateLength();
};

class AC_CORE_EXPORT Score : public ScoreObject
{
    Q_OBJECT
    Q_PROPERTY(qreal length READ length WRITE setLength)

public:
    enum { ModelItemCount = ScoreObject::ModelItemCount + 1 };

    explicit Score(QObject *parent = 0);

    qreal length() const;
    void setLength(qreal length);

    ObjectList<Track> *tracks() const;

    QGraphicsItem *sceneItem(Ac::SceneType type) const;

    void setModel(Model *model);

    // IModelItem
    Ac::ItemType type() const { return Ac::ScoreItem; }
    int modelItemCount() const { return ModelItemCount; }
    int modelItemIndex(IModelItem *item) const;
    IModelItem *modelItemAt(int i) const;
    IModelItem *findModelItemList(Ac::ItemType type) const;
    bool setData(const QVariant &value, int role);

private:
    Q_DISABLE_COPY(Score)
    Q_DECLARE_PRIVATE(Score)
};

#endif // ACSCORE_H
