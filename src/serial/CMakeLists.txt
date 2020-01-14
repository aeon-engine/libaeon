# Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

set(LIB_AEON_SERIAL_PUBLIC_SOURCE
    include/aeon/serial/serial_port.h
)

source_group(public FILES ${LIB_AEON_SERIAL_PUBLIC_SOURCE})

set(LIB_AEON_SERIAL_PRIVATE_SOURCE
    src/serial_port.cpp
)

source_group(private FILES ${LIB_AEON_SERIAL_PRIVATE_SOURCE})

add_library(aeon_serial STATIC
    ${LIB_AEON_SERIAL_PUBLIC_SOURCE}
    ${LIB_AEON_SERIAL_PRIVATE_SOURCE}
)

set_target_properties(aeon_serial PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_serial
    PUBLIC
        include
)

target_link_libraries(aeon_serial
    aeon_common
)

install(
    DIRECTORY include/aeon
    DESTINATION include
)

install(
    TARGETS aeon_serial
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
