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

#ifndef ACTRACK_H
#define ACTRACK_H

#include <acscoreobject.h>

#include <QColor>

class Note;
class Score;

class TrackPrivate;
class AC_CORE_EXPORT Track : public ScoreObject
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)
    Q_PROPERTY(QString instrument READ instrument WRITE setInstrument)

public:
    enum { ModelItemCount = ScoreObject::ModelItemCount + 1 };

    explicit Track(QObject *parent = 0);

    qreal length() const;

    const QColor &color() const;
    void setColor(const QColor &color);

    const QString &instrument() const;
    void setInstrument(const QString &instrument);

    Score *parent() const;

    ObjectList<Note> *notes() const;

    // IModelItem
    ItemType type() const { return TrackItem; }
    int modelItemCount() const { return ModelItemCount; }
    int modelItemIndex(IModelItem *item) const;
    IModelItem *modelItemAt(int i) const;
    IModelItem *findModelItemList(ItemType type) const;
    QVariant data(int role) const;
    bool setData(const QVariant &value, int role);

private:
    Q_DISABLE_COPY(Track)
    Q_DECLARE_PRIVATE(Track)
};

#endif // ACTRACK_H
