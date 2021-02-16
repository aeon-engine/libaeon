# Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

set(SOURCES
    private/cursor.cpp
    private/matchers.cpp
    private/parser.cpp
    public/aeon/rdp/cursor.h
    public/aeon/rdp/impl/parse_result_impl.h
    public/aeon/rdp/impl/parser_impl.h
    public/aeon/rdp/matchers.h
    public/aeon/rdp/parse_result.h
    public/aeon/rdp/parser.h
    public/aeon/rdp/scoped_state.h
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_library(aeon_rdp STATIC
    ${SOURCES}
)

set_target_properties(aeon_rdp PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_rdp
    PUBLIC
        public
)

target_link_libraries(aeon_rdp
    PUBLIC
        aeon_common
)

install(
    DIRECTORY public/aeon
    DESTINATION include
)

install(
    TARGETS aeon_rdp
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

if (AEON_ENABLE_TESTING)
    add_subdirectory(tests)
endif ()
