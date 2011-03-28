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

#include "database.h"

#include <ac_databaseplugin/classes/fcurve.h>
#include <ac_databaseplugin/classes/fpoint.h>
#include <ac_databaseplugin/classes/note.h>
#include <ac_databaseplugin/classes/score.h>
#include <ac_databaseplugin/classes/track.h>
#include <ac_databaseplugin/classes/tuning.h>
#include <databaseplugin/classes/list.h>

#include <QtCore/QFile>
#include <QtCore/QXmlStreamReader>
#include <QtCore/QXmlStreamWriter>

using namespace AudioCarver;
using namespace AudioCarver::Internal;

namespace AudioCarver {
namespace Internal {

class DatabaseImplData
{
public:
    DatabaseImpl *q;
    Score *score;
    QString fileName;

    DatabaseImplData(DatabaseImpl *q)
        :   q(q)
        ,   score(new Score(q))
    {
        Database::Object *tuning = score->createObject("Tuning");

        Track *track = qobject_cast<Track*>(score->createObject("Track"));
        track->setTuning(tuning);

        FCurve *pitchCurve = qobject_cast<FCurve*>(score->createObject("FCurve"));
        pitchCurve->appendPoint(FPoint(0.000001, 0));
        pitchCurve->appendPoint(FPoint(1, 1));

        Note *note = qobject_cast<Note*>(track->createObject("Note"));
        note->setPitchCurve(pitchCurve);
    }
};

} // namespace Internal
} // namespace AudioCarver

DatabaseImpl::DatabaseImpl()
    :   d(new DatabaseImplData(this))
{}

DatabaseImpl::~DatabaseImpl()
{
    delete d;
}

const QString &DatabaseImpl::fileExtension() const
{
    static QString ext = QString::fromLatin1(".ac");
    return ext;
}

const QString &DatabaseImpl::fileFilter() const
{
    static QString filter = QString::fromLatin1("AudioCarver (*%1)").arg(fileExtension());
    return filter;
}

const QString &DatabaseImpl::fileName() const
{
    return d->fileName;
}

void DatabaseImpl::clear()
{
    d->score->clear();
}

void DatabaseImpl::read(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly))
        return;

    QXmlStreamReader in(&file);
    while (in.readNext() != QXmlStreamReader::StartElement && !in.atEnd());

    if (d->score->read(in))
        d->fileName = fileName;
}

void DatabaseImpl::write(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly))
        return;

    QXmlStreamWriter out(&file);
    out.setAutoFormatting(true);

    d->score->write(out);
    file.write("\n");

    d->fileName = fileName;
}
