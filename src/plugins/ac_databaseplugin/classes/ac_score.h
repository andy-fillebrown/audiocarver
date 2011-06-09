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

class AcBarline;
class AcFCurve;
class AcGuideline;
class AcGridSettings;
class AcNote;
class AcTrack;
class AcTuning;
class AcViewSettings;

template <typename T> class MiList;

namespace Private {

class AcScoreData;

} // namespace Private

class AC_DATABASE_EXPORT AcScore : public MiRoot
{
    Q_OBJECT
    Q_PROPERTY(qreal length READ length WRITE setLength)
    Q_PROPERTY(MiObjectList* settings READ settingObjectList)
    Q_PROPERTY(MiObjectList* barlines READ barlineObjectList)
    Q_PROPERTY(MiObjectList* tunings READ tuningObjectList)
    Q_PROPERTY(MiObjectList* curves READ curveObjectList)
    Q_PROPERTY(MiObjectList* notes READ noteObjectList)
    Q_PROPERTY(MiObjectList* tracks READ trackObjectList)

public:
    AcScore(QObject *parent = 0);
    virtual ~AcScore();

    static AcScore *instance();

    qreal length() const;
    void setLength(qreal length);

    MiList<AcBarline> &barlines() const;
    MiList<AcTuning> &tunings() const;
    MiList<AcFCurve> &curves() const;
    MiList<AcNote> &notes() const;
    MiList<AcTrack> &tracks() const;

    AcGridSettings *gridSettings() const;
    AcViewSettings *viewSettings() const;

    virtual void clear();

protected:
    virtual QString &normalizeClassName(QString &className) const;
    virtual MiObject *createObject(const QString &className);
    virtual MiObject *findObject(const QString &className) const;

private slots:
    void updateScoreProperty(const QString &propertyName);
    void updateBarlineProperty(const QString &propertyName);
    void updateTuningProperty(const QString &propertyName);
    void sortBarlines();
    void sortTunings();

private:
    Q_DISABLE_COPY(AcScore)
    Private::AcScoreData *d;

    MiObjectList *settingObjectList() const;
    MiObjectList *barlineObjectList() const;
    MiObjectList *tuningObjectList() const;
    MiObjectList *curveObjectList() const;
    MiObjectList *noteObjectList() const;
    MiObjectList *trackObjectList() const;
};

#endif // AC_SCORE_H
