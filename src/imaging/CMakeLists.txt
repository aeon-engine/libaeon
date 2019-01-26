# Copyright (c) 2012-2019 Robin Degen

set(LIB_AEON_IMAGING_SOURCE
    include/aeon/imaging/dimension.h
    include/aeon/imaging/dynamic_image.h
    include/aeon/imaging/dynamic_image_descriptor.h
    include/aeon/imaging/exceptions.h
    include/aeon/imaging/image.h
    include/aeon/imaging/image_descriptor.h
    include/aeon/imaging/image_view.h
    include/aeon/imaging/image_view_base.h
    include/aeon/imaging/pixel_encoding.h
    include/aeon/imaging/pixel_encoding_traits.h
    include/aeon/imaging/pixel_math.h
)

source_group(imaging FILES ${LIB_AEON_IMAGING_SOURCE})

set(LIB_AEON_IMAGING_IMPL_SOURCE
    include/aeon/imaging/impl/dynamic_image_descriptor_impl.h
    include/aeon/imaging/impl/dynamic_image_impl.h
    include/aeon/imaging/impl/image_descriptor_impl.h
    include/aeon/imaging/impl/image_impl.h
    include/aeon/imaging/impl/image_view_base_impl.h
    include/aeon/imaging/impl/image_view_impl.h
    include/aeon/imaging/impl/pixel_encoding_impl.h
)

source_group(imaging\\impl FILES ${LIB_AEON_IMAGING_IMPL_SOURCE})

set(LIB_AEON_IMAGING_FILE_SOURCE
    include/aeon/imaging/file/bmp_file.h
    src/file/bmp_file.cpp
    include/aeon/imaging/file/png_file.h
    src/file/png_file.cpp
    include/aeon/imaging/file/jpg_file.h
    src/file/jpg_file.cpp
    include/aeon/imaging/file/tjhandle_wrapper.h
    include/aeon/imaging/file/png_structs.h
    include/aeon/imaging/file/png_read_structs.h
    include/aeon/imaging/file/png_write_structs.h
)

source_group(imaging\\file FILES ${LIB_AEON_IMAGING_FILE_SOURCE})

set(LIB_AEON_IMAGING_GENERATORS_SOURCE
    include/aeon/imaging/generators/simplex_noise.h
)

source_group(imaging\\generators FILES ${LIB_AEON_IMAGING_GENERATORS_SOURCE})

set(LIB_AEON_IMAGING_CONVERTERS_SOURCE
    include/aeon/imaging/converters/convert_pixel.h
    include/aeon/imaging/converters/convert_encoding.h
    src/converters/convert_encoding.cpp
    include/aeon/imaging/converters/stride.h
)

source_group(imaging\\converters FILES ${LIB_AEON_IMAGING_CONVERTERS_SOURCE})

set(LIB_AEON_IMAGING_FILTERS_SOURCE
    include/aeon/imaging/filters/blit.h
    include/aeon/imaging/filters/fill.h
    include/aeon/imaging/filters/invert.h
    include/aeon/imaging/filters/resize.h
)

source_group(imaging\\filters FILES ${LIB_AEON_IMAGING_FILTERS_SOURCE})

add_library(aeon_imaging STATIC
    ${LIB_AEON_IMAGING_SOURCE}
    ${LIB_AEON_IMAGING_IMPL_SOURCE}
    ${LIB_AEON_IMAGING_FILE_SOURCE}
    ${LIB_AEON_IMAGING_GENERATORS_SOURCE}
    ${LIB_AEON_IMAGING_CONVERTERS_SOURCE}
    ${LIB_AEON_IMAGING_FILTERS_SOURCE}
)

set_target_properties(aeon_imaging PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_imaging PUBLIC include)
target_link_libraries(aeon_imaging
    aeon_utility
    aeon_common
    aeon_math
    PNG::PNG
    JPEG::JPEGTURBO
)

install(
    DIRECTORY include/aeon
    DESTINATION include
)

install(
    TARGETS aeon_imaging
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

add_subdirectory(tests)
