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

#include "coreimpl.h"
#include "mainwindow.h"
#include <QStatusBar>
#include <QCoreApplication>
#include <QDir>
#include <QDebug>

namespace Core {
namespace Internal {

// The Core Singleton
static CoreImpl *m_instance = 0;

} // namespace Internal
} // namespace Core


using namespace Core;
using namespace Core::Internal;


ICore* ICore::instance()
{
    return m_instance;
}

CoreImpl::CoreImpl(MainWindow *mainwindow)
{
    m_instance = this;
    m_mainwindow = mainwindow;
}

CoreImpl::~CoreImpl()
{
    m_instance = 0;
}

bool CoreImpl::showOptionsDialog(const QString &group, const QString &page, QWidget *parent)
{
    return m_mainwindow->showOptionsDialog(group, page, parent);
}

ActionManager *CoreImpl::actionManager() const
{
    return m_mainwindow->actionManager();
}

FileManager *CoreImpl::fileManager() const
{
    return m_mainwindow->fileManager();
}

UniqueIDManager *CoreImpl::uniqueIDManager() const
{
    return m_mainwindow->uniqueIDManager();
}

QSettings *CoreImpl::settings(QSettings::Scope scope) const
{
    return m_mainwindow->settings(scope);
}

SettingsDatabase *CoreImpl::settingsDatabase() const
{
    return m_mainwindow->settingsDatabase();
}

#ifdef Q_OS_MAC
#  define SHARE_PATH "/../Resources"
#else
#  define SHARE_PATH "/../share/"PRO_NAME_LC_STR
#endif

QString CoreImpl::resourcePath() const
{
    return QDir::cleanPath(QCoreApplication::applicationDirPath() + QLatin1String(SHARE_PATH));
}

QString CoreImpl::userResourcePath() const
{
    // Create project dir if it doesn't yet exist
    const QString configDir = QFileInfo(settings(QSettings::UserScope)->fileName()).path();
    const QString urp = configDir + "/"PRO_NAME_LC_STR;

    QFileInfo fi(urp + QLatin1Char('/'));
    if (!fi.exists()) {
        QDir dir;
        if (!dir.mkpath(urp))
            qWarning() << "could not create" << urp;
    }

    return urp;
}

IContext *CoreImpl::currentContextObject() const
{
    return m_mainwindow->currentContextObject();
}


MainWindow *CoreImpl::mainWindow() const
{
    return m_mainwindow;
}

void CoreImpl::updateAdditionalContexts(const Context &remove, const Context &add)
{
    m_mainwindow->updateAdditionalContexts(remove, add);
}

bool CoreImpl::hasContext(int context) const
{
    return m_mainwindow->hasContext(context);
}

void CoreImpl::addContextObject(IContext *context)
{
    m_mainwindow->addContextObject(context);
}

void CoreImpl::removeContextObject(IContext *context)
{
    m_mainwindow->removeContextObject(context);
}
