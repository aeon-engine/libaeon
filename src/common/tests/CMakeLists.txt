# Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

include(Unittests)

add_unit_test_suite(
    NO_GTEST_MAIN
    TARGET test_libaeon_common
    SOURCES
        main.cpp
        test_base64.cpp
        test_bits.cpp
        test_buffer.cpp
        test_color.cpp
        test_commandline_parser.cpp
        test_container.cpp
        test_dispatcher.cpp
        test_element_type.cpp
        test_endianness.cpp
        test_flags.cpp
        test_from_chars.cpp
        test_general_tree.cpp
        test_hash.cpp
        test_intrusive_ptr.cpp
        test_lexical_parse.cpp
        test_literals.cpp
        test_path.cpp
        test_pmr.cpp
        test_scope_guard.cpp
        test_signals.cpp
        test_singleton.cpp
        test_string_literal.cpp
        test_string_table.cpp
        test_string_utils.cpp
        test_stringtraits.cpp
        test_tribool.cpp
        test_type_traits.cpp
        test_u8stream.cpp
        test_unique_obj.cpp
        test_unordered_flatmap.cpp
        test_unordered_flatset.cpp
        test_uuid.cpp
        test_version.cpp
    INCLUDES
        ${CMAKE_CURRENT_BINARY_DIR}
    LIBRARIES aeon_common
    FOLDER dep/libaeon/tests
)
