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

#ifndef AC_EDITORPLUGIN_H
#define AC_EDITORPLUGIN_H

#include <iplugin.h>

namespace Private {

class AcEditorPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT

public:
    AcEditorPlugin() {}
private:
    ~AcEditorPlugin() {}
    Q_DISABLE_COPY(AcEditorPlugin)

private:
    bool initialize(const QStringList &arguments, QString *errorMessage = 0);
    void extensionsInitialized() {}
};

} // namespace Private

#endif // AC_EDITORPLUGIN_H
