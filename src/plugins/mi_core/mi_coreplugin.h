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

#ifndef MI_COREPLUGIN_H
#define MI_COREPLUGIN_H

#include <iplugin.h>

namespace Mi {

class CorePlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT

protected:
    bool initialize(const QStringList &arguments, QString *errorMessage = 0);

    void extensionsInitialized()
    {}

    ~CorePlugin();
};

} // namespace Mi

#endif // MI_COREPLUGIN_H
