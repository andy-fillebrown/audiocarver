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

#ifndef MI_FONT_H
#define MI_FONT_H

#include <mi_object.h>

namespace Private {

class MiFontData;

} // namespace Private

class MI_CORE_EXPORT MiFont : public MiObject
{
    Q_OBJECT
    Q_PROPERTY(QString family READ family WRITE setFamily)
    Q_PROPERTY(int pointSize READ pointSize WRITE setPointSize)

public:
    enum PropertyIndex
    {
        Family = MiObject::PropertyCount,
        PointSize,
        PropertyCount
    };

    MiFont(QObject *parent = 0);
    virtual ~MiFont();

    QString family() const;
    void setFamily(const QString &family);
    int pointSize() const;
    void setPointSize(int size);

    const QFont &qFont() const;

private:
    Q_DISABLE_COPY(MiFont)
    Private::MiFontData *d;
};

#endif // MI_FONT_H
