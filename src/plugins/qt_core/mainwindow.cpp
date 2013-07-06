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

#include "mainwindow.h"

#include "actioncontainer.h"
#include "command.h"
#include "actionmanager_p.h"
#include "coreimpl.h"
#include "filemanager.h"
#include "generalsettings.h"
#include "plugindialog.h"
#include "qt_core_constants.h"
#include "shortcutsettings.h"

#include "settingsdialog.h"
#include "versiondialog.h"
#include "uniqueidmanager.h"

#include <imainwindowextension.h>
#include <qt_core/findplaceholder.h>
#include <qt_core/icorelistener.h>
#include <qt_core/settingsdatabase.h>
#include <utils/pathchooser.h>
#include <utils/stringutils.h>
#include <extensionsystem/pluginmanager.h>

#include <QtCore/QDebug>
#include <QtCore/QFileInfo>
#include <QtCore/QtPlugin>
#include <QtCore/QTimer>

#include <QtGui/QApplication>
#include <QtGui/QCloseEvent>
#include <QtGui/QMenu>

using namespace Core;
using namespace Core::Internal;

enum { debugMainWindow = 0 };

MainWindow::MainWindow()
    :   EventFilteringMainWindow()
    ,   m_coreImpl(new CoreImpl(this))
    ,   m_uniqueIDManager(new UniqueIDManager())
    ,   m_additionalContexts(Constants::C_GLOBAL)
    ,   m_settings(ExtensionSystem::PluginManager::instance()->settings())
    ,   m_globalSettings(new QSettings(QSettings::IniFormat, QSettings::SystemScope,
                                       QLatin1String(Constants::PRO_AUTHOR),
                                       QLatin1String(PRO_NAME_STR), this))
    ,   m_settingsDatabase(new SettingsDatabase(QFileInfo(m_settings->fileName()).path(),
                                                QLatin1String(PRO_NAME_STR),
                                                this))
    ,   m_actionManager(new ActionManagerPrivate(this))
    ,   m_fileManager(new FileManager(this))
    ,   m_activeContext(0)
    ,   m_generalSettings(new GeneralSettings)
    ,   m_shortcutSettings(new ShortcutSettings)
    ,   m_exitAction(0)
    ,   m_optionsAction(0)
#   ifdef Q_WS_MAC
    ,   m_minimizeAction(0)
    ,   m_zoomAction(0)
#   endif
{
    setWindowTitle(tr(PRO_NAME_STR));
    {
#   ifndef Q_WS_MAC
        QApplication::setWindowIcon(QIcon(QLatin1String(Constants::ICON_PROLOGO_128)));
#   endif
    }
    QCoreApplication::setApplicationName(QLatin1String(PRO_NAME_STR));
    QCoreApplication::setApplicationVersion(QLatin1String(Core::Constants::PRO_VERSION_LONG));
    QCoreApplication::setOrganizationName(QLatin1String(Constants::PRO_AUTHOR));
    QSettings::setDefaultFormat(QSettings::IniFormat);
}

MainWindow::~MainWindow()
{
    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();

    pm->removeObject(m_shortcutSettings);
    pm->removeObject(m_generalSettings);
    delete m_shortcutSettings;
    m_shortcutSettings = 0;
    delete m_generalSettings;
    m_generalSettings = 0;
    delete m_settings;
    m_settings = 0;

    delete m_uniqueIDManager;
    m_uniqueIDManager = 0;

    pm->removeObject(m_coreImpl);
    delete m_coreImpl;
    m_coreImpl = 0;
}

bool MainWindow::init(QString *errorMessage)
{
    Q_UNUSED(errorMessage)

    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    pm->addObject(m_coreImpl);

    pm->addObject(m_generalSettings);
    pm->addObject(m_shortcutSettings);

    return true;
}

void MainWindow::extensionsInitialized()
{
    m_actionManager->initialize();

    registerContainers();
    registerActions();

    // Reading the shortcut settings must be done after all shortcuts have been
    // registered.
    readSettings();

    updateContext();

    emit m_coreImpl->coreAboutToOpen();
    show();
    emit m_coreImpl->coreOpened();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    emit m_coreImpl->saveSettingsRequested();

    const QList<ICoreListener *> listeners =
        ExtensionSystem::PluginManager::instance()->getObjects<ICoreListener>();
    foreach (ICoreListener *listener, listeners) {
        if (!listener->coreAboutToClose()) {
            event->ignore();
            return;
        }
    }

    emit m_coreImpl->coreAboutToClose();

    writeSettings();

    event->accept();
}

