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
    generalsettings.cpp \
    filemanager.cpp \
    uniqueidmanager.cpp \
    versiondialog.cpp \
    actionmanager/actionmanager.cpp \
    actionmanager/command.cpp \
    actionmanager/actioncontainer.cpp \
    actionmanager/commandsfile.cpp \
    dialogs/settingsdialog.cpp \
    actionmanager/commandmappings.cpp \
    dialogs/shortcutsettings.cpp \
    coreplugin.cpp \
    coreimpl.cpp \
    plugindialog.cpp \
    findplaceholder.cpp \
    mimedatabase.cpp \
    icore.cpp \
    dialogs/ioptionspage.cpp \
    settingsdatabase.cpp \
    eventfilteringmainwindow.cpp \

HEADERS += \
    mainwindow.h \
    generalsettings.h \
    filemanager.h \
    uniqueidmanager.h \
    actionmanager/actioncontainer.h \
    actionmanager/actionmanager.h \
    actionmanager/command.h \
    actionmanager/actionmanager_p.h \
    actionmanager/command_p.h \
    actionmanager/actioncontainer_p.h \
    actionmanager/commandsfile.h \
    dialogs/settingsdialog.h \
    actionmanager/commandmappings.h \
    dialogs/shortcutsettings.h \
    dialogs/ioptionspage.h \
    icontext.h \
    icore.h \
    ifile.h \
    coreconstants.h \
    icorelistener.h \
    versiondialog.h \
    core_global.h \
    coreplugin.h \
    coreimpl.h \
    plugindialog.h \
    findplaceholder.h \
    mimedatabase.h \
    settingsdatabase.h \
    eventfilteringmainwindow.h \

FORMS += \
    actionmanager/commandmappings.ui \
    generalsettings.ui

RESOURCES += \
    core.qrc \

unix {
    images.files = images/qtcreator_logo_*.png
    images.path = /share/pixmaps
    INSTALLS += images
}
OTHER_FILES += \
    editormanager/BinFiles.mimetypes.xml \
    ide_version.h.in

QMAKE_SUBSTITUTES += ide_version.h.in
