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

#ifndef AC_MIDIMAINWINDOWEXTENSION_H
#define AC_MIDIMAINWINDOWEXTENSION_H

#include <imainwindowextension.h>

namespace Ac {
namespace Midi {

class MainWindowExtension : public Core::IMainWindowExtension
{
    Q_OBJECT

public:
    void initMenuBarGroups(QStringList &groups) const;
    void initMenuGroups(const QString &menuBarGroup, QString &id, QString &title, QStringList &groups) const;
    void initActions();

private slots:
    void importMidiFile();
};

} // namespace Midi
} // namespace Ac

#endif // AC_MIDIMAINWINDOWEXTENSION_H
