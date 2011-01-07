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

#ifndef AC_EDITORPLUGIN_H
#define AC_EDITORPLUGIN_H

#include <extensionsystem/iplugin.h>

namespace AudioCarver {
namespace Internal {

class EditorPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT

public:
    EditorPlugin();
    ~EditorPlugin();

    virtual bool initialize(const QStringList &arguments, QString *errorMessage = 0);
    virtual void extensionsInitialized();
};

} // namespace Internal
} // namespace AudioCarver

#endif // AC_EDITORPLUGIN_H
