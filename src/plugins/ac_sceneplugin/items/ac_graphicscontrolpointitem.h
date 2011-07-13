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

#ifndef AC_GRAPHICSCONTROLPOINTITEM_H
#define AC_GRAPHICSCONTROLPOINTITEM_H

#include <ac_graphicspointitem.h>

class AcPoint;

namespace Private {

class AcGraphicsControlPointItemPrivate;

} // namespace Private

class AC_SCENE_EXPORT AcGraphicsControlPointItem : public AcGraphicsPointItem
{
    Q_OBJECT

public:
    AcGraphicsControlPointItem(AcPoint *point = 0, QObject *parent = 0);
    virtual ~AcGraphicsControlPointItem();

    virtual QGraphicsItem *sceneItem(SceneType sceneType) const;

protected:
    virtual void updateDatabaseObjectProperty(int propertyIndex);

private:
    Q_DISABLE_COPY(AcGraphicsControlPointItem)
    Q_DECLARE_PRIVATE(Private::AcGraphicsControlPointItem)
};

#endif // AC_GRAPHICSCONTROLPOINTITEM_H
