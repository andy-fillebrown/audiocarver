
SOURCE_FILES = \
    controlcurve \
    curve \
    graphicsobject \
    graphicsparent \
#    gridline \
#    gridsettings \
#    note \
#    pitchcurve \
#    projectsettings \
#    score \
    scoreobject \
#    track \
#    viewsettings \

DIR = dataobjects
PREFIX = ac_

for(file, SOURCE_FILES) {
    name = $$PREFIX$$file
    header = $${name}.h
    source = $${name}.cpp
    exists($$header): HEADERS *= $$DIR/$$header
    exists($$source): SOURCES *= $$DIR/$$source
}
