# Copyright (c) 2012-2018 Robin Degen
#
# Permission is hereby granted, free of charge, to any person
# obtaining a copy of this software and associated documentation
# files (the "Software"), to deal in the Software without
# restriction, including without limitation the rights to use,
# copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following
# conditions:
#
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
# OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
# HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
# WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
# OTHER DEALINGS IN THE SOFTWARE.

message(STATUS "Building libAeon with CURL support.")

add_subdirectory(${CMAKE_SOURCE_DIR}/dep/curl dep/curl)

set(LIB_AEON_CURL_SOURCE
    include/aeon/curl/easy_wrapper.h
    src/easy_wrapper.cpp
    include/aeon/curl/exceptions.h
    include/aeon/curl/global_wrapper.h
    src/global_wrapper.cpp
    include/aeon/curl/url_downloader.h
    src/url_downloader.cpp
)

source_group(curl FILES ${LIB_AEON_CURL_SOURCE})

add_library(aeon_curl STATIC ${LIB_AEON_CURL_SOURCE})

set_target_properties(aeon_curl PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_curl PUBLIC include)
target_link_libraries(aeon_curl aeon_common aeon_streams curl)

install(
    DIRECTORY include
    DESTINATION include
)
