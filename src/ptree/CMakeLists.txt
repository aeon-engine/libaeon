# Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

set(LIB_AEON_PTREE_PUBLIC_SOURCE
    include/aeon/ptree/config_file.h
    include/aeon/ptree/ptree.h
    include/aeon/ptree/exception.h
    include/aeon/ptree/reflection.h
)

source_group(public FILES ${LIB_AEON_PTREE_PUBLIC_SOURCE})

set(LIB_AEON_PTREE_PUBLIC_IMPL_SOURCE
    include/aeon/ptree/impl/config_file_impl.h
    include/aeon/ptree/impl/ptree_impl.h
)

source_group(public\\impl FILES ${LIB_AEON_PTREE_PUBLIC_IMPL_SOURCE})

set(LIB_AEON_PTREE_PUBLIC_SERIALIZATION_SOURCE
    include/aeon/ptree/serialization/exception.h
    include/aeon/ptree/serialization/serialization_abf.h
    include/aeon/ptree/serialization/serialization_ini.h
    include/aeon/ptree/serialization/serialization_json.h
    include/aeon/ptree/serialization/serialization_xml.h
)

source_group(public\\serialization FILES ${LIB_AEON_PTREE_PUBLIC_SERIALIZATION_SOURCE})

set(LIB_AEON_PTREE_PUBLIC_XML_DOM_SOURCE
    include/aeon/ptree/xml_dom/exception.h
    include/aeon/ptree/xml_dom/xml_document.h
    include/aeon/ptree/xml_dom/xml_node.h
)

source_group(public\\xml_dom FILES ${LIB_AEON_PTREE_PUBLIC_XML_DOM_SOURCE})

set(LIB_AEON_PTREE_PRIVATE_SOURCE
    src/reflection.cpp
)

source_group(private FILES ${LIB_AEON_PTREE_PRIVATE_SOURCE})

set(LIB_AEON_PTREE_PRIVATE_SERIALIZATION_SOURCE
    src/serialization/serialization_abf.cpp
    src/serialization/serialization_ini.cpp
    src/serialization/serialization_json.cpp
    src/serialization/serialization_xml.cpp
)

source_group(private\\serialization FILES ${LIB_AEON_PTREE_PRIVATE_SERIALIZATION_SOURCE})

set(LIB_AEON_PTREE_PRIVATE_XML_DOM_SOURCE
    src/xml_dom/xml_document.cpp
    src/xml_dom/xml_node.cpp
)

source_group(private\\xml_dom FILES ${LIB_AEON_PTREE_PRIVATE_XML_DOM_SOURCE})

add_library(aeon_ptree
    STATIC
        ${LIB_AEON_PTREE_PUBLIC_SOURCE}
        ${LIB_AEON_PTREE_PUBLIC_IMPL_SOURCE}
        ${LIB_AEON_PTREE_PUBLIC_SERIALIZATION_SOURCE}
        ${LIB_AEON_PTREE_PUBLIC_XML_DOM_SOURCE}
        ${LIB_AEON_PTREE_PRIVATE_SOURCE}
        ${LIB_AEON_PTREE_PRIVATE_SERIALIZATION_SOURCE}
        ${LIB_AEON_PTREE_PRIVATE_XML_DOM_SOURCE}
)

set_target_properties(aeon_ptree PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_ptree
    PUBLIC
        include
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
    DIRECTORY include/aeon
    DESTINATION include
)

if (AEON_ENABLE_TESTING)
    add_subdirectory(tests)
endif ()
