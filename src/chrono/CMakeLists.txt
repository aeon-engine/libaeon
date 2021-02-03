# Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

handle_local_dependencies_file()

set(LIB_AEON_CHRONO_PUBLIC_SOURCE
    include/aeon/chrono/calendar.h
    include/aeon/chrono/offset.h
    include/aeon/chrono/timezone.h
)

source_group(public FILES ${LIB_AEON_CHRONO_PUBLIC_SOURCE})

set(LIB_AEON_CHRONO_PRIVATE_SOURCE
    src/calendar.cpp
    src/timezone.cpp
    src/timezone_impl.h
)

source_group(private FILES ${LIB_AEON_CHRONO_PRIVATE_SOURCE})

add_library(aeon_chrono STATIC
    ${LIB_AEON_CHRONO_PUBLIC_SOURCE}
    ${LIB_AEON_CHRONO_PRIVATE_SOURCE}
)

set_target_properties(aeon_chrono PROPERTIES
    FOLDER dep/libaeon
)

target_include_directories(aeon_chrono
    PUBLIC
        include
)

target_link_libraries(aeon_chrono
    aeon_common
    ICU::tu
    ICU::uc
    ICU::i18n
)

install(
    DIRECTORY include/aeon
    DESTINATION include
)

if (AEON_ENABLE_TESTING)
    add_subdirectory(tests)
endif ()
