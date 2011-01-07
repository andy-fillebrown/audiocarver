/**************************************************************************
**
** This file is part of Qt Creator
**
** Copyright (c) 2010 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef COREIMPL_H
#define COREIMPL_H

#include "icore.h"

namespace Core {

class MainWindow;

namespace Internal {

class CoreImpl : public ICore
{
    Q_OBJECT

public:
    CoreImpl(MainWindow *mainwindow);
    ~CoreImpl();

    bool showOptionsDialog(const QString &group = QString(),
                           const QString &page = QString(),
                           QWidget *parent = 0);

    ActionManager *actionManager() const;
    FileManager *fileManager() const ;
    UniqueIDManager *uniqueIDManager() const;

    QSettings *settings(QSettings::Scope scope = QSettings::UserScope) const;
    SettingsDatabase *settingsDatabase() const;

    QString resourcePath() const;
    QString userResourcePath() const;

    IContext *currentContextObject() const;

    MainWindow *mainWindow() const;

    // Adds and removes additional active contexts, these contexts are appended
    // to the currently active contexts.
    void updateAdditionalContexts(const Context &remove, const Context &add);
    bool hasContext(int context) const;
    void addContextObject(IContext *context);
    void removeContextObject(IContext *context);

private:
    MainWindow *m_mainwindow;
    friend class Core::MainWindow;
};

} // namespace Internal
} // namespace Core

#endif // COREIMPL_H
