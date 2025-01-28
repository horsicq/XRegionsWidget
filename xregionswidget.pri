INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += \
    $$PWD/xregionswidget.h

SOURCES += \
    $$PWD/xregionswidget.cpp

FORMS += \
    $$PWD/xregionswidget.ui

!contains(XCONFIG, xshortcuts) {
    XCONFIG += xshortcuts
    include($$PWD/../XShortcuts/xshortcuts.pri)
}

DISTFILES += \
    $$PWD/xregionswidget.cmake
