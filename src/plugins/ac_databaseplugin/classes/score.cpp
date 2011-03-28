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

#include "score.h"

#include "fcurve.h"
#include "note.h"
#include "track.h"
#include "tuning.h"

#include <ac_databaseplugin/settings/gridsettings.h>
#include <databaseplugin/classes/list.h>

using namespace AudioCarver;
using namespace AudioCarver::Internal;

namespace AudioCarver {
namespace Internal {

class ScoreData
{
public:
    Database::List *settings;
    Database::List *tunings;
    Database::List *curves;
    Database::List *tracks;

    GridSettings *gridSettings;

    ScoreData(Score *q)
        :   settings(new Database::ConstantList(q, q->propertyIndex("settings")))
        ,   tunings(new Database::List(q, q->propertyIndex("tunings")))
        ,   curves(new Database::List(q, q->propertyIndex("curves")))
        ,   tracks(new Database::List(q, q->propertyIndex("tracks")))
        ,   gridSettings(new GridSettings(q))
    {
        settings->append(gridSettings);
    }

    ~ScoreData()
    {
        delete tracks;
        delete curves;
        delete tunings;
        delete settings;
    }
};

} // namespace Internal
} // namespace AudioCarver

static Score *instance = 0;

Score::Score(QObject *parent)
    :   Root(parent)
    ,   d(new ScoreData(this))
{
    ::instance = this;
}

Score::~Score()
{
    delete d;
}

Score *Score::instance()
{
    return ::instance;
}

Database::List *Score::settings() const
{
    return d->settings;
}

Database::List *Score::tunings() const
{
    return d->tunings;
}

Database::List *Score::curves() const
{
    return d->curves;
}

Database::List *Score::tracks() const
{
    return d->tracks;
}

void Score::clear()
{
    d->tracks->deleteAll();
    d->curves->deleteAll();
}

QString &Score::normalizeClassName(QString &className) const
{
    return className.remove("AudioCarver::");
}

Database::Object *Score::createObject(const QString &className)
{
    if (className == "FCurve") {
        FCurve *fcurve = new FCurve(this);
        d->curves->append(fcurve);
        return fcurve;
    }
    if (className == "Tuning") {
        Tuning *tuning = new Tuning(this);
        d->tunings->append(tuning);
        return tuning;
    }
    if (className == "Track") {
        Track *track = new Track(this);
        d->tracks->append(track);
        return track;
    }
    return 0;
}

Database::Object *Score::findObject(const QString &className) const
{
    if (className == "GridSettings")
        return d->gridSettings;
    return 0;
}