IContext *MainWindow::currentContextObject() const
{
    return m_activeContext;
}

void MainWindow::registerContainers()
{
    QStringList menuBarGroups;
    menuBarGroups
            << Constants::G_FILE
            << Constants::G_TOOLS
            << Constants::G_WINDOW
            << Constants::G_HELP;

    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    QList<IMainWindowExtension*> mwx_list = pm->getObjects<IMainWindowExtension>();
    foreach (IMainWindowExtension *mwx, mwx_list)
        mwx->initMenuBarGroups(menuBarGroups);

    ActionManagerPrivate *am = m_actionManager;
    ActionContainer *menubar = am->createMenuBar(Constants::MENU_BAR);
#   ifndef Q_WS_MAC // System menu bar on Mac
    {   setMenuBar(menubar->menuBar());
    }
#   endif
    foreach (const QString &menuBarGroup, menuBarGroups) {
        menubar->appendGroup(menuBarGroup);
        QString id;
        QString title;
        QStringList groups;
        foreach (IMainWindowExtension *mwx, mwx_list)
            mwx->initMenuGroups(menuBarGroup, id, title, groups);
        if (Constants::G_FILE == menuBarGroup) {
            id = Constants::M_FILE;
            title = tr("&File");
            groups  << Constants::G_FILE_OTHER;
        } else if (Constants::G_TOOLS == menuBarGroup) {
            id = Constants::M_TOOLS;
            title = tr("&Tools");
        } else if (Constants::G_WINDOW == menuBarGroup) {
            id = Constants::M_WINDOW;
            title = tr("&Window");
            groups.insert(0, Constants::G_WINDOW_SIZE);
            groups  << Constants::G_WINDOW_OTHER;
        } else if (Constants::G_HELP == menuBarGroup) {
            id = Constants::M_HELP;
            title = tr("&Help");
            groups  << Constants::G_HELP_ABOUTPLUGINS;
        }
        ActionContainer *menu = am->createMenu(id);
        menubar->addMenu(menu, menuBarGroup);
        menu->menu()->setTitle(title);
        foreach (const QString &group, groups)
            menu->appendGroup(group);
    }
}

static Command *createSeparator(ActionManager *am, QObject *parent,
                                const QString &name,
                                const Context &context)
{
    QAction *tmpaction = new QAction(parent);
    tmpaction->setSeparator(true);
    Command *cmd = am->registerAction(tmpaction, name, context);
    return cmd;
}

