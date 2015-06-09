#-------------------------------------------------
#
# Project created by QtCreator 2015-06-08T20:32:52
#
#-------------------------------------------------

QT       -= core gui

TARGET = test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    main.c

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../json-parser/release/ -ljson-parser
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../json-parser/debug/ -ljson-parser
else:unix: LIBS += -L$$OUT_PWD/../json-parser/ -ljson-parser

INCLUDEPATH += $$PWD/../json-parser
DEPENDPATH += $$PWD/../json-parser
