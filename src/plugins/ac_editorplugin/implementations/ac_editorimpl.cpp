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

#include "ac_editorimpl.h"

#include <QtCore/QDebug>

using namespace AudioCarver;
using namespace AudioCarver::Internal;

EditorImpl::EditorImpl()
{
}

EditorImpl::~EditorImpl()
{
}

void EditorImpl::undo()
{
    qDebug() << Q_FUNC_INFO;
}

void EditorImpl::redo()
{
    qDebug() << Q_FUNC_INFO;
}

void EditorImpl::cut()
{
    qDebug() << Q_FUNC_INFO;
}

void EditorImpl::copy() const
{
    qDebug() << Q_FUNC_INFO;
}

void EditorImpl::paste()
{
    qDebug() << Q_FUNC_INFO;
}

void EditorImpl::selectAll()
{
    qDebug() << Q_FUNC_INFO;
}
