# Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

set(LIB_AEON_VARIANT_PUBLIC_SOURCE
    include/aeon/variant/converting_variant.h
)

source_group(public FILES ${LIB_AEON_VARIANT_PUBLIC_SOURCE})

set(LIB_AEON_VARIANT_PUBLIC_IMPL_SOURCE
    include/aeon/variant/impl/converting_variant_conversion.h
    include/aeon/variant/impl/converting_variant_enum_traits.h
    include/aeon/variant/impl/converting_variant_impl.h
)

source_group(public\\impl FILES ${LIB_AEON_VARIANT_PUBLIC_IMPL_SOURCE})

set(LIB_AEON_VARIANT_PRIVATE_SOURCE
    src/converting_variant.cpp
)

source_group(private FILES ${LIB_AEON_VARIANT_PRIVATE_SOURCE})

add_library(aeon_variant STATIC
    ${LIB_AEON_VARIANT_PUBLIC_SOURCE}
    ${LIB_AEON_VARIANT_PUBLIC_IMPL_SOURCE}
    ${LIB_AEON_VARIANT_PRIVATE_SOURCE}
)

set_target_properties(aeon_variant PROPERTIES
    FOLDER dep/libaeon
)

target_include_directories(aeon_variant
    PUBLIC
        include
)

target_link_libraries(aeon_variant
    aeon_common
    aeon_chrono
)

install(
    DIRECTORY include/aeon
    DESTINATION include
)

if (AEON_ENABLE_TESTING)
    add_subdirectory(tests)
endif ()
