include_directories(${CMAKE_CURRENT_LIST_DIR})

if (NOT DEFINED XSHORTCUTS_SOURCES)
    include(${CMAKE_CURRENT_LIST_DIR}/../XShortcuts/xshortcuts.cmake)
    set(XREGIONSWIDGET_SOURCES ${XREGIONSWIDGET_SOURCES} ${XSHORTCUTS_SOURCES})
endif()

set(XREGIONSWIDGET_SOURCES
    ${XREGIONSWIDGET_SOURCES}
    ${CMAKE_CURRENT_LIST_DIR}/xregionitem.cpp
    ${CMAKE_CURRENT_LIST_DIR}/xregionitem.h
    ${CMAKE_CURRENT_LIST_DIR}/xregionsmodel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/xregionsmodel.h
    ${CMAKE_CURRENT_LIST_DIR}/xregionswidget.cpp
    ${CMAKE_CURRENT_LIST_DIR}/xregionswidget.h
    ${CMAKE_CURRENT_LIST_DIR}/xregionswidget.ui
)
