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

#ifndef AC_GRAPHICSNOTEITEM_H
#define AC_GRAPHICSNOTEITEM_H

#include <ac_scaledgraphicsitem.h>

class AcNote;

namespace Private {

class AcGraphicsNoteItemPrivate;

} // namespace Private

class AC_SCENE_EXPORT AcGraphicsNoteItem : public AcScaledGraphicsItem
{
    Q_OBJECT

public:
    AcGraphicsNoteItem(AcNote *note = 0, QObject *parent = 0);
    virtual ~AcGraphicsNoteItem();

    virtual QGraphicsItem *sceneItem(SceneType sceneType) const;

protected slots:
    virtual void updatePitchCurveProperty(int propertyIndex);
    virtual void updateVolumeCurveProperty(int propertyIndex);

protected:
    virtual void updateViewSettingsProperty(int propertyIndex);
    virtual void updateDatabaseObjectProperty(int propertyIndex);

private:
    Q_DISABLE_COPY(AcGraphicsNoteItem)
    Q_DECLARE_PRIVATE(Private::AcGraphicsNoteItem)
};

#endif // AC_GRAPHICSNOTEITEM_H
