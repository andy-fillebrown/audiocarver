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

#ifndef AC_GRAPHICSVOLUMELINEITEM_H
#define AC_GRAPHICSVOLUMELINEITEM_H

#include <ac_graphicsgridlineitem.h>

class AcGraphicsVolumeLineItemPrivate;

class AcGraphicsVolumeLineItem : public AcGraphicsGridLineItem
{
    Q_OBJECT

public:
    AcGraphicsVolumeLineItem(AcGridLine *gridLine = 0, QObject *parent = 0);
    virtual ~AcGraphicsVolumeLineItem();

    virtual QGraphicsItem *sceneItem(SceneType sceneType) const;

protected:
    virtual void updateViewSettings(int i);
    virtual void updateDataObject(int i);

protected slots:
    virtual void updateScore(int i);

private:
    Q_DISABLE_COPY(AcGraphicsVolumeLineItem)
    Q_DECLARE_PRIVATE(AcGraphicsVolumeLineItem)
};

#endif // AC_GRAPHICSVOLUMELINEITEM_H
