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

#include "filemanager.h"

#include "icore.h"
#include "ifile.h"
#include "coreconstants.h"

#include <utils/pathchooser.h>

#include <QtCore/QSettings>
#include <QtCore/QFileInfo>
#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QtCore/QTimer>
#include <QtCore/QFileSystemWatcher>
#include <QtCore/QDateTime>
#include <QtGui/QFileDialog>
#include <QtGui/QMessageBox>
#include <QtGui/QMainWindow>

static const char settingsGroupC[] = "RecentFiles";
static const char filesKeyC[] = "Files";

static const char directoryGroupC[] = "Directories";
static const char projectDirectoryKeyC[] = "Projects";
static const char useProjectDirectoryKeyC[] = "UseProjectsDirectory";

namespace Core {
namespace Internal {

struct FileManagerPrivate {
    explicit FileManagerPrivate(QObject *q, QMainWindow *mw);

    QStringList m_recentFiles;
    static const int m_maxRecentFiles = 7;

    QMainWindow *m_mainWindow;
    QString m_lastVisitedDirectory;
    QString m_projectsDirectory;
    bool m_useProjectsDirectory;
};

#ifdef Q_OS_MAC
#   define USE_PROJECTS_DIR true // App is in bizarre places when launched via finder.
#else
#   define USE_PROJECTS_DIR false
#endif

FileManagerPrivate::FileManagerPrivate(QObject *q, QMainWindow *mw)
    :   m_mainWindow(mw)
    ,   m_lastVisitedDirectory(QDir::currentPath())
    ,   m_useProjectsDirectory(USE_PROJECTS_DIR)
{
}

} // namespace Internal

FileManager::FileManager(QMainWindow *mw)
  : QObject(mw),
    d(new Internal::FileManagerPrivate(this, mw))
{
    readSettings();
}

FileManager::~FileManager()
{
    delete d;
    d = 0;
}

QString FileManager::fixFileName(const QString &fileName)
{
    QString s = fileName;
    QFileInfo fi(s);
    if (!fi.exists())
        s = QDir::toNativeSeparators(s);
    else
        s = QDir::toNativeSeparators(fi.canonicalFilePath());

#   ifdef Q_OS_WIN
        s = s.toLower();
#   endif

    return s;
}

QString FileManager::getSaveFileName(const QString &title, const QString &pathIn,
                                     const QString &filter)
{
    const QString &path = pathIn.isEmpty() ? fileDialogInitialDirectory() : pathIn;
    QString fileName;
    bool repeat;
    do {
        repeat = false;
        fileName = QFileDialog::getSaveFileName(
            d->m_mainWindow, title, path, filter, 0, QFileDialog::DontConfirmOverwrite);
        if (!fileName.isEmpty()) {
            if (QFile::exists(fileName)) {
                if (QMessageBox::warning(d->m_mainWindow, tr("Overwrite?"),
                    tr("An item named '%1' already exists at this location. "
                       "Do you want to overwrite it?").arg(fileName),
                    QMessageBox::Yes | QMessageBox::No) == QMessageBox::No) {
                    repeat = true;
                }
            }
        }
    } while (repeat);
    if (!fileName.isEmpty())
        setFileDialogLastVisitedDirectory(QFileInfo(fileName).absolutePath());
    return fileName;
}

QString FileManager::getSaveFileNameWithExtension(const QString &title, const QString &pathIn,
                                                  const QString &filter)
{
    return getSaveFileName(title, pathIn, filter);
}

QString FileManager::getSaveAsFileName(IFile *file, const QString &filter)
{
    if (!file)
        return QLatin1String("");
    QString absoluteFilePath = file->fileName();
    const QFileInfo fi(absoluteFilePath);
    QString fileName = fi.fileName();
    QString path = fi.absolutePath();
    if (absoluteFilePath.isEmpty()) {
        fileName = file->suggestedFileName();
        const QString defaultPath = file->defaultPath();
        if (!defaultPath.isEmpty())
            path = defaultPath;
    }

    absoluteFilePath = getSaveFileName(tr("Save File As"),
        path + QDir::separator() + fileName,
        filter);
    return absoluteFilePath;
}

QStringList FileManager::getOpenFileNames(const QString &filters,
                                          const QString pathIn)
{
    QString path = pathIn;
    if (path.isEmpty()) {
        if (path.isEmpty() && useProjectsDirectory()) {
            path = projectsDirectory();
        }
    }
    const QStringList files = QFileDialog::getOpenFileNames(d->m_mainWindow,
                                                      tr("Open File"),
                                                      path, filters);
    if (!files.isEmpty())
        setFileDialogLastVisitedDirectory(QFileInfo(files.front()).absolutePath());
    return files;
}

void FileManager::addToRecentFiles(const QString &fileName)
{
    if (fileName.isEmpty())
        return;
    QString unifiedForm(fixFileName(fileName));
    QMutableStringListIterator it(d->m_recentFiles);
    while (it.hasNext()) {
        QString recentUnifiedForm(fixFileName(it.next()));
        if (unifiedForm == recentUnifiedForm)
            it.remove();
    }
    if (d->m_recentFiles.count() > d->m_maxRecentFiles)
        d->m_recentFiles.removeLast();
    d->m_recentFiles.prepend(fileName);
}

QStringList FileManager::recentFiles() const
{
    return d->m_recentFiles;
}

void FileManager::saveSettings()
{
    QSettings *s = Core::ICore::instance()->settings();
    s->beginGroup(QLatin1String(settingsGroupC));
    s->setValue(QLatin1String(filesKeyC), d->m_recentFiles);
    s->endGroup();
    s->beginGroup(QLatin1String(directoryGroupC));
    s->setValue(QLatin1String(projectDirectoryKeyC), d->m_projectsDirectory);
    s->setValue(QLatin1String(useProjectDirectoryKeyC), d->m_useProjectsDirectory);
    s->endGroup();
}

void FileManager::readSettings()
{
    const QSettings *s = Core::ICore::instance()->settings();
    d->m_recentFiles.clear();
    QStringList recentFiles = s->value(QLatin1String(settingsGroupC) + QLatin1Char('/') + QLatin1String(filesKeyC), QStringList()).toStringList();
    // clean non-existing files
    foreach (const QString &file, recentFiles) {
        if (QFileInfo(file).isFile())
            d->m_recentFiles.append(QDir::fromNativeSeparators(file)); // from native to guard against old settings
    }

    const QString directoryGroup = QLatin1String(directoryGroupC) + QLatin1Char('/');
    const QString settingsProjectDir = s->value(directoryGroup + QLatin1String(projectDirectoryKeyC),
                                       QString()).toString();
    if (!settingsProjectDir.isEmpty() && QFileInfo(settingsProjectDir).isDir()) {
        d->m_projectsDirectory = settingsProjectDir;
    } else {
        d->m_projectsDirectory = Utils::PathChooser::homePath();
    }
    d->m_useProjectsDirectory = s->value(directoryGroup + QLatin1String(useProjectDirectoryKeyC),
                                         d->m_useProjectsDirectory).toBool();
}

QString FileManager::fileDialogInitialDirectory() const
{
    return d->m_lastVisitedDirectory;
}

QString FileManager::projectsDirectory() const
{
    return d->m_projectsDirectory;
}

void FileManager::setProjectsDirectory(const QString &dir)
{
    d->m_projectsDirectory = dir;
}

bool FileManager::useProjectsDirectory() const
{
    return d->m_useProjectsDirectory;
}

void FileManager::setUseProjectsDirectory(bool useProjectsDirectory)
{
    d->m_useProjectsDirectory = useProjectsDirectory;
}

QString FileManager::fileDialogLastVisitedDirectory() const
{
    return d->m_lastVisitedDirectory;
}

void FileManager::setFileDialogLastVisitedDirectory(const QString &directory)
{
    d->m_lastVisitedDirectory = directory;
}

} // namespace Core
