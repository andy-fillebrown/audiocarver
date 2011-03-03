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

#ifndef AC_SCENE_TRACK_H
#define AC_SCENE_TRACK_H

#include <QtCore/QObject>

namespace AudioCarver {
namespace Scene {

class Track : public QObject
{
    Q_OBJECT

public:
    Track(QObject *parent = 0);
    virtual ~Track();
};

} // namespace Scene
} // namespace AudioCarver

#endif // AC_SCENE_TRACK_H
