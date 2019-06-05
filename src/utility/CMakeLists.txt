# Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

set(LIB_AEON_UTILITY_PUBLIC_SOURCE
    include/aeon/utility/configfile.h
    include/aeon/utility/uuid_stream.h
)

source_group(public FILES ${LIB_AEON_UTILITY_PUBLIC_SOURCE})

set(LIB_AEON_UTILITY_PRIVATE_SOURCE
    src/configfile.cpp
)

source_group(private FILES ${LIB_AEON_UTILITY_PRIVATE_SOURCE})

add_library(aeon_utility STATIC
    ${LIB_AEON_UTILITY_PUBLIC_SOURCE}
    ${LIB_AEON_UTILITY_PRIVATE_SOURCE}
)

set_target_properties(aeon_utility PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_utility
    PUBLIC
        include
)

target_link_libraries(aeon_utility
    aeon_common
    aeon_streams
)

install(
    DIRECTORY include/aeon
    DESTINATION include
)

install(
    TARGETS aeon_utility
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

if (AEON_ENABLE_TESTING)
    add_subdirectory(tests)
endif ()
