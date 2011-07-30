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

#ifndef AC_GRAPHICSBARLINEITEM_H
#define AC_GRAPHICSBARLINEITEM_H

#include <ac_graphicsgridlineitem.h>

class AcBarLine;

namespace Private {

class AcGraphicsBarLineItemPrivate;

} // namespace Private

class AcGraphicsBarLineItem : public AcGraphicsGridLineItem
{
    Q_OBJECT

public:
    AcGraphicsBarLineItem(AcBarLine *barLine = 0, QObject *parent = 0);
    virtual ~AcGraphicsBarLineItem();

    virtual QGraphicsItem *sceneItem(SceneType sceneType) const;

protected:
    virtual void updateViewSettingsProperty(int propertyIndex);
    virtual void updateDatabaseObjectProperty(int propertyIndex);

private:
    Q_DISABLE_COPY(AcGraphicsBarLineItem)
    Q_DECLARE_PRIVATE(Private::AcGraphicsBarLineItem)
};

#endif // AC_GRAPHICSBARLINEITEM_H
