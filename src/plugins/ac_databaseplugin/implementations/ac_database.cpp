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

#include "ac_database.h"

#include <ac_fcurve.h>
#include <ac_fpoint.h>
#include <ac_note.h>
#include <ac_score.h>
#include <ac_track.h>
#include <ac_tuning.h>

#include <mi_list.h>

#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

using namespace Private;

namespace Private {

class AcDatabaseImplData
{
public:
    AcDatabaseImpl *q;
    AcScore *score;
    QString fileName;

    AcDatabaseImplData(AcDatabaseImpl *q)
        :   q(q)
        ,   score(new AcScore(q))
    {
        MiObject *tuning = score->createObject("Tuning");

        AcTrack *track = qobject_cast<AcTrack*>(score->createObject("Track"));
        track->setTuning(tuning);

        AcFCurve *pitchCurve = qobject_cast<AcFCurve*>(score->createObject("FCurve"));
        pitchCurve->appendPoint(AcFPoint(0.000001, 0));
        pitchCurve->appendPoint(AcFPoint(1, 1));

        AcNote *note = qobject_cast<AcNote*>(track->createObject("Note"));
        note->setPitchCurve(pitchCurve);
    }
};

} // namespace Private

AcDatabaseImpl::AcDatabaseImpl()
    :   d(new AcDatabaseImplData(this))
{}

AcDatabaseImpl::~AcDatabaseImpl()
{
    delete d;
}

const QString &AcDatabaseImpl::fileExtension() const
{
    static QString ext = QString::fromLatin1(".ac");
    return ext;
}

const QString &AcDatabaseImpl::fileFilter() const
{
    static QString filter = QString::fromLatin1("AudioCarver (*%1)").arg(fileExtension());
    return filter;
}

const QString &AcDatabaseImpl::fileName() const
{
    return d->fileName;
}

void AcDatabaseImpl::clear()
{
    d->score->clear();
}

void AcDatabaseImpl::read(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly))
        return;

    QXmlStreamReader in(&file);
    while (in.readNext() != QXmlStreamReader::StartElement && !in.atEnd());

    if (d->score->read(in))
        d->fileName = fileName;
}

void AcDatabaseImpl::write(const QString &fileName)
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
