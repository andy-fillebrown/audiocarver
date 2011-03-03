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

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <coreplugin/core_global.h>

#include <QtCore/QObject>
#include <QtCore/QStringList>

QT_BEGIN_NAMESPACE

class QMainWindow;

QT_END_NAMESPACE

namespace Core {

class ICore;
class IContext;
class IFile;

namespace Internal {
struct FileManagerPrivate;
}

class CORE_EXPORT FileManager : public QObject
{
    Q_OBJECT
public:
    explicit FileManager(QMainWindow *ew);
    virtual ~FileManager();

    // recent files
    void addToRecentFiles(const QString &fileName);
    QStringList recentFiles() const;
    void saveSettings();

    // helper methods
    static QString fixFileName(const QString &fileName);

    QStringList getOpenFileNames(const QString &filters,
                                 const QString path = QString());
    QString getSaveFileName(const QString &title, const QString &pathIn,
                            const QString &filter = QString());
    QString getSaveFileNameWithExtension(const QString &title, const QString &pathIn,
                                         const QString &filter);
    QString getSaveAsFileName(IFile *file, const QString &filter = QString());

    QString fileDialogLastVisitedDirectory() const;
    void setFileDialogLastVisitedDirectory(const QString &);

    QString fileDialogInitialDirectory() const;

    bool useProjectsDirectory() const;
    void setUseProjectsDirectory(bool);

    QString projectsDirectory() const;
    void setProjectsDirectory(const QString &);

private:
    void readSettings();

    Internal::FileManagerPrivate *d;
};

} // namespace Core

#endif // FILEMANAGER_H
