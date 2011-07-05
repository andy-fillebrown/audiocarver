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

#ifndef AC_GRIDLINE_H
#define AC_GRIDLINE_H

#include <mi_object.h>
#include <ac_database_global.h>

namespace Private {

class AcGridLineData;

} // namespace Private

class AC_DATABASE_EXPORT AcGridLine : public MiObject
{
    Q_OBJECT
    Q_PROPERTY(qreal location READ location WRITE setLocation)
    Q_PROPERTY(QColor color READ color WRITE setColor)
    Q_PROPERTY(QString label READ label WRITE setLabel)
    Q_PROPERTY(int priority READ priority WRITE setPriority)

public:
    explicit AcGridLine(QObject *parent = 0);
    virtual ~AcGridLine();

    inline static bool locationLessThan(MiObject *a, MiObject *b);
    inline static bool priorityLessThan(MiObject *a, MiObject *b);

    qreal location() const;
    void setLocation(qreal location);
    const QColor &color() const;
    void setColor(const QColor &color);
    const QString &label() const;
    void setLabel(const QString &label);
    int priority() const;
    void setPriority(int priority);

private:
    Q_DISABLE_COPY(AcGridLine)
    Private::AcGridLineData *d;
};

inline bool AcGridLine::locationLessThan(MiObject *a, MiObject *b)
{
    AcGridLine *A = qobject_cast<AcGridLine*>(a);
    AcGridLine *B = qobject_cast<AcGridLine*>(b);
    return A->location() < B->location();
}

inline bool AcGridLine::priorityLessThan(MiObject *a, MiObject *b)
{
    AcGridLine *A = qobject_cast<AcGridLine*>(a);
    AcGridLine *B = qobject_cast<AcGridLine*>(b);
    if (A->priority() < B->priority())
        return true;
    if (A->priority() == B->priority() && A->location() <= B->location())
        return true;
    return false;
}

#endif // AC_GRIDLINE_H