TEMPLATE = lib
TARGET   = Core
DEFINES += CORE_LIBRARY

QT += xml
CONFIG += help

include(../../audiocarverplugin.pri)
include(../../libs/utils/utils.pri)
include(coreplugin_dependencies.pri)

win32-msvc*:QMAKE_CXXFLAGS += -wd4251 -wd4290 -wd4250

INCLUDEPATH += \
    dialogs \
    actionmanager \
    progressmanager

DEPENDPATH += \
    dialogs \
    actionmanager

SOURCES += \
    mainwindow.cpp \
#    tabpositionindicator.cpp \
#    fancyactionbar.cpp \
#    fancytabwidget.cpp \
#    flowlayout.cpp \
    generalsettings.cpp \
    filemanager.cpp \
    uniqueidmanager.cpp \
#    messagemanager.cpp \
#    statusbarmanager.cpp \
    versiondialog.cpp \
    actionmanager/actionmanager.cpp \
    actionmanager/command.cpp \
    actionmanager/actioncontainer.cpp \
    actionmanager/commandsfile.cpp \
#    dialogs/saveitemsdialog.cpp \
    dialogs/settingsdialog.cpp \
    actionmanager/commandmappings.cpp \
    dialogs/shortcutsettings.cpp \
#    progressmanager/progressmanager.cpp \
#    progressmanager/progressview.cpp \
#    progressmanager/progressbar.cpp \
#    progressmanager/futureprogress.cpp \
#    basemode.cpp \
#    statusbarwidget.cpp \
    coreplugin.cpp \
#    variablemanager.cpp \
#    modemanager.cpp \
    coreimpl.cpp \
#    basefilewizard.cpp \
    plugindialog.cpp \
#    inavigationwidgetfactory.cpp \
#    navigationwidget.cpp \
#    manhattanstyle.cpp \
#    minisplitter.cpp \
#    styleanimator.cpp \
    findplaceholder.cpp \
#    rightpane.cpp \
#    sidebar.cpp \
#    fileiconprovider.cpp \
    mimedatabase.cpp \
    icore.cpp \
    dialogs/ioptionspage.cpp \
#    dialogs/iwizard.cpp \
    settingsdatabase.cpp \
    eventfilteringmainwindow.cpp \
#    imode.cpp \
#    helpmanager.cpp \
#    navigationsubwidget.cpp \
#    sidebarwidget.cpp

HEADERS += \
    mainwindow.h \
#    tabpositionindicator.h \
#    fancyactionbar.h \
#    fancytabwidget.h \
#    flowlayout.h \
    generalsettings.h \
    filemanager.h \
    uniqueidmanager.h \
#    messagemanager.h \
#    statusbarmanager.h \
    actionmanager/actioncontainer.h \
    actionmanager/actionmanager.h \
    actionmanager/command.h \
    actionmanager/actionmanager_p.h \
    actionmanager/command_p.h \
    actionmanager/actioncontainer_p.h \
    actionmanager/commandsfile.h \
#    dialogs/saveitemsdialog.h \
    dialogs/settingsdialog.h \
    actionmanager/commandmappings.h \
    dialogs/shortcutsettings.h \
#    dialogs/iwizard.h \
    dialogs/ioptionspage.h \
#    progressmanager/progressmanager_p.h \
#    progressmanager/progressview.h \
#    progressmanager/progressbar.h \
#    progressmanager/futureprogress.h \
#    progressmanager/progressmanager.h \
    icontext.h \
    icore.h \
    ifile.h \
#    ifilefactory.h \
#    imode.h \
    coreconstants.h \
#    ifilewizardextension.h \
    icorelistener.h \
    versiondialog.h \
    core_global.h \
#    basemode.h \
#    statusbarwidget.h \
    coreplugin.h \
#    variablemanager.h \
#    modemanager.h \
    coreimpl.h \
#    basefilewizard.h \
    plugindialog.h \
#    inavigationwidgetfactory.h \
#    navigationwidget.h \
#    manhattanstyle.h \
#    minisplitter.h \
#    styleanimator.h \
    findplaceholder.h \
#    rightpane.h \
#    sidebar.h \
#    fileiconprovider.h \
    mimedatabase.h \
    settingsdatabase.h \
    eventfilteringmainwindow.h \
#    helpmanager.h \
#    navigationsubwidget.h \
#    sidebarwidget.h

FORMS += \
    actionmanager/commandmappings.ui \
    dialogs/saveitemsdialog.ui \
    generalsettings.ui

RESOURCES += \
    core.qrc \
#    fancyactionbar.qrc

win32 {
#    SOURCES += progressmanager/progressmanager_win.cpp
#    LIBS += -lole32
}
else:macx {
#    OBJECTIVE_SOURCES += progressmanager/progressmanager_mac.mm
#    LIBS += -framework AppKit
}
else:unix {
#    SOURCES += progressmanager/progressmanager_x11.cpp

    images.files = images/qtcreator_logo_*.png
    images.path = /share/pixmaps
    INSTALLS += images
}
OTHER_FILES += \
    editormanager/BinFiles.mimetypes.xml \
    ide_version.h.in

QMAKE_SUBSTITUTES += ide_version.h.in