void MainWindow::registerActions()
{
    ActionManagerPrivate *am = m_actionManager;
    ActionContainer *mfile = am->actionContainer(Constants::M_FILE);
    ActionContainer *mtools = am->actionContainer(Constants::M_TOOLS);
    ActionContainer *mwindow = am->actionContainer(Constants::M_WINDOW);
    ActionContainer *mhelp = am->actionContainer(Constants::M_HELP);

    Context globalContext(Constants::C_GLOBAL);

    QIcon icon;
    QAction *action = 0;
    Command *cmd = 0;

    // File menu separators
    cmd = createSeparator(am, this, QLatin1String(PRO_NAME_STR".File.Sep.Other"), globalContext);
    mfile->addAction(cmd, Constants::G_FILE_OTHER);

    // Exit Action
    icon = QIcon::fromTheme(QLatin1String("application-exit"));
    m_exitAction = new QAction(icon, tr("E&xit"), this);
    cmd = am->registerAction(m_exitAction, Constants::EXIT, globalContext);
    cmd->setDefaultKeySequence(QKeySequence(tr("Ctrl+Q")));
    mfile->addAction(cmd, Constants::G_FILE_OTHER);
    connect(m_exitAction, SIGNAL(triggered()), this, SLOT(exit()));

    // Tools menu separators
    cmd = createSeparator(am, this, QLatin1String(PRO_NAME_STR".Tools.Sep.Options"), globalContext);
    mtools->addAction(cmd, Constants::G_DEFAULT_THREE);

    // Options Action
    m_optionsAction = new QAction(tr("&Options..."), this);
    cmd = am->registerAction(m_optionsAction, Constants::OPTIONS, globalContext);
#   ifdef Q_WS_MAC
    {   cmd->setDefaultKeySequence(QKeySequence("Ctrl+,"));
        cmd->action()->setMenuRole(QAction::PreferencesRole);
    }
#   endif
    mtools->addAction(cmd, Constants::G_DEFAULT_THREE);
    connect(m_optionsAction, SIGNAL(triggered()), this, SLOT(showOptionsDialog()));

#   ifdef Q_WS_MAC
    {   // Minimize Action
        m_minimizeAction = new QAction(tr("Minimize"), this);
        cmd = am->registerAction(m_minimizeAction, Constants::MINIMIZE_WINDOW, globalContext);
        cmd->setDefaultKeySequence(QKeySequence("Ctrl+M"));
        mwindow->addAction(cmd, Constants::G_WINDOW_SIZE);
        connect(m_minimizeAction, SIGNAL(triggered()), this, SLOT(showMinimized()));

        // Zoom Action
        m_zoomAction = new QAction(tr("Zoom"), this);
        cmd = am->registerAction(m_zoomAction, Constants::ZOOM_WINDOW, globalContext);
        mwindow->addAction(cmd, Constants::G_WINDOW_SIZE);
        connect(m_zoomAction, SIGNAL(triggered()), this, SLOT(showMaximized()));

        // Window separator
        cmd = createSeparator(am, this, QLatin1String(PRO_NAME_STR".Window.Sep.Size"), globalContext);
        mwindow->addAction(cmd, Constants::G_WINDOW_SIZE);
    }
#   else
    {   // Full Screen Action
        m_toggleFullScreenAction = new QAction(tr("Full Screen"), this);
        m_toggleFullScreenAction->setCheckable(true);
        cmd = am->registerAction(m_toggleFullScreenAction, Constants::TOGGLE_FULLSCREEN, globalContext);
        cmd->setDefaultKeySequence(QKeySequence("Ctrl+Shift+F11"));
        mwindow->addAction(cmd, Constants::G_WINDOW_SIZE);
        connect(m_toggleFullScreenAction, SIGNAL(triggered(bool)), this, SLOT(setFullScreen(bool)));
    }
#   endif

    // About Plugins Action
    action = new QAction(tr("About &Plugins..."), this);
    cmd = am->registerAction(action, Constants::ABOUTPLUGINS, globalContext);
    mhelp->addAction(cmd, Constants::G_HELP_ABOUTPLUGINS);
    action->setEnabled(true);
#   ifdef Q_WS_MAC
    {   cmd->action()->setMenuRole(QAction::ApplicationSpecificRole);
    }
#   endif
    connect(action, SIGNAL(triggered()), this,  SLOT(aboutPlugins()));

#   ifndef Q_WS_MAC // doesn't have the "About" actions in the Help menu
    {   action = new QAction(this);
        action->setSeparator(true);
        cmd = am->registerAction(action, PRO_NAME_STR".Help.Sep.About", globalContext);
        mhelp->addAction(cmd, Constants::G_HELP_ABOUTPLUGINS);
    }
#   endif

    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    QList<IMainWindowExtension*> mwx_list = pm->getObjects<IMainWindowExtension>();
    foreach (IMainWindowExtension *mwx, mwx_list)
        mwx->initActions();
}

bool MainWindow::showOptionsDialog(const QString &category,
                                   const QString &page,
                                   QWidget *parent)
{
    emit m_coreImpl->optionsDialogRequested();
    if (!parent)
        parent = this;
    SettingsDialog *dialog = SettingsDialog::getSettingsDialog(parent, category, page);
    return dialog->execDialog();
}

void MainWindow::exit()
{
    // this function is most likely called from a user action
    // that is from an event handler of an object
    // since on close we are going to delete everything
    // so to prevent the deleting of that object we
    // just append it
    QTimer::singleShot(0, this, SLOT(close()));
}

ActionManager *MainWindow::actionManager() const
{
    return m_actionManager;
}

FileManager *MainWindow::fileManager() const
{
    return m_fileManager;
}

UniqueIDManager *MainWindow::uniqueIDManager() const
{
    return m_uniqueIDManager;
}

QSettings *MainWindow::settings(QSettings::Scope scope) const
{
    if (scope == QSettings::UserScope)
        return m_settings;
    else
        return m_globalSettings;
}

IContext *MainWindow::contextObject(QWidget *widget)
{
    return m_contextWidgets.value(widget);
}

