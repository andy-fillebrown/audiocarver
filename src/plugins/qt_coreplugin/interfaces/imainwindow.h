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

#ifndef IMAINWINDOW_H
#define IMAINWINDOW_H

#include <qt_coreplugin/core_global.h>

#include <QtCore/QObject>

namespace Core {

class CORE_EXPORT IMainWindow : public QObject
{
    Q_OBJECT

public:
    IMainWindow();
    virtual ~IMainWindow();

    virtual void initMenuBarGroups(QStringList &groups) const = 0;
    virtual void initMenuGroups(const QString &menuBarGroup, QString &id, QString &title, QStringList &groups) const = 0;
    virtual void initActions() = 0;
};

} // namespace Core

#endif // IMAINWINDOW_H
