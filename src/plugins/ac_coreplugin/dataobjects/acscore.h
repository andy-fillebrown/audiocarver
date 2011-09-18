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

class ScorePrivate;
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

    void setModel(Model *model);

    // IModelItem
    ItemType type() const { return ScoreItem; }
    int modelItemCount() const { return ModelItemCount; }
    int modelItemIndex(IModelItem *item) const;
    IModelItem *modelItemAt(int i) const;
    IModelItem *findModelItemList(ItemType type) const;
    bool setData(const QVariant &value, int role);

private:
    Q_DISABLE_COPY(Score)
    Q_DECLARE_PRIVATE(Score)
};

#endif // ACSCORE_H
