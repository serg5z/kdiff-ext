cmake_minimum_required(VERSION 3.16)

project(kdiff-ext VERSION 1.0.0)

set(CPACK_PACKAGE_NAME "kdiff-ext")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_VENDOR "Sergey Zorin")
set(VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-${VERSION}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Dolphin plugin to compare files with external diff tool")
set(CPACK_PACKAGE_CONTACT "szorin@gmail.com")
set(CPACK_DEBIAN_FILE_NAME "DEB-DEFAULT")
set(CPACK_DEBIAN_PACKAGE_SUGGESTS "dolphin")
set(CPACK_DEBIAN_PACKAGE_SUGGESTS "meld")
set(CPACK_DEBIAN_PACKAGE_DEPENDS
    "libkf5coreaddons5, libkf5i18n5, libkf5kiocore5, libkf5kiowidgets5, libkf5widgetsaddons5, libqt5core5a, libqt5widgets5"
)
set(CPACK_STRIP_FILES TRUE)
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Sergey Zorin")
set(CPACK_GENERATOR "DEB")

add_subdirectory(diff-ext)
add_subdirectory(diff-ext-config)

########### install files ###############

install(FILES COPYING AUTHORS DESTINATION share/doc/kdiff-ext)

set(CPACK_SOURCE_GENERATOR "TGZ")
set(CPACK_SOURCE_IGNORE_FILES
    "/build/"
    "/\\.git/"
    "/\\.github/"
    "~$"
    ".swp$"
    "\\.user$"
    "\\.DS_Store"
)

include(CPack)

