# Copyright (c) 2012-2019 Robin Degen

set(LIB_AEON_TRACELOG_SOURCE
    src/config.h
    src/data.h
    include/aeon/tracelog/tracelog.h
    src/tracelog.cpp
    src/context.cpp
    src/context.h
)

source_group(tracelog FILES ${LIB_AEON_TRACELOG_SOURCE})

add_library(aeon_tracelog STATIC ${LIB_AEON_TRACELOG_SOURCE})

set_target_properties(aeon_tracelog PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_tracelog
    PUBLIC include
    PRIVATE src
)

target_link_libraries(aeon_tracelog aeon_common aeon_streams)

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
