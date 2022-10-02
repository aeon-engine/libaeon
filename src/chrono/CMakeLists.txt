# Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

find_package(ICU CONFIG)

set(SOURCES
    private/calendar.cpp
    private/timezone.cpp
    private/timezone_impl.h
    public/aeon/chrono/calendar.h
    public/aeon/chrono/offset.h
    public/aeon/chrono/timezone.h
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_library(aeon_chrono STATIC
    ${SOURCES}
)

set_target_properties(aeon_chrono PROPERTIES
    FOLDER dep/libaeon
)

target_include_directories(aeon_chrono
    PUBLIC
        public
)

target_link_libraries(aeon_chrono
    aeon_common
    ICU::ICU
)

install(
    DIRECTORY public/aeon
    DESTINATION include
)

if (AEON_ENABLE_TESTING)
    add_subdirectory(tests)
endif ()
