# Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

set(SOURCES
    private/container.cpp
    public/aeon/file_container/container.h
    public/aeon/file_container/exception.h
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_library(aeon_file_container STATIC
    ${SOURCES}
)

set_target_properties(aeon_file_container PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_file_container
    PUBLIC
        public
)

target_link_libraries(aeon_file_container
    aeon_common
    aeon_streams
    aeon_ptree
)

install(
    DIRECTORY public/aeon
    DESTINATION include
)

if (AEON_ENABLE_TESTING)
    add_subdirectory(tests)
endif ()
