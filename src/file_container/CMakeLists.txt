# Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

set(LIB_AEON_FILE_CONTAINER_PUBLIC_SOURCE
    include/aeon/file_container/container.h
    include/aeon/file_container/exception.h
)

source_group(public FILES ${LIB_AEON_FILE_CONTAINER_PUBLIC_SOURCE})

set(LIB_AEON_FILE_CONTAINER_PRIVATE_SOURCE
    src/container.cpp
)

source_group(private FILES ${LIB_AEON_FILE_CONTAINER_PRIVATE_SOURCE})

add_library(aeon_file_container STATIC
    ${LIB_AEON_FILE_CONTAINER_PUBLIC_SOURCE}
    ${LIB_AEON_FILE_CONTAINER_PRIVATE_SOURCE}
)

set_target_properties(aeon_file_container PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_file_container
    PUBLIC
        include
)

target_link_libraries(aeon_file_container
    aeon_common
    aeon_streams
    aeon_ptree
)

install(
    DIRECTORY include
    DESTINATION include
)

add_subdirectory(tests)
