/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2013 Andrew Fillebrown.
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

#ifndef AC_GUI_COPYFILER_H
#define AC_GUI_COPYFILER_H

#include <ifiler.h>
#include <QString>

class IAggregate;

namespace Xml {

class CopyFiler : public IFiler
{
    IAggregate *_aggregate;
    QString _data;
    QXmlStreamReader *_reader;
    QXmlStreamWriter *_writer;

public:
    CopyFiler(IAggregate *aggregate);
    ~CopyFiler();

    void *queryInterface(int interfaceType) const;

protected:
    void initialize()
    {}

    void reset();

    QString fileName() const
    {
        return QString();
    }

    void setFileName(const QString &fileName)
    {}

    QXmlStreamReader *reader();
    QXmlStreamWriter *writer();
};

}

#endif
