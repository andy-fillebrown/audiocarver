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

#ifndef AC_TUNING_H
#define AC_TUNING_H

#include <mi_object.h>

#include <ac_database_global.h>

namespace Private {

class AcTuningData;
class AcTuningNoteData;

} // namespace Private

class AC_DATABASE_EXPORT AcTuning : public MiObject
{
    Q_OBJECT
    Q_PROPERTY(qreal cents READ cents WRITE setCents)
    Q_PROPERTY(QColor color READ color WRITE setColor)
    Q_PROPERTY(int priority READ priority WRITE setPriority)

public:
    explicit AcTuning(QObject *parent = 0);
    virtual ~AcTuning();

    qreal cents() const;
    void setCents(qreal cents);

    const QColor &color() const;
    void setColor(const QColor &color);

    int priority() const;
    void setPriority(int priority);

private:
    Q_DISABLE_COPY(AcTuning)
    Private::AcTuningData *d;
};

#endif // AC_TUNING_H
