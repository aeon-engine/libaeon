# Copyright (c) 2012-2019 Robin Degen

set(LIB_AEON_RDP_PUBLIC_SOURCE
    include/aeon/rdp/parser.h
    include/aeon/rdp/cursor.h
    include/aeon/rdp/matchers.h
    include/aeon/rdp/parse_result.h
    include/aeon/rdp/scoped_state.h
)

source_group(public FILES ${LIB_AEON_RDP_PUBLIC_SOURCE})

set(LIB_AEON_RDP_PUBLIC_IMPL_SOURCE
    include/aeon/rdp/impl/parser_impl.h
    include/aeon/rdp/impl/parse_result_impl.h
)

source_group(public\\impl FILES ${LIB_AEON_RDP_PUBLIC_IMPL_SOURCE})

set(LIB_AEON_RDP_PRIVATE_SOURCE
    src/parser.cpp
    src/cursor.cpp
    src/matchers.cpp
)

source_group(private FILES ${LIB_AEON_RDP_PRIVATE_SOURCE})

add_library(aeon_rdp STATIC
    ${LIB_AEON_RDP_PUBLIC_SOURCE}
    ${LIB_AEON_RDP_PUBLIC_IMPL_SOURCE}
    ${LIB_AEON_RDP_PRIVATE_SOURCE}
)

set_target_properties(aeon_rdp PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_rdp
    PUBLIC
        include
    PRIVATE
        ${CMAKE_BINARY_DIR}
)

target_link_libraries(aeon_rdp
    PUBLIC
        aeon_common
)

install(
    DIRECTORY include/aeon
    DESTINATION include
)

install(
    TARGETS aeon_rdp
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

if (AEON_ENABLE_TESTING)
    add_subdirectory(tests)
endif ()
