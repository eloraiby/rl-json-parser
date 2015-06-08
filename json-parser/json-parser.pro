#-------------------------------------------------
#
# Project created by QtCreator 2015-06-07T16:28:28
#
#-------------------------------------------------

QT       -= core gui

TARGET = json-parser
TEMPLATE = lib

DEFINES += JSONPARSER_LIBRARY

lexer.target = lexer.c
lexer.commands = ragel -C -o $$PWD/lexer.c $$PWD/lexer.rl
lexer.depends =

parser.target = parser.c
parser.commands = lemon -T$$PWD/lempar.c_template $$PWD/parser.y

QMAKE_EXTRA_TARGETS	+= lexer parser

PRE_TARGETDEPS	+= parser.c lexer.c

SOURCES += \
    lexer.c \
    parser.c \
    json-primitives.c

HEADERS += \
	json-parser.h \
    parser.h \
    private/private.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
	lexer.rl \
	lempar.c_template \
    parser.y
