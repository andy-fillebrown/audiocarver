TEMPLATE = lib
TARGET   = Core

QT += \
    sql \
    xml

include(../../projectplugin.pri)
include(../../libs/utils/utils.pri)
include(coreplugin_dependencies.pri)

win32-msvc*:QMAKE_CXXFLAGS += -wd4251 -wd4290 -wd4250

DEFINES += CORE_LIBRARY

INCLUDEPATH += \
    actionmanager \
    dialogs

DEPENDPATH += \
    actionmanager \
    dialogs

SOURCES += \
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
    coreimpl.cpp \
    coreplugin.cpp \
    eventfilteringmainwindow.cpp \
    filemanager.cpp \
    findplaceholder.cpp \
    generalsettings.cpp \
    icore.cpp \
    mainwindow.cpp \
    plugindialog.cpp \
    settingsdatabase.cpp \
    uniqueidmanager.cpp \
    versiondialog.cpp \

HEADERS += \
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
    core_global.h \
    coreconstants.h \
    coreimpl.h \
    coreplugin.h \
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
    settingsdatabase.h \
    versiondialog.h

FORMS += \
    actionmanager/commandmappings.ui \
    \
    generalsettings.ui

RESOURCES += \
    core.qrc \

unix {
    images.files = images/project_logo_*.png
    images.path = /share/pixmaps
    INSTALLS += images
}

QMAKE_SUBSTITUTES += pro_version.h.in
OTHER_FILES += $$QMAKE_SUBSTITUTES
