# Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

handle_local_dependencies_file()

set(SOURCES
    private/face.cpp
    private/face_wrapper.cpp
    private/font_manager.cpp
    public/aeon/fonts/config.h
    public/aeon/fonts/exceptions.h
    public/aeon/fonts/face.h
    public/aeon/fonts/face_wrapper.h
    public/aeon/fonts/font_manager.h
    public/aeon/fonts/glyph.h
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_library(aeon_fonts STATIC
    ${SOURCES}
)

set_target_properties(aeon_fonts PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_fonts
    PUBLIC
        public
)

target_link_libraries(aeon_fonts
    aeon_common
    aeon_imaging
    aeon_streams
    Freetype::Freetype
)

install(
    DIRECTORY public/aeon
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
