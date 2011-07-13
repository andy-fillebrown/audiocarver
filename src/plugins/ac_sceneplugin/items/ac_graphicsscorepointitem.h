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

#ifndef AC_GRAPHICSSCOREPOINTITEM_H
#define AC_GRAPHICSSCOREPOINTITEM_H

#include <ac_graphicspointitem.h>

class AcPoint;

namespace Private {

class AcGraphicsScorePointItemPrivate;

} // namespace Private

class AC_SCENE_EXPORT AcGraphicsScorePointItem : public AcGraphicsPointItem
{
    Q_OBJECT

public:
    AcGraphicsScorePointItem(AcPoint *point = 0, QObject *parent = 0);
    virtual ~AcGraphicsScorePointItem();

    virtual QGraphicsItem *sceneItem(SceneType sceneType) const;

protected:
    virtual void updateDatabaseObjectProperty(const QString &propertyName);

private:
    Q_DISABLE_COPY(AcGraphicsScorePointItem)
    Q_DECLARE_PRIVATE(Private::AcGraphicsScorePointItem)
};

#endif // AC_GRAPHICSSCOREPOINTITEM_H
