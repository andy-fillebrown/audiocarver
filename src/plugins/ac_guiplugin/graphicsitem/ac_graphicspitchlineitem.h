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

#ifndef AC_GRAPHICSPITCHLINEITEM_H
#define AC_GRAPHICSPITCHLINEITEM_H

#include <ac_graphicsgridlineitem.h>

class AcGraphicsPitchLineItemPrivate;

class AcGraphicsPitchLineItem : public AcGraphicsGridLineItem
{
    Q_OBJECT

public:
    AcGraphicsPitchLineItem(AcGridLine *gridLine = 0, QObject *parent = 0);
    ~AcGraphicsPitchLineItem();

    QGraphicsItem *sceneItem(SceneType sceneType) const;

protected:
    void updateViewSettings(int i, const QVariant &value);
    void updateDataObject(int i, const QVariant &value);

protected slots:
    virtual void updateScore(int i, const QVariant &value);

private:
    Q_DISABLE_COPY(AcGraphicsPitchLineItem)
    Q_DECLARE_PRIVATE(AcGraphicsPitchLineItem)
};

#endif // AC_GRAPHICSPITCHLINEITEM_H
