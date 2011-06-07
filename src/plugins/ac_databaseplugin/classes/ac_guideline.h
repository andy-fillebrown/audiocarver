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

#ifndef AC_GUIDELINE_H
#define AC_GUIDELINE_H

#include <mi_object.h>

#include <ac_database_global.h>

namespace Private {

class AcGuidelineData;

} // namespace Private

class AC_DATABASE_EXPORT AcGuideline : public MiObject
{
    Q_OBJECT
    Q_PROPERTY(qreal location READ location WRITE setLocation)
    Q_PROPERTY(QColor color READ color WRITE setColor)
    Q_PROPERTY(QString text READ text WRITE setText)
    Q_PROPERTY(int priority READ priority WRITE setPriority)

public:
    explicit AcGuideline(QObject *parent = 0);
    virtual ~AcGuideline();

    qreal location() const;
    void setLocation(qreal location);

    const QColor &color() const;
    void setColor(const QColor &color);

    const QString &text() const;
    void setText(const QString &text);

    int priority() const;
    void setPriority(int priority);

private:
    Q_DISABLE_COPY(AcGuideline)
    Private::AcGuidelineData *d;
};

#endif // AC_GUIDELINE_H
