project(kdiff-ext)

cmake_minimum_required(VERSION 3.16)

set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-${VERSION}")

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

