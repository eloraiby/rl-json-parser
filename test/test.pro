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

QMAKE_CFLAGS	+= -std=c99

SOURCES += \
    main.c

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../json-parser/release/ -ljson-parser
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../json-parser/debug/ -ljson-parser
else:unix: LIBS += -L$$OUT_PWD/../json-parser/ -ljson-parser

INCLUDEPATH += $$PWD/../json-parser
DEPENDPATH += $$PWD/../json-parser

OTHER_FILES += \
    jsonchecker/fail34.json \
    jsonchecker/fail01_EXCLUDE.json \
    jsonchecker/fail02.json \
    jsonchecker/fail03.json \
    jsonchecker/fail04.json \
    jsonchecker/fail05.json \
    jsonchecker/fail06.json \
    jsonchecker/fail07.json \
    jsonchecker/fail08.json \
    jsonchecker/fail09.json \
    jsonchecker/fail10.json \
    jsonchecker/fail11.json \
    jsonchecker/fail12.json \
    jsonchecker/fail13.json \
    jsonchecker/fail14.json \
    jsonchecker/fail15.json \
    jsonchecker/fail16.json \
    jsonchecker/fail17.json \
    jsonchecker/fail18_EXCLUDE.json \
    jsonchecker/fail19.json \
    jsonchecker/fail20.json \
    jsonchecker/fail21.json \
    jsonchecker/fail22.json \
    jsonchecker/fail23.json \
    jsonchecker/fail24.json \
    jsonchecker/fail25.json \
    jsonchecker/fail26.json \
    jsonchecker/fail27.json \
    jsonchecker/fail28.json \
    jsonchecker/fail29.json \
    jsonchecker/fail30.json \
    jsonchecker/fail31.json \
    jsonchecker/fail32.json \
    jsonchecker/fail33.json \
    jsonchecker/pass01.json \
    jsonchecker/pass02.json \
    jsonchecker/pass03.json \
    jsonchecker/readme.txt
