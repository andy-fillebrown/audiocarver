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

#include "mainwindow.h"
#include "actioncontainer.h"
#include "command.h"
#include "actionmanager_p.h"
#include "coreimpl.h"
#include "coreconstants.h"
#include "filemanager.h"
#include "generalsettings.h"
#include "plugindialog.h"
#include "shortcutsettings.h"

#include "settingsdialog.h"
#include "versiondialog.h"
#include "uniqueidmanager.h"

#include <coreplugin/findplaceholder.h>
#include <coreplugin/icorelistener.h>
#include <coreplugin/settingsdatabase.h>
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
    ,   m_versionDialog(0)
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

    registerDefaultContainers();
    registerDefaultActions();
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
    // reading the shortcut settings must be done after all shortcuts have been registered
    m_actionManager->initialize();

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

void MainWindow::registerDefaultContainers()
{
    ActionManagerPrivate *am = m_actionManager;
    ActionContainer *menubar = am->createMenuBar(Constants::MENU_BAR);
    {
#   ifndef Q_WS_MAC // System menu bar on Mac
        setMenuBar(menubar->menuBar());
#   endif
    }
    menubar->appendGroup(Constants::G_FILE);
    menubar->appendGroup(Constants::G_EDIT);
    menubar->appendGroup(Constants::G_VIEW);
    menubar->appendGroup(Constants::G_TOOLS);
    menubar->appendGroup(Constants::G_WINDOW);
    menubar->appendGroup(Constants::G_HELP);

    // File Menu
    ActionContainer *filemenu = am->createMenu(Constants::M_FILE);
    menubar->addMenu(filemenu, Constants::G_FILE);
    filemenu->menu()->setTitle(tr("&File"));
    filemenu->appendGroup(Constants::G_FILE_NEW);
    filemenu->appendGroup(Constants::G_FILE_OPEN);
    filemenu->appendGroup(Constants::G_FILE_SAVE);
    filemenu->appendGroup(Constants::G_FILE_OTHER);

    // Edit Menu
    ActionContainer *medit = am->createMenu(Constants::M_EDIT);
    menubar->addMenu(medit, Constants::G_EDIT);
    medit->menu()->setTitle(tr("&Edit"));
    medit->appendGroup(Constants::G_EDIT_UNDOREDO);
    medit->appendGroup(Constants::G_EDIT_COPYPASTE);
    medit->appendGroup(Constants::G_EDIT_SELECTALL);
    medit->appendGroup(Constants::G_EDIT_OTHER);

    // Tools Menu
    ActionContainer *ac = am->createMenu(Constants::M_TOOLS);
    menubar->addMenu(ac, Constants::G_TOOLS);
    ac->menu()->setTitle(tr("&Tools"));

    // Window Menu
    ActionContainer *mwindow = am->createMenu(Constants::M_WINDOW);
    menubar->addMenu(mwindow, Constants::G_WINDOW);
    mwindow->menu()->setTitle(tr("&Window"));
    mwindow->appendGroup(Constants::G_WINDOW_SIZE);
    mwindow->appendGroup(Constants::G_WINDOW_OTHER);

    // Help Menu
    ac = am->createMenu(Constants::M_HELP);
    menubar->addMenu(ac, Constants::G_HELP);
    ac->menu()->setTitle(tr("&Help"));
    ac->appendGroup(Constants::G_HELP_ABOUT);
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

void MainWindow::registerDefaultActions()
{
    ActionManagerPrivate *am = m_actionManager;
    ActionContainer *mfile = am->actionContainer(Constants::M_FILE);
    ActionContainer *medit = am->actionContainer(Constants::M_EDIT);
    ActionContainer *mtools = am->actionContainer(Constants::M_TOOLS);
    ActionContainer *mwindow = am->actionContainer(Constants::M_WINDOW);
    ActionContainer *mhelp = am->actionContainer(Constants::M_HELP);

    Context globalContext(Constants::C_GLOBAL);

    // File menu separators
    Command *cmd = createSeparator(am, this, QLatin1String(PRO_NAME_STR".File.Sep.Other"), globalContext);
    mfile->addAction(cmd, Constants::G_FILE_OTHER);

    // Edit menu separators
    cmd = createSeparator(am, this, QLatin1String(PRO_NAME_STR".Edit.Sep.CopyPaste"), globalContext);
    medit->addAction(cmd, Constants::G_EDIT_COPYPASTE);

    cmd = createSeparator(am, this, QLatin1String(PRO_NAME_STR".Edit.Sep.SelectAll"), globalContext);
    medit->addAction(cmd, Constants::G_EDIT_SELECTALL);

    // Tools menu separators
    cmd = createSeparator(am, this, QLatin1String(PRO_NAME_STR".Tools.Sep.Options"), globalContext);
    mtools->addAction(cmd, Constants::G_DEFAULT_THREE);

    // Exit Action
    QIcon icon = QIcon::fromTheme(QLatin1String("application-exit"));
    m_exitAction = new QAction(icon, tr("E&xit"), this);
    cmd = am->registerAction(m_exitAction, Constants::EXIT, globalContext);
    cmd->setDefaultKeySequence(QKeySequence(tr("Ctrl+Q")));
    mfile->addAction(cmd, Constants::G_FILE_OTHER);
    connect(m_exitAction, SIGNAL(triggered()), this, SLOT(exit()));

    // Undo Action
    icon = QIcon::fromTheme(QLatin1String("edit-undo"), QIcon(Constants::ICON_UNDO));
    QAction *tmpaction = new QAction(icon, tr("&Undo"), this);
    cmd = am->registerAction(tmpaction, Constants::UNDO, globalContext);
    cmd->setDefaultKeySequence(QKeySequence::Undo);
    cmd->setAttribute(Command::CA_UpdateText);
    cmd->setDefaultText(tr("&Undo"));
    medit->addAction(cmd, Constants::G_EDIT_UNDOREDO);
//    tmpaction->setEnabled(false);

    // Redo Action
    icon = QIcon::fromTheme(QLatin1String("edit-redo"), QIcon(Constants::ICON_REDO));
    tmpaction = new QAction(icon, tr("&Redo"), this);
    cmd = am->registerAction(tmpaction, Constants::REDO, globalContext);
    cmd->setDefaultKeySequence(QKeySequence::Redo);
    cmd->setAttribute(Command::CA_UpdateText);
    cmd->setDefaultText(tr("&Redo"));
    medit->addAction(cmd, Constants::G_EDIT_UNDOREDO);
//    tmpaction->setEnabled(false);

    // Cut Action
    icon = QIcon::fromTheme(QLatin1String("edit-cut"), QIcon(Constants::ICON_CUT));
    tmpaction = new QAction(icon, tr("Cu&t"), this);
    cmd = am->registerAction(tmpaction, Constants::CUT, globalContext);
    cmd->setDefaultKeySequence(QKeySequence::Cut);
    medit->addAction(cmd, Constants::G_EDIT_COPYPASTE);
//    tmpaction->setEnabled(false);

    // Copy Action
    icon = QIcon::fromTheme(QLatin1String("edit-copy"), QIcon(Constants::ICON_COPY));
    tmpaction = new QAction(icon, tr("&Copy"), this);
    cmd = am->registerAction(tmpaction, Constants::COPY, globalContext);
    cmd->setDefaultKeySequence(QKeySequence::Copy);
    medit->addAction(cmd, Constants::G_EDIT_COPYPASTE);
//    tmpaction->setEnabled(false);

    // Paste Action
    icon = QIcon::fromTheme(QLatin1String("edit-paste"), QIcon(Constants::ICON_PASTE));
    tmpaction = new QAction(icon, tr("&Paste"), this);
    cmd = am->registerAction(tmpaction, Constants::PASTE, globalContext);
    cmd->setDefaultKeySequence(QKeySequence::Paste);
    medit->addAction(cmd, Constants::G_EDIT_COPYPASTE);
//    tmpaction->setEnabled(false);

    // Select All
    icon = QIcon::fromTheme(QLatin1String("edit-select-all"));
    tmpaction = new QAction(icon, tr("&Select All"), this);
    cmd = am->registerAction(tmpaction, Constants::SELECTALL, globalContext);
    cmd->setDefaultKeySequence(QKeySequence::SelectAll);
    medit->addAction(cmd, Constants::G_EDIT_SELECTALL);
//    tmpaction->setEnabled(false);

    // Options Action
    m_optionsAction = new QAction(tr("&Options..."), this);
    cmd = am->registerAction(m_optionsAction, Constants::OPTIONS, globalContext);
    {
#   ifdef Q_WS_MAC
        cmd->setDefaultKeySequence(QKeySequence("Ctrl+,"));
        cmd->action()->setMenuRole(QAction::PreferencesRole);
#   endif
    }
    mtools->addAction(cmd, Constants::G_DEFAULT_THREE);
    connect(m_optionsAction, SIGNAL(triggered()), this, SLOT(showOptionsDialog()));

    {
#   ifdef Q_WS_MAC
        // Minimize Action
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
        cmd = createSeparator(am, this, QLatin1String("SuperConductor.Window.Sep.Size"), globalContext);
        mwindow->addAction(cmd, Constants::G_WINDOW_SIZE);
#   endif
    }

    {
#   ifndef Q_WS_MAC
        // Full Screen Action
        m_toggleFullScreenAction = new QAction(tr("Full Screen"), this);
        m_toggleFullScreenAction->setCheckable(true);
        cmd = am->registerAction(m_toggleFullScreenAction, Constants::TOGGLE_FULLSCREEN, globalContext);
        cmd->setDefaultKeySequence(QKeySequence("Ctrl+Shift+F11"));
        mwindow->addAction(cmd, Constants::G_WINDOW_SIZE);
        connect(m_toggleFullScreenAction, SIGNAL(triggered(bool)), this, SLOT(setFullScreen(bool)));
#   endif
    }

    // About Project Action
    icon = QIcon::fromTheme(QLatin1String("help-about"));
    {
#   ifdef Q_WS_MAC
        tmpaction = new QAction(icon, tr("About &"PRO_NAME_STR), this); // it's convention not to add dots to the about menu
#   else
        tmpaction = new QAction(icon, tr("About &"PRO_NAME_STR"..."), this);
#   endif
    }
    cmd = am->registerAction(tmpaction, Constants::ABOUT_PROJECT, globalContext);
    mhelp->addAction(cmd, Constants::G_HELP_ABOUT);
    tmpaction->setEnabled(true);
    {
#   ifdef Q_WS_MAC
        cmd->action()->setMenuRole(QAction::ApplicationSpecificRole);
#   endif
    }
    connect(tmpaction, SIGNAL(triggered()), this,  SLOT(aboutAudioCarver()));

    // About Plugins Action
    tmpaction = new QAction(tr("About &Plugins..."), this);
    cmd = am->registerAction(tmpaction, Constants::ABOUT_PLUGINS, globalContext);
    mhelp->addAction(cmd, Constants::G_HELP_ABOUT);
    tmpaction->setEnabled(true);
    {
#   ifdef Q_WS_MAC
        cmd->action()->setMenuRole(QAction::ApplicationSpecificRole);
#   endif
    }
    connect(tmpaction, SIGNAL(triggered()), this,  SLOT(aboutPlugins()));

    {
#   ifndef Q_WS_MAC // doesn't have the "About" actions in the Help menu
        tmpaction = new QAction(this);
        tmpaction->setSeparator(true);
        cmd = am->registerAction(tmpaction, PRO_NAME_STR".Help.Sep.About", globalContext);
        mhelp->addAction(cmd, Constants::G_HELP_ABOUT);
#   endif
    }
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
    QTimer::singleShot(0, this,  SLOT(close()));
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
        {
#       ifdef Q_WS_MAC
            bool minimized = isMinimized();
            if (debugMainWindow)
                qDebug() << "main window state changed to minimized=" << minimized;
            m_minimizeAction->setEnabled(!minimized);
            m_zoomAction->setEnabled(!minimized);
#       else
            bool isFullScreen = (windowState() & Qt::WindowFullScreen) != 0;
            m_toggleFullScreenAction->setChecked(isFullScreen);
#       endif
        }
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

// TODO compat for <= 2.1, remove later
static const char *geometryKey = "Geometry";
static const char *maxKey = "Maximized";
static const char *fullScreenKey = "FullScreen";

void MainWindow::readSettings()
{
    m_settings->beginGroup(QLatin1String(settingsGroup));

    // TODO compat for <= 2.1, remove later
    if (m_settings->contains(QLatin1String(geometryKey))) {
        const QVariant geom = m_settings->value(QLatin1String(geometryKey));
        if (geom.isValid()) {
            setGeometry(geom.toRect());
        } else {
            resize(1024, 700);
        }
        if (m_settings->value(QLatin1String(maxKey), false).toBool())
            setWindowState(Qt::WindowMaximized);
        setFullScreen(m_settings->value(QLatin1String(fullScreenKey), false).toBool());

        m_settings->remove(QLatin1String(geometryKey));
        m_settings->remove(QLatin1String(maxKey));
        m_settings->remove(QLatin1String(fullScreenKey));
    } else {
        if (!restoreGeometry(m_settings->value(QLatin1String(windowGeometryKey)).toByteArray()))
            resize(1024, 700);
        restoreState(m_settings->value(QLatin1String(windowStateKey)).toByteArray());
    }

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

void MainWindow::aboutAudioCarver()
{
    if (!m_versionDialog) {
        m_versionDialog = new VersionDialog(this);
        connect(m_versionDialog, SIGNAL(finished(int)),
                this, SLOT(destroyVersionDialog()));
    }
    m_versionDialog->show();
}

void MainWindow::destroyVersionDialog()
{
    if (m_versionDialog) {
        m_versionDialog->deleteLater();
        m_versionDialog = 0;
    }
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
