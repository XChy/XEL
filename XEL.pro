#-------------------------------------------------
#
# Project created by QtCreator 2018-08-08T17:20:19
#
#-------------------------------------------------

QT       -= gui

TARGET = XEL
TEMPLATE = lib

DEFINES += XEL_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    EvaluateNode.cpp \
    NodeCreator.cpp \
    Parser.cpp \
    Preprocessor.cpp \
    Token.cpp \
    Tokenizer.cpp \
    Variant.cpp \
    XELEngine.cpp \
    XELError.cpp \
    XELContext.cpp

HEADERS += \
    EvaluateNode.h \
    NodeCreator.h \
    Parser.h \
    Preprocessor.h \
    Token.h \
    Tokenizer.h \
    Variant.h \
    XELEngine.h \
    xel_global.h \
    XELError.h \
    XELContext.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
