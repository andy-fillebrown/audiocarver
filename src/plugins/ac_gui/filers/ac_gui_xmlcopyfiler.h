/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2012 Andrew Fillebrown.
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

#ifndef AC_GUI_XMLCOPYFILER_H
#define AC_GUI_XMLCOPYFILER_H

#include "mi_core_aggregator.h"

#include "ac_core_xmlreader.h"
#include "ac_core_xmlwriter.h"

namespace Ac {
namespace Gui {

class XmlCopyFiler : public Mi::Core::Aggregator
{
    friend class FilerFactory;

    QString _data;

protected:
    XmlCopyFiler()
    {}

    virtual IAggregator *init();

    QString *data()
    {
        return &_data;
    }

    class Reader : public Core::XmlReader
    {
        friend class XmlCopyFiler;

    protected:
        Reader(XmlCopyFiler *aggregator)
            :   XmlReader(aggregator)
        {}

        IAggregate *init();

        XmlCopyFiler *a() const
        {
            return static_cast<XmlCopyFiler*>(XmlReader::a());
        }
    };

    class Writer : public Core::XmlWriter
    {
        friend class XmlCopyFiler;

    protected:
        Writer(IAggregator *aggregator)
            :   XmlWriter(aggregator)
        {}

        IAggregate *init();

        XmlCopyFiler *a() const
        {
            return static_cast<XmlCopyFiler*>(XmlWriter::a());
        }
    };

    // IAggregator
    IAggregate *createAggregate(int interfaceType)
    {
        switch (interfaceType) {
        case I::IReader:
            return (new Reader(this))->init();
        case I::IWriter:
            return (new Writer(this))->init();
        default:
            return Aggregator::createAggregate(interfaceType);
        }
    }
};

} // namespace Gui
} // namespace Ac

#endif // AC_GUI_XMLCOPYFILER_H
