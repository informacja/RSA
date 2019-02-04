TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    rsa.c \
    file.c \
    colors.c \
    dialog.c

HEADERS += \
    header.h \
    getline.h
