# Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

handle_local_dependencies_file()

set(SOURCES
    private/ctypes.cpp
    private/encoding.cpp
    private/stringutils.cpp
    private/ucnv_wrapper.h
    private/utf16_iterator.cpp
    private/utf8_iterator.cpp
    public/aeon/unicode/base_utf_iterator.h
    public/aeon/unicode/ctypes.h
    public/aeon/unicode/encoding.h
    public/aeon/unicode/exception.h
    public/aeon/unicode/stringutils.h
    public/aeon/unicode/utf16_iterator.h
    public/aeon/unicode/utf8_iterator.h
    public/aeon/unicode/utf_string_view.h
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_library(aeon_unicode STATIC
    ${SOURCES}
)

set_target_properties(aeon_unicode PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_unicode
    PUBLIC
        public
)

target_link_libraries(aeon_unicode
    aeon_common
    ICU::uc
)

install(
    DIRECTORY public/aeon
    DESTINATION include
)

install(
    TARGETS aeon_unicode
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

if (AEON_ENABLE_TESTING)
    add_subdirectory(tests)
endif ()
