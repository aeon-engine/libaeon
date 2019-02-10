# Copyright (c) 2012-2019 Robin Degen

set(LIB_AEON_PTREE_SOURCE
    include/aeon/ptree/ptree.h
    include/aeon/ptree/exception.h
)

source_group(ptree FILES ${LIB_AEON_PTREE_SOURCE})

set(LIB_AEON_PTREE_SERIALIZATION_SOURCE
    include/aeon/ptree/serialization/exception.h
    include/aeon/ptree/serialization/serialization_json.h
    src/serialization_json.cpp
    include/aeon/ptree/serialization/serialization_abf.h
    src/serialization_abf.cpp
)

source_group(ptree\\serialization FILES ${LIB_AEON_PTREE_SERIALIZATION_SOURCE})

add_library(aeon_ptree
    STATIC
        ${LIB_AEON_PTREE_SOURCE}
        ${LIB_AEON_PTREE_SERIALIZATION_SOURCE}
)

set_target_properties(aeon_ptree PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_ptree
    PUBLIC
        include
)

target_link_libraries(aeon_ptree
    aeon_common
    aeon_utility
    aeon_unicode
    aeon_streams
)

install(
    DIRECTORY include
    DESTINATION include
)

add_subdirectory(tests)
