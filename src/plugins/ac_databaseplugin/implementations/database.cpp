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

#include "database.h"

#include <classes/note.h>
#include <classes/score.h>
#include <classes/track.h>

#include <QtCore/QFile>
#include <QtCore/QXmlStreamReader>
#include <QtCore/QXmlStreamWriter>

using namespace AudioCarver;
using namespace AudioCarver::Internal;

namespace AudioCarver {

static Score *scoreInstance = 0;

Score *score()
{
    return scoreInstance;
}

namespace Internal {

class DatabaseImplPrivate
{
public:
    DatabaseImpl *q;
    Score *score;
    QString fileName;

    DatabaseImplPrivate(DatabaseImpl *q)
        :   q(q)
        ,   score(new Score(q))
    {
        Q_CHECK_PTR(score);

//        Track* track = qobject_cast<Track*>(score->createObject("Track"));
//        track->setParent(score);
//        score->tracks()->append(track);

//        FCurve *pitchCurve = qobject_cast<FCurve*>(score->createObject("FCurve"));
//        pitchCurve->setParent(score);
//        score->curves()->append(pitchCurve);
//        pitchCurve->appendPoint(FPoint(0.000001, 0));
//        pitchCurve->appendPoint(FPoint(1, 1));

//        FCurve *volumeCurve = qobject_cast<FCurve*>(score->createObject("FCurve"));
//        volumeCurve->setParent(score);
//        score->curves()->append(volumeCurve);
//        volumeCurve->appendPoint(FPoint(0, 0));
//        volumeCurve->appendPoint(FPoint(0.5, 1, true));
//        volumeCurve->appendPoint(FPoint(1, 0));

//        Note *note = qobject_cast<Note*>(score->createObject("Note"));
//        note->setParent(track);
//        track->notes()->append(note);
//        note->setPitchCurve(pitchCurve);
//        note->setVolumeCurve(volumeCurve);
    }

    ~DatabaseImplPrivate()
    {
        score = 0;
        q = 0;
    }
};

} // namespace Internal
} // namespace AudioCarver

DatabaseImpl::DatabaseImpl()
    :   d(new DatabaseImplPrivate(this))
{
}

DatabaseImpl::~DatabaseImpl()
{
    delete d;  d = 0;
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
    d->score->initialize();
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
