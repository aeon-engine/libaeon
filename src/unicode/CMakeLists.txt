# Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

handle_local_dependencies_file()

set(LIB_AEON_UNICODE_PUBLIC_SOURCE
    include/aeon/unicode/encoding.h
    include/aeon/unicode/exception.h
    include/aeon/unicode/utf_string_view.h
    include/aeon/unicode/base_utf_iterator.h
    include/aeon/unicode/utf8_iterator.h
    include/aeon/unicode/utf16_iterator.h
    include/aeon/unicode/stringutils.h
    include/aeon/unicode/ctypes.h
)

source_group(public FILES ${LIB_AEON_UNICODE_PUBLIC_SOURCE})

set(LIB_AEON_UNICODE_PRIVATE_SOURCE
    src/encoding.cpp
    src/ucnv_wrapper.h
    src/utf8_iterator.cpp
    src/utf16_iterator.cpp
    src/stringutils.cpp
    src/ctypes.cpp
)

source_group(private FILES ${LIB_AEON_UNICODE_PRIVATE_SOURCE})

add_library(aeon_unicode STATIC
    ${LIB_AEON_UNICODE_PUBLIC_SOURCE}
    ${LIB_AEON_UNICODE_PRIVATE_SOURCE}
)

set_target_properties(aeon_unicode PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_unicode
    PUBLIC
        include
)

target_link_libraries(aeon_unicode
    aeon_common
    ICU::uc
)

install(
    DIRECTORY include/aeon
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
