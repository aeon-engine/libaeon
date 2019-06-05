# Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

handle_local_dependencies_file()

set(LIB_AEON_FONTS_PUBLIC_SOURCE
    include/aeon/fonts/config.h
    include/aeon/fonts/exceptions.h
    include/aeon/fonts/face.h
    include/aeon/fonts/face_wrapper.h
    include/aeon/fonts/font_manager.h
    include/aeon/fonts/glyph.h
)

source_group(public FILES ${LIB_AEON_FONTS_PUBLIC_SOURCE})

set(LIB_AEON_FONTS_PRIVATE_SOURCE
    src/face.cpp
    src/face_wrapper.cpp
    src/font_manager.cpp
)

source_group(private FILES ${LIB_AEON_FONTS_PRIVATE_SOURCE})

add_library(aeon_fonts STATIC
    ${LIB_AEON_FONTS_PUBLIC_SOURCE}
    ${LIB_AEON_FONTS_PRIVATE_SOURCE}
)

set_target_properties(aeon_fonts PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_fonts
    PUBLIC
        include
)

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

if (AEON_ENABLE_TESTING)
    add_subdirectory(tests)
endif ()
