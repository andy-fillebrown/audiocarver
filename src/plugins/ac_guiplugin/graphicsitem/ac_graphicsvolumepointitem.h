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

#ifndef AC_GRAPHICSVOLUMEPOINTITEM_H
#define AC_GRAPHICSVOLUMEPOINTITEM_H

#include <ac_graphicspointitem.h>

class AcPoint;

class AcGraphicsVolumePointItemPrivate;

class AcGraphicsVolumePointItem : public AcGraphicsPointItem
{
    Q_OBJECT

public:
    AcGraphicsVolumePointItem(AcPoint *point = 0, QObject *parent = 0);

    ~AcGraphicsVolumePointItem()
    {}

    virtual QGraphicsItem *sceneItem(SceneType sceneType) const;

protected:
    void updateViewSettings(int i, const QVariant &value);
    void updateDataObject(int i, const QVariant &value);

private:
    Q_DISABLE_COPY(AcGraphicsVolumePointItem)
    Q_DECLARE_PRIVATE(AcGraphicsVolumePointItem)
};

#endif // AC_GRAPHICSVOLUMEPOINTITEM_H
