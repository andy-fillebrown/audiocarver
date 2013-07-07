TEMPLATE = subdirs

CONFIG *= \
    ordered \

SUBDIRS = \
    qt_core \
    mi_core \
    mi_gui \
    mi_audioengine \
    mi_synthesizer \
    ac_core \
    ac_gui \
    ac_midi \
    ac_audioengine \
    ac_csound_audioengine \
    ac_csound_synthesizer \

HEADERS *= \
    interfaces.h \

INTERFACE_FILES *= \
    aggregate \
    audioengine \
    audioenginesettingswatcher \
    component \
    database \
    databaseobjectfactory \
    databasewatcher \
    editor \
    filer \
    filerfactory \
    graphicsdelegate \
    graphicseditor \
    graphicsgrip \
    graphicsgriplist \
    graphicsitem \
    mainwindow \
    mainwindowextension \
    model \
    modelitem \
    modelitemwatcher \
    modellistwatcher \
    modelwatcher \
    playcursor \
    reader \
    selectionset \
    selectionsetwatcher \
    session \
    synthesizer \
    undomanager \
    unknown \
    writer \

for(file, INTERFACE_FILES) {
    HEADERS *= _.interfaces/i$${file}.h
}

OTHER_FILES *= \
    Doxyfile \
