/**************************************************************************
**
** This file is part of Qt Creator
**
** Copyright (c) 2011 Nokia Corporation and/or its subsidiary(-ies).
**
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** Commercial Usage
**
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
**
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at http://qt.nokia.com/contact.
**
**************************************************************************/

#ifndef IFILE_H
#define IFILE_H

#include "qt_core_global.h"
#include <QtCore/QObject>

namespace Core {

class MimeType;

class CORE_EXPORT IFile : public QObject
{
    Q_OBJECT

public:
    // This enum must match the indexes of the reloadBehavior widget
    // in generalsettings.ui
    enum ReloadSetting {
        AlwaysAsk = 0,
        ReloadUnmodified = 1,
        IgnoreAll = 2
    };

    enum Utf8BomSetting {
        AlwaysAdd = 0,
        OnlyKeep = 1,
        AlwaysDelete = 2
    };

    enum ChangeTrigger {
        TriggerInternal,
        TriggerExternal
    };

    enum ChangeType {
        TypeContents,
        TypePermissions,
        TypeRemoved
    };

    enum ReloadBehavior {
        BehaviorAsk,
        BehaviorSilent
    };

    enum ReloadFlag {
        FlagReload,
        FlagIgnore
    };

    IFile(QObject *parent = 0) : QObject(parent) {}
    virtual ~IFile() {}

    virtual bool save(const QString &fileName = QString()) = 0;
    virtual QString fileName() const = 0;

    virtual QString defaultPath() const = 0;
    virtual QString suggestedFileName() const = 0;
    virtual QString mimeType() const = 0;

    virtual bool isModified() const = 0;
    virtual bool isReadOnly() const = 0;
    virtual bool isSaveAsAllowed() const = 0;

    virtual ReloadBehavior reloadBehavior(ChangeTrigger state, ChangeType type) const = 0;
    virtual void reload(ReloadFlag flag, ChangeType type) = 0;
    virtual void rename(const QString &newName) = 0;

    virtual void checkPermissions() {}

signals:
    void changed();

    void aboutToReload();
    void reloaded();
};

} // namespace Core

#endif // IFILE_H
