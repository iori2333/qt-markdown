cmake_minimum_required(VERSION 3.5)

project(qt-markdown VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets WebEngineWidgets WebChannel REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets WebEngineWidgets WebChannel REQUIRED)

set(PROJECT_SOURCES
        src/main.cpp
        src/mainwindow.cpp
        include/mainwindow.h
        forms/mainwindow.ui
        include/interface.h
        include/element.h
        include/utils.h src/utils.cpp
        include/parser.h src/parser.cpp
        include/translator.h src/translator.cpp
        src/parse_inline.cpp src/parse_line.cpp
        include/page.h src/page.cpp
        include/document.h src/document.cpp
        resources/markdown.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(qt-markdown
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(qt-markdown SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(qt-markdown
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_include_directories(qt-markdown PUBLIC include/)
target_include_directories(qt-markdown PUBLIC forms/)

target_link_libraries(qt-markdown PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(qt-markdown PRIVATE Qt${QT_VERSION_MAJOR}::WebEngineWidgets)

set_target_properties(qt-markdown PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(qt-markdown)
endif()
