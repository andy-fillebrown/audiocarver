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

#ifndef AC_GRAPHICSTRACKITEM_H
#define AC_GRAPHICSTRACKITEM_H

#include <QObject>
#include <ac_scene_global.h>

class AcTrack;
class QGraphicsItemGroup;

namespace Private {

class AcGraphicsTrackItemData
{
public:
    AcTrack *track;
    QGraphicsItemGroup *scoreGroup;
    QGraphicsItemGroup *controlGroup;

    AcGraphicsTrackItemData();
    virtual ~AcGraphicsTrackItemData();
};

class AcGraphicsTrackItemPrivate;

} // namespace Private

class AC_SCENE_EXPORT AcGraphicsTrackItem : public QObject
{
    Q_OBJECT

public:
    AcGraphicsTrackItem(AcTrack *track = 0, QObject *parent = 0);
    virtual ~AcGraphicsTrackItem();

    virtual void setDatabaseObject(AcTrack *track);

    bool isVisible() const;
    virtual void show();
    virtual void hide();

protected slots:
    virtual void updateTrackProperty(const QString &propertyName);

private:
    Q_DISABLE_COPY(AcGraphicsTrackItem)
    Q_DECLARE_PRIVATE(Private::AcGraphicsTrackItem)
    Private::AcGraphicsTrackItemData *d_ptr;
};

#endif // AC_GRAPHICSTRACKITEM_H
