# Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

set(SOURCES
    private/converting_variant.cpp
    public/aeon/variant/converting_variant.h
    public/aeon/variant/impl/converting_variant_conversion.h
    public/aeon/variant/impl/converting_variant_enum_traits.h
    public/aeon/variant/impl/converting_variant_impl.h
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_library(aeon_variant STATIC
    ${SOURCES}
)

set_target_properties(aeon_variant PROPERTIES
    FOLDER dep/libaeon
)

target_include_directories(aeon_variant
    PUBLIC
        public
)

target_link_libraries(aeon_variant
    aeon_common
    aeon_chrono
)

install(
    DIRECTORY public/aeon
    DESTINATION include
)

if (AEON_ENABLE_TESTING)
    add_subdirectory(tests)
endif ()
