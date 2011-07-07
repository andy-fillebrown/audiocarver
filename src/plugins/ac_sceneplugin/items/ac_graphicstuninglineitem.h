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

class AcGraphicsTuningLineItemData;

} // namespace Private

class AC_SCENE_EXPORT AcGraphicsTuningLineItem : public AcGraphicsGridLineItem
{
public:
    AcGraphicsTuningLineItem(AcTuningLine *tuningLine = 0);
    virtual ~AcGraphicsTuningLineItem();

    virtual bool isVertical() const { return false; }

    virtual void setGridLine(AcGridLine *gridLine);

protected:
    virtual void updateFontSettingsProperty(const QString &propertyName);
    virtual void updateViewSettingsProperty(const QString &propertyName);
    virtual void updateGridLineProperty(const QString &propertyName);

private:
    Q_DISABLE_COPY(AcGraphicsTuningLineItem)
    Private::AcGraphicsTuningLineItemData *d;
};

#endif // AC_GRAPHICSTUNINGLINEITEM_H
