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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "eventfilteringmainwindow.h"
#include "icontext.h"
#include "icore.h"

#include <QtCore/QMap>
#include <QtGui/QColor>

QT_BEGIN_NAMESPACE
class QSettings;
class QShortcut;
class QPrinter;
class QToolButton;
QT_END_NAMESPACE

namespace Core {

class ActionManager;
class StatusBarWidget;
class FileManager;
class HelpManager;
class IWizard;
class MessageManager;
class MimeDatabase;
class ModeManager;
class ProgressManager;
class NavigationWidget;
class RightPaneWidget;
class SettingsDatabase;
class UniqueIDManager;
class VariableManager;

namespace Internal {

class ActionManagerPrivate;
class CoreImpl;
class FancyTabWidget;
class GeneralSettings;
class ProgressManagerPrivate;
class ShortcutSettings;
class StatusBarManager;
class VersionDialog;

class MainWindow : public EventFilteringMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

    bool init(QString *errorMessage);
    void extensionsInitialized();
    void aboutToShutdown();

    IContext *contextObject(QWidget *widget);
    void addContextObject(IContext *contex);
    void removeContextObject(IContext *contex);
    void resetContext();

    Core::ActionManager *actionManager() const;
    Core::FileManager *fileManager() const;
    Core::UniqueIDManager *uniqueIDManager() const;
    Core::MimeDatabase *mimeDatabase() const;

    QSettings *settings(QSettings::Scope scope) const;
    inline SettingsDatabase *settingsDatabase() const { return m_settingsDatabase; }
    IContext * currentContextObject() const;

    void updateAdditionalContexts(const Context &remove, const Context &add);
    bool hasContext(int context) const;

signals:
    void windowActivated();

public slots:
    void exit();
    void setFullScreen(bool on);

    bool showOptionsDialog(const QString &category = QString(),
                           const QString &page = QString(),
                           QWidget *parent = 0);

    bool showWarningWithOptions(const QString &title, const QString &text,
                                const QString &details = QString(),
                                const QString &settingsCategory = QString(),
                                const QString &settingsId = QString(),
                                QWidget *parent = 0);

protected:
    virtual void changeEvent(QEvent *e);
    virtual void closeEvent(QCloseEvent *event);
    virtual void dragEnterEvent(QDragEnterEvent *event);
    virtual void dropEvent(QDropEvent *event);

private slots:
    void aboutAudioCarver();
    void aboutPlugins();
    void updateFocusWidget(QWidget *old, QWidget *now);
    void destroyVersionDialog();

private:
    void updateContextObject(IContext *context);
    void updateContext();

    void registerDefaultContainers();
    void registerDefaultActions();

    void readSettings();
    void writeSettings();

    CoreImpl *m_coreImpl;
    UniqueIDManager *m_uniqueIDManager;
    Context m_additionalContexts;
    QSettings *m_settings;
    QSettings *m_globalSettings;
    SettingsDatabase *m_settingsDatabase;
    ActionManagerPrivate *m_actionManager;
    FileManager *m_fileManager;
    MimeDatabase *m_mimeDatabase;
    VersionDialog *m_versionDialog;

    IContext *m_activeContext;

    QMap<QWidget *, IContext *> m_contextWidgets;

    GeneralSettings *m_generalSettings;
    ShortcutSettings *m_shortcutSettings;

    // actions
    QAction *m_exitAction;
    QAction *m_optionsAction;
    QAction *m_toggleFullScreenAction;
#ifdef Q_WS_MAC
    QAction *m_minimizeAction;
    QAction *m_zoomAction;
#endif
};

} // namespace Internal
} // namespace Core

#endif // MAINWINDOW_H
