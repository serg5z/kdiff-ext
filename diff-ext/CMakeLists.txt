cmake_minimum_required(VERSION 3.16)
project(kdiff-ext)

find_package(ECM REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})
include(KDEInstallDirs5)
include(KDECMakeSettings)
include(KDEFrameworkCompilerSettings)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(KF5 REQUIRED COMPONENTS I18n CoreAddons KIO WidgetsAddons)

kcoreaddons_add_plugin(kdiff-ext
    SOURCES src/diff-ext.cpp
    INSTALL_NAMESPACE "kf5/kfileitemaction")

target_link_libraries(kdiff-ext KF5::I18n KF5::CoreAddons KF5::KIOCore KF5::KIOWidgets Qt5::Core Qt5::Widgets)

