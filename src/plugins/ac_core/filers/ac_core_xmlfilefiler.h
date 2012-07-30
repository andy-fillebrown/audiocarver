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

#ifndef AC_CORE_XMLFILEFILER_H
#define AC_CORE_XMLFILEFILER_H

#include "mi_core_aggregate.h"

#include "ac_core_xmlreader.h"
#include "ac_core_xmlwriter.h"
#include "mi_ifiler.h"

class QFile;

namespace Ac {
namespace Core {

class XmlFileFiler : public Mi::Core::Aggregator
{
    friend class FilerFactory;

    QFile *_file;

protected:
    XmlFileFiler()
        :   _file(0)
    {}

    virtual IAggregator *init();
    ~XmlFileFiler();

    QFile *file() const
    {
        return _file;
    }

    QString fileName() const;
    void setFileName(const QString &fileName);

    class FileFiler : public IFileFiler
    {
        friend class XmlFileFiler;

        XmlFileFiler *_aggregator;

    protected:
        FileFiler(XmlFileFiler *aggregator)
            :   _aggregator(aggregator)
        {}

        IAggregate *init();

        XmlFileFiler *a() const
        {
            return _aggregator;
        }

        // IFileFiler
        QString fileName() const
        {
            return a()->fileName();
        }

        void setFileName(const QString &fileName)
        {
            return a()->setFileName(fileName);
        }

        // IAggregate
        IAggregator *aggregator() const
        {
            return _aggregator;
        }
    };

    class Reader : XmlReader
    {
        friend class XmlFileFiler;

    protected:
        Reader(XmlFileFiler *aggregator)
            :   XmlReader(aggregator)
        {}

        IAggregate *init();

        XmlFileFiler *a() const
        {
            return static_cast<XmlFileFiler*>(XmlReader::a());
        }
    };

    class Writer : XmlWriter
    {
        friend class XmlFileFiler;

    protected:
        Writer(XmlFileFiler *aggregator)
            :   XmlWriter(aggregator)
        {}

        IAggregate *init();

        XmlFileFiler *a() const
        {
            return static_cast<XmlFileFiler*>(XmlWriter::a());
        }
    };

    // IAggregator
    IAggregate *createAggregate(int interfaceType)
    {
        switch (interfaceType) {
        case I::IFileFiler:
            return appendAggregate((new FileFiler(this))->init());
        case I::IReader:
            return appendAggregate((new Reader(this))->init());
        case I::IWriter:
            return appendAggregate((new Writer(this))->init());
        default:
            return Aggregator::createAggregate(interfaceType);
        }
    }
};

} // namespace Core
} // namespace Ac

#endif // AC_CORE_XMLFILEFILER_H
