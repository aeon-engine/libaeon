# Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

set(SOURCES
    private/reflection.cpp
    private/serialization/serialization_abf.cpp
    private/serialization/serialization_ini.cpp
    private/serialization/serialization_json.cpp
    private/serialization/serialization_xml.cpp
    private/xml_dom/xml_document.cpp
    private/xml_dom/xml_node.cpp
    public/aeon/ptree/config_file.h
    public/aeon/ptree/exception.h
    public/aeon/ptree/impl/config_file_impl.h
    public/aeon/ptree/impl/ptree_impl.h
    public/aeon/ptree/ptree.h
    public/aeon/ptree/reflection.h
    public/aeon/ptree/serialization/exception.h
    public/aeon/ptree/serialization/serialization_abf.h
    public/aeon/ptree/serialization/serialization_ini.h
    public/aeon/ptree/serialization/serialization_json.h
    public/aeon/ptree/serialization/serialization_xml.h
    public/aeon/ptree/xml_dom/exception.h
    public/aeon/ptree/xml_dom/xml_document.h
    public/aeon/ptree/xml_dom/xml_node.h
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_library(aeon_ptree
    STATIC
        ${SOURCES}
)

set_target_properties(aeon_ptree PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_ptree
    PUBLIC
        public
)

target_link_libraries(aeon_ptree
    aeon_common
    aeon_rdp
    aeon_reflection
    aeon_streams
    aeon_unicode
    aeon_variant
)

install(
    DIRECTORY public/aeon
    DESTINATION include
)

if (AEON_ENABLE_TESTING)
    add_subdirectory(tests)
endif ()
