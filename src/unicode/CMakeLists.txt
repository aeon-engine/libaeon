# Copyright (c) 2012-2019 Robin Degen

set(LIB_AEON_UNICODE_SOURCE
    src/encoding.cpp
    src/ucnv_wrapper.h
    include/aeon/unicode/encoding.h
    include/aeon/unicode/exception.h
    include/aeon/unicode/utf_string_view.h
    include/aeon/unicode/base_utf_iterator.h
    src/utf8_iterator.cpp
    include/aeon/unicode/utf8_iterator.h
    src/utf16_iterator.cpp
    include/aeon/unicode/utf16_iterator.h
    src/ctypes.cpp
    include/aeon/unicode/ctypes.h
)

source_group(unicode FILES ${LIB_AEON_UNICODE_SOURCE})

add_library(aeon_unicode STATIC
    ${LIB_AEON_UNICODE_SOURCE}
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

add_subdirectory(tests)
