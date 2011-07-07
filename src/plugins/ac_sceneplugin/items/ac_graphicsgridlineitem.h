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

#ifndef AC_GRAPHICSGRIDLINEITEM_H
#define AC_GRAPHICSGRIDLINEITEM_H

#include <QObject>
#include <ac_scene_global.h>

class AcGridLine;

namespace Private {

class AcGraphicsGridLineItemData;

} // namespace Private

class AC_SCENE_EXPORT AcGraphicsGridLineItem : public QObject
{
    Q_OBJECT

public:
    AcGraphicsGridLineItem(AcGridLine *gridLine = 0, QObject *parent = 0);
    virtual ~AcGraphicsGridLineItem();

    virtual bool isVertical() const = 0;

    AcGridLine *gridLine() const;
    virtual void setGridLine(AcGridLine *gridLine);

protected slots:
    virtual void updateFontSettingsProperty(const QString &propertyName) = 0;
    virtual void updateViewSettingsProperty(const QString &propertyName) = 0;
    virtual void updateGridLineProperty(const QString &propertyName);

private:
    Q_DISABLE_COPY(AcGraphicsGridLineItem)
    Private::AcGraphicsGridLineItemData *d;
};

#endif // AC_GRAPHICSGRIDLINEITEM_H
