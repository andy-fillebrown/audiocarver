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

#ifndef AC_SCALEDGRAPHICSITEM_H
#define AC_SCALEDGRAPHICSITEM_H

#include <ac_graphicsitem.h>

class AcViewSettings;

namespace Private {

class AcScaledGraphicsItemData : public AcGraphicsItemData
{
public:
    AcScaledGraphicsItemData() {}
    virtual ~AcScaledGraphicsItemData() {}

    const AcViewSettings *viewSettings() const;
};

class AcScaledGraphicsItemPrivate;

} // namespace Private

class AC_SCENE_EXPORT AcScaledGraphicsItem : public AcGraphicsItem
{
    Q_OBJECT

protected:
    AcScaledGraphicsItem(Private::AcScaledGraphicsItemData &dd, QObject *parent = 0);

public:
    virtual ~AcScaledGraphicsItem();

protected slots:
    virtual void updateViewSettingsProperty(int propertyIndex) = 0;

private:
    Q_DISABLE_COPY(AcScaledGraphicsItem)
    Q_DECLARE_PRIVATE(Private::AcScaledGraphicsItem)
};

#endif // AC_SCALEDGRAPHICSITEM_H
