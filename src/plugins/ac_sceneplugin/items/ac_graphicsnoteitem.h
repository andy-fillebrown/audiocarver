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

#include <QObject>
#include <ac_scene_global.h>

class AcNote;

namespace Private {

class AcGraphicsNoteItemData;

} // namespace Private

class AC_SCENE_EXPORT AcGraphicsNoteItem : public QObject
{
    Q_OBJECT

public:
    AcGraphicsNoteItem(AcNote *note = 0, QObject *parent = 0);
    virtual ~AcGraphicsNoteItem();

    virtual void setDatabaseObject(AcNote *note);

    bool isVisible() const;
    virtual void show();
    virtual void hide();

protected slots:
    virtual void updateNoteProperty(const QString &propertyName);

private:
    Q_DISABLE_COPY(AcGraphicsNoteItem)
    Private::AcGraphicsNoteItemData *d;
};

#endif // AC_GRAPHICSNOTEITEM_H
