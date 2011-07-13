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

#ifndef AC_GRAPHICSTUNINGLINEITEM_H
#define AC_GRAPHICSTUNINGLINEITEM_H

#include <ac_graphicsgridlineitem.h>

class AcTuningLine;

namespace Private {

class AcGraphicsTuningLineItemPrivate;

} // namespace Private

class AC_SCENE_EXPORT AcGraphicsTuningLineItem : public AcGraphicsGridLineItem
{
    Q_OBJECT

public:
    AcGraphicsTuningLineItem(AcTuningLine *tuningLine = 0, QObject *parent = 0);
    virtual ~AcGraphicsTuningLineItem();

    virtual QGraphicsItem *sceneItem(SceneType sceneType) const;

protected:
    virtual void updateViewSettingsProperty(int propertyIndex);
    virtual void updateGridLineProperty(int propertyIndex);

protected slots:
    virtual void updateScoreProperty(int propertyIndex);

private:
    Q_DISABLE_COPY(AcGraphicsTuningLineItem)
    Q_DECLARE_PRIVATE(Private::AcGraphicsTuningLineItem)
};

#endif // AC_GRAPHICSTUNINGLINEITEM_H
