TEMPLATE = subdirs

CONFIG *= \
    ordered \

SUBDIRS = \
    qt_core \
    mi_core \
    mi_gui \
    ac_core \
    ac_csound \
    ac_gui \
    ac_midi \
#    ac_audioengine \

HEADERS *= \
    interfaces.h \

INTERFACE_FILES *= \
    aggregate \
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
    model \
    modelitem \
    modelitemwatcher \
    modellistwatcher \
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
