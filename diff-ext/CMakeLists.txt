cmake_minimum_required(VERSION 3.16)
project(kdiff-ext)

find_package(ECM REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs5)
include(KDECMakeSettings)
include(KDEFrameworkCompilerSettings)
include(ECMQtDeclareLoggingCategory)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(KF5 REQUIRED COMPONENTS I18n CoreAddons KIO WidgetsAddons)

set(KDE_INSTALL_QTPLUGINDIR lib/aarch64-linux-gnu/qt5/plugins)
message(STATUS "KDE_INSTALL_QTPLUGINDIR: ${KDE_INSTALL_QTPLUGINDIR}")

ecm_qt_declare_logging_category(
    kdiff-ext
    HEADER logging.h
    IDENTIFIER DIFFEXT
    CATEGORY_NAME org.kde.diff-ext
    DEFAULT_SEVERITY Info
)

kcoreaddons_add_plugin(kdiff-ext
    INSTALL_NAMESPACE "kf5/kfileitemaction"
    SOURCES 
        src/diff-ext.h
        src/diff-ext.cpp 
        src/logging.h
        src/logging.cpp 
)

target_link_libraries(kdiff-ext KF5::I18n KF5::CoreAddons KF5::KIOCore KF5::KIOWidgets Qt5::Core Qt5::Widgets)
