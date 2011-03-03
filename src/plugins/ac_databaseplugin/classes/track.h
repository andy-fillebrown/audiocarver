/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2010 Andrew Fillebrown.
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

#ifndef AC_TRACK_H
#define AC_TRACK_H

#include <databaseplugin/classes/list.h>

namespace AudioCarver {

namespace Internal {
class TrackPrivate;
} // namespace Internal

class Track : public Database::Object
{
    Q_OBJECT

    Q_PROPERTY(Database::List* notes READ notes)
    Q_PROPERTY(bool visible READ isVisible WRITE setVisibility)
    Q_PROPERTY(qreal volume READ volume WRITE setVolume)

public:
    Track(QObject *parent = 0);
    virtual ~Track();

    bool isVisible() const;
    void setVisibility(bool visible);

    qreal volume() const;
    void setVolume(qreal volume);

    Database::List *notes() const;

private:
    Q_DISABLE_COPY(Track)
    Internal::TrackPrivate *d;
};

} // namespace AudioCarver

#endif // AC_TRACK_H
