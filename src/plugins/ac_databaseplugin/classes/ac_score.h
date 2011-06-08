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

#ifndef AC_SCORE_H
#define AC_SCORE_H

#include <mi_root.h>

#include <ac_database_global.h>

class AcFCurve;
class AcGuideline;
class AcGridSettings;
class AcNote;
class AcTrack;
class AcViewSettings;

namespace Private {

class AcScoreData;

} // namespace Private

class AC_DATABASE_EXPORT AcScore : public MiRoot
{
    Q_OBJECT
    Q_PROPERTY(MiList* settings READ settings)
    Q_PROPERTY(MiList* barlines READ barlines)
    Q_PROPERTY(MiList* tunings READ tunings)
    Q_PROPERTY(MiList* curves READ curves)
    Q_PROPERTY(MiList* notes READ notes)
    Q_PROPERTY(MiList* tracks READ tracks)
    Q_PROPERTY(qreal length READ length WRITE setLength)

public:
    AcScore(QObject *parent = 0);
    virtual ~AcScore();

    static AcScore *instance();

    MiList *settings() const;
    MiList *barlines() const;
    MiList *tunings() const;
    MiList *curves() const;
    MiList *notes() const;
    MiList *tracks() const;

    qreal length() const;
    void setLength(qreal length);

    AcGuideline *addBarline(AcGuideline *barline = 0);
    AcGuideline *addTuning(AcGuideline *tuning = 0);
    AcFCurve *addCurve(AcFCurve *curve = 0);
    AcNote *addNote(AcNote *note = 0);
    AcTrack *addTrack(AcTrack *track = 0);

    void addBarlines(const QList<MiObject*> &barlines);
    void addTunings(const QList<MiObject*> &tunings);
    void addCurves(const QList<MiObject*> &curves);
    void addNotes(const QList<MiObject*> &notes);
    void addTracks(const QList<MiObject*> &tracks);

    AcGridSettings *gridSettings() const;
    AcViewSettings *viewSettings() const;
    AcGuideline *barlineAt(int i);
    AcGuideline *tuningAt(int i);
    AcFCurve *curveAt(int i);
    AcNote *noteAt(int i);
    AcTrack *trackAt(int i);

    void clearBarlines();
    void clearTunings();

    virtual void clear();

    virtual QString &normalizeClassName(QString &className) const;
    virtual MiObject *createObject(const QString &className);
    virtual MiObject *findObject(const QString &className) const;

private:
    Q_DISABLE_COPY(AcScore)
    Private::AcScoreData *d;
};

#endif // AC_SCORE_H
