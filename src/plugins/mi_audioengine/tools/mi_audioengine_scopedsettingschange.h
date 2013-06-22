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

#ifndef MI_AUDIOENGINE_SCOPEDSETTINGSCHANGE_H
#define MI_AUDIOENGINE_SCOPEDSETTINGSCHANGE_H

#include <iaggregate.h>
#include <iaudioenginesettingswatcher.h>

namespace AudioEngine {

class ScopedSettingsChange
{
    QList<IAudioEngineSettingsWatcher*> _watchers;

public:
    ScopedSettingsChange(IAudioEngine *engine)
    {
        if (!engine)
            return;
        const QList<IComponent*> &components = query<IAggregate>(engine)->components();
        foreach (IComponent *component, components)
            if (component->isTypeOfInterface(I::IAudioEngineSettingsWatcher))
                _watchers.append(query<IAudioEngineSettingsWatcher>(component));
    }

    ~ScopedSettingsChange()
    {
        foreach (IAudioEngineSettingsWatcher *watcher, _watchers)
            watcher->settingsChanged();
    }
};

}

#endif
