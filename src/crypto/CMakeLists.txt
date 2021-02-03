# Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

set(LIB_AEON_CRYPTO_PUBLIC_SOURCE
    include/aeon/crypto/sha256.h
)

source_group(public FILES ${LIB_AEON_CRYPTO_PUBLIC_SOURCE})

set(LIB_AEON_CRYPTO_PUBLIC_STREAM_FILTERS_SOURCE
    include/aeon/crypto/stream_filters/sha256_filter.h
)

source_group(public\\stream_filters FILES ${LIB_AEON_CRYPTO_PUBLIC_STREAM_FILTERS_SOURCE})

set(LIB_AEON_CRYPTO_PRIVATE_SOURCE
    src/sha256.cpp
)

source_group(private FILES ${LIB_AEON_CRYPTO_PRIVATE_SOURCE})

add_library(aeon_crypto STATIC
    ${LIB_AEON_CRYPTO_PUBLIC_SOURCE}
    ${LIB_AEON_CRYPTO_PUBLIC_STREAM_FILTERS_SOURCE}
    ${LIB_AEON_CRYPTO_PRIVATE_SOURCE}
)

set_target_properties(aeon_crypto PROPERTIES
    FOLDER dep/libaeon
)

target_include_directories(aeon_crypto
    PUBLIC
        include
)

target_link_libraries(aeon_crypto
    aeon_common
    aeon_streams
)

install(
    DIRECTORY include/aeon
    DESTINATION include
)

if (AEON_ENABLE_TESTING)
    add_subdirectory(tests)
endif ()
