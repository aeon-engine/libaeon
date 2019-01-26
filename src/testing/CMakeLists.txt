# Copyright (c) 2012-2019 Robin Degen

set(LIB_AEON_TESTING_SOURCE
    include/aeon/testing/temporary_file_fixture.h
    src/temporary_file_fixture.cpp
)

source_group(testing FILES ${LIB_AEON_TESTING_SOURCE})

add_library(aeon_testing STATIC ${LIB_AEON_TESTING_SOURCE})

set_target_properties(aeon_testing PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_testing PUBLIC include)
target_link_libraries(aeon_testing aeon_common aeon_utility)

install(
    DIRECTORY include/aeon
    DESTINATION include
)

install(
    TARGETS aeon_testing
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
