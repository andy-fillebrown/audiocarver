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

#ifndef ICORE_H
#define ICORE_H

#include "qt_core_global.h"

#include <QtCore/QObject>
#include <QtCore/QSettings>

QT_BEGIN_NAMESPACE

class QPrinter;
class QStatusBar;
template <class T> class QList;

QT_END_NAMESPACE

namespace Core {
class ActionManager;
class Context;
class FileManager;
class IContext;
class MainWindow;
class SettingsDatabase;
class UniqueIDManager;

class CORE_EXPORT ICore : public QObject
{
    Q_OBJECT

public:
    ICore() {}
    virtual ~ICore() {}

    static ICore *instance();

    virtual bool showOptionsDialog(const QString &group = QString(),
                                   const QString &page = QString(),
                                   QWidget *parent = 0) = 0;

    virtual ActionManager *actionManager() const = 0;
    virtual FileManager *fileManager() const = 0;
    virtual UniqueIDManager *uniqueIDManager() const = 0;

    virtual QSettings *settings(QSettings::Scope scope = QSettings::UserScope) const = 0;
    virtual SettingsDatabase *settingsDatabase() const = 0;

    virtual QString resourcePath() const = 0;
    virtual QString userResourcePath() const = 0;

    virtual MainWindow *mainWindow() const = 0;

    virtual IContext *currentContextObject() const = 0;
    // Adds and removes additional active contexts, these contexts are appended
    // to the currently active contexts.
    virtual void updateAdditionalContexts(const Context &remove, const Context &add) = 0;
    virtual bool hasContext(int context) const = 0;
    virtual void addContextObject(IContext *context) = 0;
    virtual void removeContextObject(IContext *context) = 0;

    enum OpenFilesFlags {
        None = 0,
        SwitchMode = 1,
        CanContainLineNumbers = 2,
         /// Stop loading once the first file fails to load
        StopOnLoadFail = 4
    };

signals:
    void coreAboutToOpen();
    void coreOpened();
    void saveSettingsRequested();
    void optionsDialogRequested();
    void coreAboutToClose();
    void contextAboutToChange(Core::IContext *context);
    void contextChanged(Core::IContext *context, const Core::Context &additionalContexts);
};

} // namespace Core

#endif // ICORE_H
