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

#ifndef GL_BEHAVIORSETTINGS_H
#define GL_BEHAVIORSETTINGS_H

#include <gleditorplugin/gleditor_global.h>

QT_BEGIN_NAMESPACE

class QSettings;

QT_END_NAMESPACE

namespace GL {

class GLEDITOR_EXPORT BehaviorSettingsData
{
public:
    BehaviorSettingsData();

    qreal zoomSpeed;

    bool panningZ;
    bool scrollWheelPanningZ;
    bool scrollWheelZooming;
    bool scalingY;
    bool rotatingX;

    bool linkedViewportModelXforms;
};

class GLEDITOR_EXPORT BehaviorSettings
{
public:
    BehaviorSettingsData d;

    void save(const QString &category, QSettings *s) const;
    void load(const QString &category, const QSettings *s);

    bool equals(const BehaviorSettings &bs) const;
};

inline bool operator==(const BehaviorSettings &a, const BehaviorSettings &b) { return a.equals(b); }
inline bool operator!=(const BehaviorSettings &a, const BehaviorSettings &b) { return !a.equals(b); }

} // namespace GL

#endif // GL_BEHAVIORSETTINGS_H