void MainWindow::addContextObject(IContext *context)
{
    if (!context)
        return;
    QWidget *widget = context->widget();
    if (m_contextWidgets.contains(widget))
        return;

    m_contextWidgets.insert(widget, context);
}

void MainWindow::removeContextObject(IContext *context)
{
    if (!context)
        return;

    QWidget *widget = context->widget();
    if (!m_contextWidgets.contains(widget))
        return;

    m_contextWidgets.remove(widget);
    if (m_activeContext == context)
        updateContextObject(0);
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    if (e->type() == QEvent::ActivationChange) {
        if (isActiveWindow()) {
            if (debugMainWindow)
                qDebug() << "main window activated";
            emit windowActivated();
        }
    } else if (e->type() == QEvent::WindowStateChange) {
#       ifdef Q_WS_MAC
        {   bool minimized = isMinimized();
            if (debugMainWindow)
                qDebug() << "main window state changed to minimized=" << minimized;
            m_minimizeAction->setEnabled(!minimized);
            m_zoomAction->setEnabled(!minimized);
        }
#       else
        {   bool isFullScreen = (windowState() & Qt::WindowFullScreen) != 0;
            m_toggleFullScreenAction->setChecked(isFullScreen);
        }
#       endif
    }
}

void MainWindow::updateContextObject(IContext *context)
{
    if (context == m_activeContext)
        return;
    IContext *oldContext = m_activeContext;
    m_activeContext = context;
    if (!context || oldContext != m_activeContext) {
        emit m_coreImpl->contextAboutToChange(context);
        updateContext();
        if (debugMainWindow) {
            qDebug() << "new context object =" << context << (context ? context->widget() : 0)
                     << (context ? context->widget()->metaObject()->className() : 0);
        }
    }
}

void MainWindow::resetContext()
{
    updateContextObject(0);
}

void MainWindow::aboutToShutdown()
{
    m_activeContext = 0;
    hide();
}

static const char *settingsGroup = "MainWindow";
static const char *windowGeometryKey = "WindowGeometry";
static const char *windowStateKey = "WindowState";

void MainWindow::readSettings()
{
    m_settings->beginGroup(QLatin1String(settingsGroup));

    if (!restoreGeometry(m_settings->value(QLatin1String(windowGeometryKey)).toByteArray()))
        resize(1024, 700);
    restoreState(m_settings->value(QLatin1String(windowStateKey)).toByteArray());

    m_settings->endGroup();
}

void MainWindow::writeSettings()
{
    m_settings->beginGroup(QLatin1String(settingsGroup));

    m_settings->setValue(QLatin1String(windowGeometryKey), saveGeometry());
    m_settings->setValue(QLatin1String(windowStateKey), saveState());

    m_settings->endGroup();

    m_fileManager->saveSettings();
    m_actionManager->saveSettings(m_settings);
}

void MainWindow::updateAdditionalContexts(const Context &remove, const Context &add)
{
    foreach (const int context, remove) {
        if (context == 0)
            continue;

        int index = m_additionalContexts.indexOf(context);
        if (index != -1) {
            m_additionalContexts.removeAt(index);
        }
    }

    foreach (const int context, add) {
        if (context == 0)
            continue;

        if (!m_additionalContexts.contains(context)) {
            m_additionalContexts.prepend(context);
        }
    }

    updateContext();
}

bool MainWindow::hasContext(int context) const
{
    return m_actionManager->hasContext(context);
}

void MainWindow::updateContext()
{
    Context contexts;

    if (m_activeContext)
        contexts.add(m_activeContext->context());

    contexts.add(m_additionalContexts);

    Context uniquecontexts;
    for (int i = 0; i < contexts.size(); ++i) {
        const int c = contexts.at(i);
        if (!uniquecontexts.contains(c)) {
            uniquecontexts.add(c);
        }
    }

    m_actionManager->setContext(uniquecontexts);
    emit m_coreImpl->contextChanged(m_activeContext, m_additionalContexts);
}

void MainWindow::aboutPlugins()
{
    PluginDialog dialog(this);
    dialog.exec();
}

void MainWindow::setFullScreen(bool on)
{
    if (bool(windowState() & Qt::WindowFullScreen) == on)
        return;

    if (on)
        setWindowState(windowState() | Qt::WindowFullScreen);
    else
        setWindowState(windowState() & ~Qt::WindowFullScreen);
}
