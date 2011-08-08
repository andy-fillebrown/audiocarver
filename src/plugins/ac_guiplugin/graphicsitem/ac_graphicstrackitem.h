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

#ifndef AC_GRAPHICSTRACKITEM_H
#define AC_GRAPHICSTRACKITEM_H

#include <ac_graphicsitem.h>

class AcTrack;
class QGraphicsItemGroup;

class AcGraphicsTrackItemPrivate;

class AcGraphicsTrackItem : public AcGraphicsItem
{
    Q_OBJECT

public:
    AcGraphicsTrackItem(AcTrack *track = 0, QObject *parent = 0);

    ~AcGraphicsTrackItem()
    {}

    QGraphicsItem *sceneItem(SceneType sceneType) const;

protected:
    void updateDataObject(int i, const QVariant &value);

private:
    Q_DISABLE_COPY(AcGraphicsTrackItem)
    Q_DECLARE_PRIVATE(AcGraphicsTrackItem)
};

#endif // AC_GRAPHICSTRACKITEM_H
