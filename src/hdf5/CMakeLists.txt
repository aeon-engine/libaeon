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

message(STATUS "Building libAeon with HDF5 wrapper support.")

add_subdirectory(${CMAKE_SOURCE_DIR}/dep/hdf5 dep/hdf5)

set(LIB_AEON_HDF5_SOURCE
    include/aeon/hdf5/hdf5_dataset.h
    src/hdf5_dataset.cpp
    include/aeon/hdf5/hdf5_dataset_properties.h
    src/hdf5_dataset_properties.cpp
    include/aeon/hdf5/hdf5_dataset_wrapper.h
    src/hdf5_dataset_wrapper.cpp
    include/aeon/hdf5/hdf5_dataspace.h
    src/hdf5_dataspace.cpp
    include/aeon/hdf5/hdf5_datatype.h
    src/hdf5_datatype.cpp
    include/aeon/hdf5/hdf5_file.h
    src/hdf5_file.cpp
    include/aeon/hdf5/hdf5_object.h
    src/hdf5_object.cpp
    include/aeon/hdf5/hdf5_object_iterator.h
    src/hdf5_object_iterator.cpp
    include/aeon/hdf5/hdf5_scoped_create_group.h
    src/hdf5_scoped_create_group.cpp
)

source_group(hdf5 FILES ${LIB_AEON_HDF5_SOURCE})

add_library(aeon_hdf5 STATIC ${LIB_AEON_HDF5_SOURCE})

set_target_properties(aeon_hdf5 PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_hdf5 PUBLIC include)
target_link_libraries(aeon_hdf5 aeon_common aeon_filesystem hdf5-static hdf5_hl-static)

install(
    DIRECTORY include
    DESTINATION include
)

add_subdirectory(tests)
