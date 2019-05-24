# Copyright (c) 2012-2019 Robin Degen

depend_on(common)
depend_on(streams)

if (AEON_ENABLE_TESTING)
    depend_on(testing)
endif ()
