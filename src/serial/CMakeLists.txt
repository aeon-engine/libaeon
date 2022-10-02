# Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

set(SOURCES
    private/serial_port.cpp
    public/aeon/serial/serial_port.h
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_library(aeon_serial STATIC
    ${SOURCES}
)

set_target_properties(aeon_serial PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_serial
    PUBLIC
        public
)

target_link_libraries(aeon_serial
    aeon_common
)

install(
    DIRECTORY public/aeon
    DESTINATION include
)

install(
    TARGETS aeon_serial
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
