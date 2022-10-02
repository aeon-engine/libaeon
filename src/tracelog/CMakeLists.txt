# Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

set(SOURCES
    private/config.h
    private/context.cpp
    private/context.h
    private/data.h
    private/tracelog.cpp
    public/aeon/tracelog/tracelog.h
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_library(aeon_tracelog STATIC
    ${SOURCES}
)

set_target_properties(aeon_tracelog PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_tracelog
    PUBLIC
        public
    PRIVATE
        private
)

target_link_libraries(aeon_tracelog
    aeon_common
    aeon_streams
)

install(
    DIRECTORY public/aeon
    DESTINATION include
)

install(
    TARGETS aeon_tracelog
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

if (AEON_ENABLE_TESTING)
    add_subdirectory(tests)
endif ()
