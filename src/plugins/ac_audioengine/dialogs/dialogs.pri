
UI_SOURCES = \
    ac_audioenginedialog \

for(pair, UI_SOURCES) {
    HEADERS *= dialogs/$${pair}.h
    SOURCES *= dialogs/$${pair}.cpp
    FORMS *= dialogs/$${pair}.ui
}
