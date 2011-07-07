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

class AcGraphicsBarLineItemData;

} // namespace Private

class AC_SCENE_EXPORT AcGraphicsBarLineItem : public AcGraphicsGridLineItem
{
public:
    AcGraphicsBarLineItem(AcBarLine *barLine = 0, QObject *parent = 0);
    virtual ~AcGraphicsBarLineItem();

    virtual bool isVertical() const { return true; }

    virtual void setGridLine(AcGridLine *barLine);

protected:
    virtual void updateFontSettingsProperty(const QString &propertyName);
    virtual void updateViewSettingsProperty(const QString &propertyName);
    virtual void updateGridLineProperty(const QString &propertyName);

private:
    Q_DISABLE_COPY(AcGraphicsBarLineItem)
    Private::AcGraphicsBarLineItemData *d;
};

#endif // AC_GRAPHICSBARLINEITEM_H
