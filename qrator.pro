QT += core gui widgets

TARGET = QRator
TEMPLATE = app

FORMS += \
    src/ui/mainwindow.ui

HEADERS += \
    src/ui/mainwindow.h \
    src/ui/qrdisplay.h \
    src/qr/BitBuffer.hpp \
    src/qr/QrCode.hpp \
    src/qr/QrSegment.hpp

SOURCES += \
    src/main.cpp \
    src/ui/mainwindow.cpp \
    src/ui/qrdisplay.cpp \
    src/qr/BitBuffer.cpp \
    src/qr/QrCode.cpp \
    src/qr/QrSegment.cpp

