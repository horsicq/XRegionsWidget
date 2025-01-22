INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

!contains(XCONFIG, xshortcuts) {
    XCONFIG += xshortcuts
    include($$PWD/../XShortcuts/xshortcuts.pri)
}

DISTFILES += \
    $$PWD/xregionswidget.cmake
