# Copyright (c) 2012-2019 Robin Degen

set(LIB_AEON_FONTS_SOURCE
    include/aeon/fonts/config.h
    include/aeon/fonts/exceptions.h
    include/aeon/fonts/face.h
    src/face.cpp
    include/aeon/fonts/face_wrapper.h
    src/face_wrapper.cpp
    include/aeon/fonts/font_manager.h
    src/font_manager.cpp
    include/aeon/fonts/glyph.h
)

source_group(fonts FILES ${LIB_AEON_FONTS_SOURCE})

add_library(aeon_fonts STATIC
    ${LIB_AEON_FONTS_SOURCE}
)

set_target_properties(aeon_fonts PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_fonts PUBLIC include)
target_link_libraries(aeon_fonts
    aeon_common
    aeon_imaging
    aeon_streams
    Freetype::Freetype
)

install(
    DIRECTORY include/aeon
    DESTINATION include
)

install(
    TARGETS aeon_fonts
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

add_subdirectory(tests)
