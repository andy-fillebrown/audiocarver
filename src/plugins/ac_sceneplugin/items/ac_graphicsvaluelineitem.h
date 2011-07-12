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

#ifndef AC_GRAPHICSVALUELINEITEM_H
#define AC_GRAPHICSVALUELINEITEM_H

#include <ac_graphicsgridlineitem.h>

class AcValueLine;

namespace Private {

class AcGraphicsValueLineItemPrivate;

} // namespace Private

class AC_SCENE_EXPORT AcGraphicsValueLineItem : public AcGraphicsGridLineItem
{
    Q_OBJECT

public:
    AcGraphicsValueLineItem(AcValueLine *valueLine = 0, QObject *parent = 0);
    virtual ~AcGraphicsValueLineItem();

    virtual void setDatabaseObject(AcGridLine *gridLine);

protected:
    virtual void updateViewSettingsProperty(const QString &propertyName);
    virtual void updateGridLineProperty(const QString &propertyName);

protected slots:
    virtual void updateScoreProperty(const QString &propertyName);

private:
    Q_DISABLE_COPY(AcGraphicsValueLineItem)
    Q_DECLARE_PRIVATE(Private::AcGraphicsValueLineItem)
};

#endif // AC_GRAPHICSVALUELINEITEM_H
