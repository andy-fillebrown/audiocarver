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

#ifndef GLEDITORSETTINGS_H
#define GLEDITORSETTINGS_H

#include "gleditor_global.h"

#include <QtCore/QObject>

namespace GLEditor {

class BehaviorSettings;
class DisplaySettings;

namespace Internal {

class GLEditorSettingsData
{
public:
    GLEditorSettingsData();

    BehaviorSettings *behaviorSettings;
    DisplaySettings *displaySettings;
};

} // namespace Internal

class GLEDITOR_EXPORT GLEditorSettings : public QObject
{
    Q_OBJECT

public:
    GLEditorSettings(QObject *parent = 0);
    virtual ~GLEditorSettings();

    static GLEditorSettings *instance();

    const BehaviorSettings &behaviorSettings() const;
    const DisplaySettings &displaySettings() const;

private:
    Internal::GLEditorSettingsData *d;

    friend class GLWidget;
};

} // namespace GLEditor

#endif // GLEDITORSETTINGS_H
