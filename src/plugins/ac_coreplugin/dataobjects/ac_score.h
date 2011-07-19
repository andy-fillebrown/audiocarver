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
#include <ac_core_global.h>

class AcBarLine;
class AcGridSettings;
class AcTrack;
class AcTuningLine;
class AcValueLine;
class AcViewSettings;
class MiFont;
template <typename T> class MiList;

namespace Private {

class AcScoreData;

} // namespace Private

class AC_CORE_EXPORT AcScore : public MiRoot
{
    Q_OBJECT
    Q_PROPERTY(qreal length READ length WRITE setLength)
    Q_PROPERTY(MiObjectList* settings READ settingsObjects)
    Q_PROPERTY(MiObjectList* tracks READ trackObjects)
    Q_PROPERTY(MiObjectList* barLines READ barLineObjects)
    Q_PROPERTY(MiObjectList* tuningLines READ tuningLineObjects)
    Q_PROPERTY(MiObjectList* valueLines READ valueLineObjects)

public:
    enum PropertyIndex
    {
        Length = MiRoot::PropertyCount,
        Settings,
        Tracks,
        BarLines,
        TuningLines,
        ValueLines,
        PropertyCount
    };

    AcScore(QObject *parent = 0);
    virtual ~AcScore();

    static AcScore *instance();

    qreal length() const;
    void setLength(qreal length);
    MiList<AcTrack> &tracks() const;
    MiList<AcBarLine> &barLines() const;
    MiList<AcTuningLine> &tuningLines() const;
    MiList<AcValueLine> &valueLines() const;

    MiFont *fontSettings() const;
    AcGridSettings *gridSettings() const;
    AcViewSettings *viewSettings() const;

    virtual void clear();

protected:
    virtual QString &normalizeClassName(QString &className) const;
    virtual MiObject *createObject(const QString &className);
    virtual MiObject *findObject(const QString &className) const;

private slots:
    void updateScoreProperty(int propertyIndex);
    void updateBarLineProperty(int propertyIndex);
    void updateTuningLineProperty(int propertyIndex);
    void updateValueLineProperty(int propertyIndex);
    void sortBarLines();
    void sortTuningLines();
    void sortValueLines();

private:
    Q_DISABLE_COPY(AcScore)
    Private::AcScoreData *d;

    MiObjectList *settingsObjects() const;
    MiObjectList *trackObjects() const;
    MiObjectList *barLineObjects() const;
    MiObjectList *tuningLineObjects() const;
    MiObjectList *valueLineObjects() const;
};

#endif // AC_SCORE_H