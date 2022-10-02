# Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

set(LIB_AEON_HEADER_DATA_GENERATOR_PRIVATE_SOURCE
    src/main.cpp
    src/application.cpp
    src/application.h
)

source_group(private FILES ${LIB_AEON_HEADER_DATA_GENERATOR_PRIVATE_SOURCE})

add_executable(aeon_header_data_generator
    ${LIB_AEON_HEADER_DATA_GENERATOR_PRIVATE_SOURCE}
)

set_target_properties(aeon_header_data_generator PROPERTIES
    FOLDER dep/libaeon/tools
    LINKER_LANGUAGE CXX
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_include_directories(aeon_header_data_generator
    PRIVATE
        src
)

target_link_libraries(aeon_header_data_generator
    aeon_common
    aeon_streams
)

install(
    TARGETS aeon_header_data_generator
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
