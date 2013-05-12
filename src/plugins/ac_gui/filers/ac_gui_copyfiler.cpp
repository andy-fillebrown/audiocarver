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

#include "ac_gui_copyfiler.h"
#include <mi_core_global.h>
#include <iaggregate.h>
#include <QApplication>
#include <QClipboard>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

namespace Xml {

CopyFiler::CopyFiler(IAggregate *aggregate)
    :   _aggregate(aggregate)
    ,   _reader(0)
    ,   _writer(0)
{
    _aggregate->appendComponent(this);
}

CopyFiler::~CopyFiler()
{
    qDelete(_writer);
    qDelete(_reader);
}

void *CopyFiler::queryInterface(int interfaceType) const
{
    void *i = IFiler::queryInterface(interfaceType);
    return i ? i : _aggregate->queryInterface(interfaceType);
}

QXmlStreamReader *CopyFiler::reader()
{
    if (!_reader && !_writer) {
        _data = QString("<clipboard>") + QApplication::clipboard()->text() + "</clipboard>";
        _reader = new QXmlStreamReader(_data);
    }
    return _reader;
}

QXmlStreamWriter *CopyFiler::writer()
{
    if (!_reader && !_writer) {
        _writer = new QXmlStreamWriter(&_data);
        _writer->setAutoFormatting(true);
    }
    return _writer;
}

}
