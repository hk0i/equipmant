######################################################################
# Automatically generated by qmake (2.01a) Wed May 9 19:10:55 2012
######################################################################

TEMPLATE = app
TARGET = equip
DEPENDPATH += . model model/tests
INCLUDEPATH += . model model/tests

# Input
HEADERS += equipmant.h \
           imp_about.h \
           imp_equipmant.h \
           imp_equiptab.h \
           model/Equip.h \
           model/EquipIoFactory.h \
           model/EquipReader.h \
           model/EquipReaderTxt.h \
           model/EquipWriter.h \
           model/EquipWriterTxt.h \
           ui/GScriptHighlighter.h
FORMS += about.ui equipmant.ui equipTab.ui
SOURCES += imp_about.cpp \
           imp_equipmant.cpp \
           imp_equiptab.cpp \
           main.cpp \
           model/Equip.cpp \
           model/EquipIoFactory.cpp \
           model/EquipReader.cpp \
           model/EquipReaderTxt.cpp \
           model/EquipWriter.cpp \
           model/EquipWriterTxt.cpp \
           ui/GScriptHighlighter.cpp
RESOURCES += equip.qrc
RC_FILE = equip.rc

OTHER_FILES += \
    items.txt
