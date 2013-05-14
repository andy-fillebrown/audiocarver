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

#ifndef IFILER_H
#define IFILER_H

#include <icomponent.h>

class QFile;
class QString;
class QXmlStreamReader;
class QXmlStreamWriter;

class IFiler : public IComponent
{
public:
    enum { InterfaceType = I::IFiler };

    virtual QString fileName() const = 0;
    virtual void setFileName(const QString &fileName) = 0;
    virtual QXmlStreamReader *reader() = 0;
    virtual QXmlStreamWriter *writer() = 0;

    int interfaceType() const
    {
        return InterfaceType;
    }

    bool isTypeOfInterface(int interfaceType) const
    {
        if (InterfaceType == interfaceType)
            return true;
        return IComponent::isTypeOfInterface(interfaceType);
    }
};

#endif
