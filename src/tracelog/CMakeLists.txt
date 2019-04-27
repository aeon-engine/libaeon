# Copyright (c) 2012-2019 Robin Degen

set(LIB_AEON_TRACELOG_PUBLIC_SOURCE
    include/aeon/tracelog/tracelog.h
)

source_group(public FILES ${LIB_AEON_TRACELOG_PUBLIC_SOURCE})

set(LIB_AEON_TRACELOG_PRIVATE_SOURCE
    src/config.h
    src/data.h
    src/tracelog.cpp
    src/context.cpp
    src/context.h
)

source_group(private FILES ${LIB_AEON_TRACELOG_PRIVATE_SOURCE})

add_library(aeon_tracelog STATIC
    ${LIB_AEON_TRACELOG_PUBLIC_SOURCE}
    ${LIB_AEON_TRACELOG_PRIVATE_SOURCE}
)

set_target_properties(aeon_tracelog PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_tracelog
    PUBLIC
        include
    PRIVATE
        src
)

target_link_libraries(aeon_tracelog
    aeon_common
    aeon_streams
)

install(
    DIRECTORY include/aeon
    DESTINATION include
)

install(
    TARGETS aeon_tracelog
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

add_subdirectory(tests)
