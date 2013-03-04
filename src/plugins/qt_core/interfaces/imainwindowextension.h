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

#ifndef IMAINWINDOWEXTENSION_H
#define IMAINWINDOWEXTENSION_H

#include <QObject>
#include "qt_core_global.h"

class CORE_EXPORT IMainWindowExtension : public QObject
{
    Q_OBJECT

public:
    virtual void initMenuBarGroups(QStringList &groups) const = 0;
    virtual void initMenuGroups(const QString &menuBarGroup, QString &id, QString &title, QStringList &groups) const = 0;
    virtual void initActions() = 0;
};

#endif
