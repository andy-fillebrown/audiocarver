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

#ifndef MI_GUI_CORE_DATABASESAVER_H
#define MI_GUI_CORE_DATABASESAVER_H

#include <icorelistener.h>
#include <mi_gui_global.h>

namespace Core {

class MI_GUI_EXPORT DatabaseSaver : public ICoreListener
{
public:
    DatabaseSaver(QObject *parent = 0)
        :   ICoreListener(parent)
    {}

protected:
    bool coreAboutToClose();
};

}

#endif
