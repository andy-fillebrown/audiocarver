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

#include "score.h"

#include "note.h"
#include "track.h"

using namespace AudioCarver;
using namespace AudioCarver::Internal;

namespace AudioCarver {
namespace Internal {

class ScorePrivate
{
public:
    Database::ObjectList *curves;
    Database::ObjectList *tracks;

    ScorePrivate()
        :   curves(new Database::ObjectList)
        ,   tracks(new Database::ObjectList)
    {
        Q_CHECK_PTR(curves);
        Q_CHECK_PTR(tracks);
    }

    ~ScorePrivate()
    {
        delete tracks;  tracks = 0;
        delete curves;  curves = 0;
    }
};

} // namespace Internal
} // namespace AudioCarver

Score::Score(QObject *parent)
    :   RootObject(parent)
    ,   d(new ScorePrivate)
{
    Q_CHECK_PTR(d);
}

Score::~Score()
{
    delete d;  d = 0;
}

QString &Score::normalizeClassName(QString &className) const
{
    return className.remove("AudioCarver::");
}

Database::Object *Score::createObject(const QString &className) const
{
    if (className == "Note")
        return new Note;

    if (className == "FCurve")
        return new FCurve;

    if (className == "Track")
        return new Track;

    return 0;
}

Database::ObjectList *Score::curves() const
{
    return d->curves;
}

Database::ObjectList *Score::tracks() const
{
    return d->tracks;
}
