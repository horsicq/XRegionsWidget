INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += \
    $$PWD/xregionitem.h \
    $$PWD/xregionsmodel.h \
    $$PWD/xregionswidget.h

SOURCES += \
    $$PWD/xregionitem.cpp \
    $$PWD/xregionsmodel.cpp \
    $$PWD/xregionswidget.cpp

FORMS += \
    $$PWD/xregionswidget.ui

!contains(XCONFIG, xshortcuts) {
    XCONFIG += xshortcuts
    include($$PWD/../XShortcuts/xshortcuts.pri)
}

DISTFILES += \
    $$PWD/xregionswidget.cmake
