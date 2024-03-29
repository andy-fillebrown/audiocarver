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

#include "ac_core_filefiler.h"
#include <mi_core_global.h>
#include <iaggregate.h>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

namespace Xml {

FileFiler::FileFiler(IAggregate *aggregate)
    :   _aggregate(aggregate)
    ,   _file(0)
    ,   _reader(0)
    ,   _writer(0)
{
    _aggregate->appendComponent(this);
}

FileFiler::~FileFiler()
{
    qDelete(_writer);
    qDelete(_reader);
    qDelete(_file);
}

void *FileFiler::queryInterface(int interfaceType) const
{
    void *i = IFiler::queryInterface(interfaceType);
    return i ? i : _aggregate->queryInterface(interfaceType);
}

QString FileFiler::fileName() const
{
    if (!_file)
        return QString();
    return _file->fileName();
}

void FileFiler::setFileName(const QString &fileName)
{
    if (this->fileName() == fileName)
        return;
    delete _file;
    _file = new QFile(fileName);
}

QXmlStreamReader *FileFiler::reader()
{
    if (_file && !_reader && !_writer)
        if (_file->open(QIODevice::ReadOnly))
            _reader = new QXmlStreamReader(_file);
    return _reader;
}

QXmlStreamWriter *FileFiler::writer()
{
    if (_file && !_reader && !_writer) {
        if (_file->open(QIODevice::WriteOnly)) {
            _writer = new QXmlStreamWriter(_file);
            _writer->setAutoFormatting(true);
        }
    }
    return _writer;
}

}
