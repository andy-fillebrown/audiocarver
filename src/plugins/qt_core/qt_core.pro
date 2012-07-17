TARGET = QtCorePlugin
TEMPLATE = lib

load(../../plugin.prf)
load(../qt_core/qt_core_dependencies.prf)

QMAKE_SUBSTITUTES *= \
    pro_version.h.in \

DEFINES *= \
    CORE_LIBRARY \

HEADERS = \
    actionmanager/actioncontainer.h \
    actionmanager/actioncontainer_p.h \
    actionmanager/actionmanager.h \
    actionmanager/actionmanager_p.h \
    actionmanager/command.h \
    actionmanager/command_p.h \
    actionmanager/commandmappings.h \
    actionmanager/commandsfile.h \
    \
    dialogs/ioptionspage.h \
    dialogs/settingsdialog.h \
    dialogs/shortcutsettings.h \
    \
    interfaces/imainwindowextension.h \
    \
    coreimpl.h \
    generalsettings.h \
    filemanager.h \
    uniqueidmanager.h \
    eventfilteringmainwindow.h \
    findplaceholder.h \
    icontext.h \
    icore.h \
    ifile.h \
    icorelistener.h \
    mainwindow.h \
    plugindialog.h \
    qt_core_constants.h \
    qt_core_global.h \
    qt_coreplugin.h \
    settingsdatabase.h \
    versiondialog.h \

SOURCES = \
    actionmanager/actioncontainer.cpp \
    actionmanager/actionmanager.cpp \
    actionmanager/command.cpp \
    actionmanager/commandmappings.cpp \
    actionmanager/commandsfile.cpp \
    \
    dialogs/ioptionspage.cpp \
    dialogs/settingsdialog.cpp \
    dialogs/shortcutsettings.cpp \
    \
    interfaces/imainwindowextension.cpp \
    \
    coreimpl.cpp \
    eventfilteringmainwindow.cpp \
    filemanager.cpp \
    findplaceholder.cpp \
    generalsettings.cpp \
    icore.cpp \
    mainwindow.cpp \
    plugindialog.cpp \
    qt_coreplugin.cpp \
    settingsdatabase.cpp \
    uniqueidmanager.cpp \
    versiondialog.cpp \

FORMS = \
    actionmanager/commandmappings.ui \
    \
    generalsettings.ui \

RESOURCES = \
    qt_core.qrc \

OTHER_FILES *= \
    pro_version.h.in \
    qt_core.prf \
    qt_core_dependencies.prf \
    qt_core.pluginspec.in \

unix {
    images.files = images/project_logo_*.png
    images.path = /share/pixmaps
    INSTALLS += images
}

win32-msvc* {
    QMAKE_CXXFLAGS *= \
        -wd4251 \
        -wd4290 \
        -wd4250 \
}