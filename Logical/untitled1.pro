QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Board.cpp \
    ChessPieceOp.cpp \
    DifficultAI.cpp \
    EasyAI.cpp \
    Game.cpp \
    Piece.cpp \
    form.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    AI.h \
    Board.h \
    ChessPieceOp.h \
    DifficultAI.h \
    EasyAI.h \
    Game.h \
    Piece.h \
    form.h \
    mainwindow.h

FORMS += \
    form.ui \
    mainwindow.ui

TRANSLATIONS += \
    untitled1_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
QMAKE_CXXFLAGS_RELEASE += -O0

RESOURCES += \
    resource.qrc
