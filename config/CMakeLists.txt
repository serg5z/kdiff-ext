find_package(KF5CoreAddons REQUIRED)
find_package(KF5Config REQUIRED)

add_library(config-lib STATIC
    src/config.cpp
)

target_include_directories(config-lib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(config-lib
    KF5::CoreAddons
    KF5::ConfigCore
)
