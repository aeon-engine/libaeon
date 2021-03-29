# Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

handle_local_dependencies_file()

set(SOURCES
    private/converters/convert_encoding.cpp
    private/file/bmp_file.cpp
    private/file/jpg_file.cpp
    private/file/png_file.cpp
    public/aeon/imaging/converters/convert_encoding.h
    public/aeon/imaging/converters/convert_pixel.h
    public/aeon/imaging/converters/stride.h
    public/aeon/imaging/exceptions.h
    public/aeon/imaging/file/bmp_file.h
    public/aeon/imaging/file/jpg_file.h
    public/aeon/imaging/file/png_file.h
    public/aeon/imaging/file/png_read_structs.h
    public/aeon/imaging/file/png_structs.h
    public/aeon/imaging/file/png_write_structs.h
    public/aeon/imaging/file/tjhandle_wrapper.h
    public/aeon/imaging/filters/resize.h
    public/aeon/imaging/iimage.h
    public/aeon/imaging/image.h
    public/aeon/imaging/image_view.h
    public/aeon/imaging/impl/image_impl.h
    public/aeon/imaging/impl/image_view_impl.h
    public/aeon/imaging/impl/pixel_encoding_impl.h
    public/aeon/imaging/pixel_encoding.h
    public/aeon/imaging/pixel_encoding_traits.h
    public/aeon/imaging/pixel_math.h
    public/aeon/imaging/utils/atlas.h
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_library(aeon_imaging STATIC
    ${SOURCES}
)

set_target_properties(aeon_imaging PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_imaging
    PUBLIC
        public
)

target_link_libraries(aeon_imaging
    aeon_common
    aeon_math
    aeon_streams
    PNG::PNG
    JPEG::JPEGTURBO
)

install(
    DIRECTORY public/aeon
    DESTINATION include
)

install(
    TARGETS aeon_imaging
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

if (AEON_ENABLE_TESTING)
    add_subdirectory(tests)
endif ()
