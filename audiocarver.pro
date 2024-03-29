# check qt version
contains(QT_VERSION, ^5\\.[0-3]\\..*) {
    error("Cannot build AudioCarver with Qt version $${QT_VERSION}." \
          "Use at least Qt 5.4.")
}

# check mkspec
win32*: !win32-g++* {
    error("Cannot build AudioCarver on Windows without g++." \
          "Use MinGW.")
}

TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS = src

OTHER_FILES *= \
    testing/*.ac \
    testing/*.csd \
    \
    .gitignore \
    bugs.txt \
    project.prf \
