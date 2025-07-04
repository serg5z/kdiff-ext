cmake_minimum_required(VERSION 3.16)

project(kdiff-ext-config)

find_package(ECM REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs5)
include(KDECMakeSettings)
include(KDEFrameworkCompilerSettings)

find_package(Qt5 REQUIRED COMPONENTS Widgets)
find_package(KF5CoreAddons REQUIRED)
find_package(KF5Config REQUIRED)
find_package(KF5I18n REQUIRED)
find_package(KF5KIO REQUIRED)
find_package(KF5WidgetsAddons REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

qt5_add_resources(GENERATED_RESOURCE_SOURCES resources.qrc)

add_executable(kdiff-ext-config
    src/main.cpp
    src/diff-ext-config.h
    src/diff-ext-config.cpp
    src/aboutdialog.h
    src/aboutdialog.cpp
    src/diff-ext-config.ui
    ${GENERATED_RESOURCE_SOURCES}
)

# target_include_directories(kdiff-ext-config PRIVATE /usr/include/KF5/KConfigCore)
target_include_directories(kdiff-ext-config
    PRIVATE ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(kdiff-ext-config
    config-lib
    Qt5::Widgets
    KF5::CoreAddons
    KF5ConfigCore
    KF5::I18n
)

install(TARGETS kdiff-ext-config DESTINATION ${KDE_INSTALL_BINDIR})
