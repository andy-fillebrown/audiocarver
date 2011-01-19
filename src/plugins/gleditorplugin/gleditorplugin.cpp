/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2010 Andrew Fillebrown.
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

#include "gleditorplugin.h"

#include "classes/glwidget.h"

#include "implementations/gleditor_mainwindowimpl.h"

#include <coreplugin/icore.h>
#include <coreplugin/mainwindow.h>

#include <QtCore/QtPlugin>

using namespace GLEditor;
using namespace GLEditor::Internal;

GLEditorPlugin::GLEditorPlugin()
{
}

GLEditorPlugin::~GLEditorPlugin()
{
}

bool GLEditorPlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorMessage);
    addAutoReleasedObject(new MainWindowImpl);
    return true;
}

void GLEditorPlugin::extensionsInitialized()
{
}

Q_EXPORT_PLUGIN(GLEditorPlugin)
