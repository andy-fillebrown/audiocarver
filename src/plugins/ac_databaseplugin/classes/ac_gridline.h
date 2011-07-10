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
    Q_PROPERTY(QString label READ label WRITE setLabel)
    Q_PROPERTY(int priority READ priority WRITE setPriority)
    Q_PROPERTY(QColor color READ color WRITE setColor)

public:
    explicit AcGridLine(QObject *parent = 0);
    virtual ~AcGridLine();

    inline static bool lessThan(MiObject *a, MiObject *b);

    qreal location() const;
    void setLocation(qreal location);
    const QString &label() const;
    void setLabel(const QString &label);
    int priority() const;
    void setPriority(int priority);
    const QColor &color() const;
    void setColor(const QColor &color);

    void set(qreal location, const QString &label, int priority, const QColor &color = Qt::lightGray);
    void set(qreal location, int priority, const QColor &color = Qt::lightGray);

private:
    Q_DISABLE_COPY(AcGridLine)
    Private::AcGridLineData *d;
};

inline bool AcGridLine::lessThan(MiObject *a, MiObject *b)
{
    AcGridLine *A = static_cast<AcGridLine*>(a);
    AcGridLine *B = static_cast<AcGridLine*>(b);
    return A->location() < B->location();
}

#endif // AC_GRIDLINE_H
