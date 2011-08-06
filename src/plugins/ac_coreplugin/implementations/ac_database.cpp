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
//#include <ac_barline.h>
#include <ac_note.h>
#include <ac_notelist.h>
#include <ac_pitchcurve.h>
#include <ac_pitchpoint.h>
//#include <ac_point.h>
#include <ac_score.h>
#include <ac_track.h>
#include <ac_tracklist.h>
//#include <ac_tuningline.h>
//#include <ac_valueline.h>
//#include <ac_volumecurve.h>
//#include <mi_list.h>
//#include <QFile>
//#include <QXmlStreamReader>
//#include <QXmlStreamWriter>

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
        ,   score(new AcScore)
    {
//        score->tuningLines().add()->set(127.0f, "", 0, Qt::black);
//        score->tuningLines().add()->set(0.0f, "", 0, Qt::black);
//        score->tuningLines().add()->set(84.0f, "84 (C)", 1, QColor(127, 0, 0));
//        score->tuningLines().add()->set(72.0f, "72 (C)", 2, QColor(127, 0, 0));
//        score->tuningLines().add()->set(60.0f, "60 (C)", 0, QColor(127, 0, 0));
//        score->tuningLines().add()->set(48.0f, "48 (C)", 2, QColor(127, 0, 0));
//        score->tuningLines().add()->set(32.0f, "32 (C)", 1, QColor(127, 0, 0));
//        score->tuningLines().add()->set(79.0f, "79 (G)", 3);
//        score->tuningLines().add()->set(67.0f, "67 (G)", 3);
//        score->tuningLines().add()->set(55.0f, "55 (G)", 3);
//        score->tuningLines().add()->set(39.0f, "39 (G)", 3);

//        for (int i = 0;  i < 128;  ++i) {
//            QString label = QString("%1.%2").arg((i / 4) + 1).arg(i % 4);
//            if (label.endsWith(".0"))
//                label.chop(2);
//            AcBarLine *barLine = score->barLines().add();
//            barLine->setLocation(i);
//            barLine->setLabel(label);
//        }
//        score->barLines().first()->setColor(QColor(0, 127, 0));
//        for (int i = 1;  i < 128;  i*=2)
//            for (int j = i;  j < 128;  j+=i)
//                score->barLines().at(j)->setPriority(128 / (i + 1));
//        score->barLines().add()->set(4.0f * 32, 0, QColor(127, 0, 0));

//        score->valueLines().add()->set(1.0f, "1.000", 0, Qt::black);
//        score->valueLines().add()->set(0.875f, "0.875", 3);
//        score->valueLines().add()->set(0.75f, "0.750", 2);
//        score->valueLines().add()->set(0.625f, "0.625", 3);
//        score->valueLines().add()->set(0.5f, "0.500", 1, QColor(0, 0, 127));
//        score->valueLines().add()->set(0.375f, "0.375", 3);
//        score->valueLines().add()->set(0.25f, "0.250", 2);
//        score->valueLines().add()->set(0.125f, "0.125", 3);
//        score->valueLines().add()->set(0.0f, "", 0, Qt::black);

        AcTrack *track = new AcTrack;
        score->tracks()->addChild(track);
//        for (int i = 0;  i < 126;  ++i) {
            int i = 48;
            AcNote *note = new AcNote;
            track->notes()->addChild(note);
            AcPitchCurve *pitchCurve = note->pitchCurve();
            AcPitchPoint *first = pitchCurve->children().first();
            AcPitchPoint *last = pitchCurve->children().last();
            AcPitchPoint *pitchPointA = new AcPitchPoint;
            pitchCurve->addChild(pitchPointA);
            pitchPointA->setX(i + 0.0f);
            pitchPointA->setY(60.0f);
            AcPitchPoint *pitchPointB = new AcPitchPoint;
            pitchCurve->addChild(pitchPointB);
            pitchPointB->setX(i + 1.0f);
            pitchPointB->setY(72.0f);
            AcPitchPoint *pitchPointC = new AcPitchPoint;
            pitchCurve->addChild(pitchPointC);
            pitchPointC->setX(i + 2.0f);
            pitchPointC->setY(67.0f);
            AcPitchPoint *pitchPointD = new AcPitchPoint;
            pitchCurve->addChild(pitchPointD);
            pitchPointD->setCurveType(AcCurvePoint::BezierCurve);
            pitchPointD->setX(i + 5.0f);
            pitchPointD->setY(71.0f);
            AcPitchPoint *pitchPointE = new AcPitchPoint;
            pitchCurve->addChild(pitchPointE);
            pitchPointE->setX(i + 7.0f);
            pitchPointE->setY(72.0f);
            pitchCurve->removeChild(first);
            pitchCurve->removeChild(last);
//            AcVolumeCurve *volumeCurve = note->volumeCurve();
//            AcPoint *volumePointA = volumeCurve->points().add();
//            volumePointA->setX(0.0f);
//            volumePointA->setY(0.0f);
//            AcPoint *volumePointB = volumeCurve->points().add();
//            volumePointB->setX(0.5f);
//            volumePointB->setY(1.0f);
//            volumePointB->setCurved(true);
//            AcPoint *volumePointC = volumeCurve->points().add();
//            volumePointC->setX(1.0f);
//            volumePointC->setY(0.0f);
//        }
    }

    virtual ~AcDatabaseImplData()
    {
        delete score;
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
//    d->score->clear();
}

void AcDatabaseImpl::read(const QString &fileName)
{
//    QFile file(fileName);
//    if (!file.open(QFile::ReadOnly))
//        return;
//    QXmlStreamReader in(&file);
//    while (in.readNext() != QXmlStreamReader::StartElement && !in.atEnd());
//    if (d->score->read(in)) {
//        d->score->update(true);
//        d->fileName = fileName;
//    }
}

void AcDatabaseImpl::write(const QString &fileName)
{
//    QFile file(fileName);
//    if (!file.open(QFile::WriteOnly))
//        return;
//    QXmlStreamWriter out(&file);
//    out.setAutoFormatting(true);
//    d->score->write(out);
//    file.write("\n");
//    d->fileName = fileName;
}
