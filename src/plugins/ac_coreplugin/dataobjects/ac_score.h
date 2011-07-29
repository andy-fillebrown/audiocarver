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

#include <ac_scoreobject.h>

class AcTrackList;

class AcScorePrivate : public AcScoreObjectPrivate
{
public:
    qreal length;
    AcTrackList *tracks;

    AcScorePrivate(AcScoreObject *q);

    virtual ~AcScorePrivate()
    {}
};

class AcScore : public AcScoreObject
{
    Q_OBJECT
    Q_PROPERTY(qreal length READ length WRITE setLength)
    Q_PROPERTY(AcTrackList* tracks READ tracks)

public:
    enum PropertyIndex {
        LengthIndex = AcScoreObject::PropertyCount,
        TracksIndex,
        PropertyCount
    };

    AcScore()
        :   AcScoreObject(*(new AcScorePrivate(this)))
    {}

    virtual ~AcScore()
    {}

    qreal length() const
    {
        Q_D(const AcScore);
        return d->length;
    }

    void setLength(qreal length)
    {
        Q_D(AcScore);
        if (length < 0.0f)
            length = 0.0f;
        if (length == d->length)
            return;
        emit aboutToChange(LengthIndex, d->length);
        d->length = length;
        emit changed(LengthIndex, d->length);
    }

    AcTrackList *tracks() const
    {
        Q_D(const AcScore);
        return d->tracks;
    }

private:
    Q_DISABLE_COPY(AcScore)
    Q_DECLARE_PRIVATE(AcScore)
};

#endif // AC_SCORE_H
