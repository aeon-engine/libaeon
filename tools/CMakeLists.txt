# Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

include(ComponentUtils)

check_component_enabled(streams streams_enabled)

if (${streams_enabled})
    add_subdirectory(header_data_generator)
endif ()
