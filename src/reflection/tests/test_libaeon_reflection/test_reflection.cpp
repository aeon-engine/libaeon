// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#include <aeon/reflection/reflection.h>
#include <aeon/ast/basic_printer.h>
#include <aeon/ast/class.h>
#include <aeon/ast/enum.h>
#include <aeon/ast/constructor.h>
#include <reflection_unittest_data.h>
#include <gtest/gtest.h>

using namespace aeon;
using namespace aeon::reflection;

TEST(test_reflection, test_reflection_parse_methods)
{
    parser parser;
    const auto result = parser.parse(AEON_REFLECTION_UNITTEST_DATA_PATH "class_with_methods.h");

    ASSERT_TRUE(result.contains("aeon", ast::ast_entity_type::namespace_t));
    ASSERT_TRUE(result["aeon"].contains("testing", ast::ast_entity_type::namespace_t));
    ASSERT_TRUE(result["aeon"]["testing"].contains("test_class", ast::ast_entity_type::class_t));

    const auto &cls = result["aeon"]["testing"]["test_class"].as<ast::ast_class>();
    const auto public_methods = cls.methods(ast::access_specifier::public_t);

    EXPECT_EQ(std::size(public_methods), 4u);

    EXPECT_EQ(1u, std::size(public_methods.find("public_method2", 2)));
    EXPECT_NE(std::end(public_methods), public_methods.find("public_method2", {"int", "float"}));

    EXPECT_EQ(1u, std::size(public_methods.find("public_method2", 3)));
    EXPECT_NE(std::end(public_methods), public_methods.find("public_method2", {"int", "float", "std::string"}));

    EXPECT_EQ((*public_methods.find("public_method2", {"int", "float"}))->exception_specification(),
              ast::exception_specification::basic_noexcept);

    EXPECT_EQ(public_methods.find("public_method2", 2).at(0), *public_methods.find("public_method2", {"int", "float"}));
    EXPECT_EQ(public_methods.find("public_method2", 3).at(0),
              *public_methods.find("public_method2", {"int", "float", "std::string"}));

    const auto protected_methods = cls.methods(ast::access_specifier::protected_t);
    EXPECT_EQ(std::size(protected_methods), 3u);

    const auto private_methods = cls.methods(ast::access_specifier::private_t);
    EXPECT_EQ(std::size(private_methods), 3u);
    EXPECT_FALSE(std::empty(private_methods.find("private_method1")));
    EXPECT_TRUE(private_methods.contains("private_method1", 0));
    EXPECT_TRUE(private_methods.contains("private_method2", {"int", "float", "std::string"}));
    EXPECT_TRUE(private_methods.contains("private_method3", {"aeon::testing::unknown_type3"}));

    const auto ctors = cls.constructors();
    EXPECT_EQ(1u, std::size(ctors.find(0)));
    EXPECT_EQ(1u, std::size(ctors.find({"int", "float"})));
}

TEST(test_reflection, test_reflection_enum)
{
    parser parser;
    const auto result = parser.parse(AEON_REFLECTION_UNITTEST_DATA_PATH "enum.h");

    ASSERT_TRUE(result.contains("aeon", ast::ast_entity_type::namespace_t));
    ASSERT_TRUE(result["aeon"].contains("testing", ast::ast_entity_type::namespace_t));
    ASSERT_TRUE(result["aeon"]["testing"].contains("test_enum", ast::ast_entity_type::enum_t));
    ASSERT_TRUE(result["aeon"]["testing"].contains("test_enum_class", ast::ast_entity_type::enum_t));

    const auto &test_enum = result["aeon"]["testing"]["test_enum"].as<ast::ast_enum>();
    EXPECT_EQ(test_enum.constants_count(), 3u);
    EXPECT_TRUE((test_enum.constants() ==
                 std::vector<std::string>{"test_enum_member1", "test_enum_member2", "test_enum_member3"}));

    const auto &test_enum_class = result["aeon"]["testing"]["test_enum_class"].as<ast::ast_enum>();
    EXPECT_EQ(test_enum_class.constants_count(), 4u);
    EXPECT_TRUE((test_enum_class.constants() == std::vector<std::string>{"member1", "member2", "member3", "member4"}));
}

TEST(test_reflection, test_reflection_static_function)
{
    parser parser;
    const auto result = parser.parse(AEON_REFLECTION_UNITTEST_DATA_PATH "class_with_static_function.h");

    ASSERT_TRUE(result.contains("aeon", ast::ast_entity_type::namespace_t));
    ASSERT_TRUE(result["aeon"].contains("testing", ast::ast_entity_type::namespace_t));
    ASSERT_TRUE(result["aeon"]["testing"].contains("test_class", ast::ast_entity_type::class_t));

    const auto &cls = result["aeon"]["testing"]["test_class"].as<ast::ast_class>();

    EXPECT_EQ(std::size(cls), 4u);

    const auto public_method_itr = cls.find("public_method");
    ASSERT_NE(public_method_itr, std::end(cls));
    const auto &public_method = (*public_method_itr)->as<ast::ast_method>();
    EXPECT_FALSE(public_method.is_static());

    const auto public_static_method_itr = cls.find("public_static_method");
    ASSERT_NE(public_static_method_itr, std::end(cls));
    const auto &public_static_method = (*public_static_method_itr)->as<ast::ast_method>();
    EXPECT_TRUE(public_static_method.is_static());
}

TEST(test_reflection, test_reflection_function_types)
{
    parser parser;
    const auto result = parser.parse(AEON_REFLECTION_UNITTEST_DATA_PATH "functions_and_methods.h");

    const auto public_method_result = result.find_recursive("public_method", ast::ast_entity_type::method_t);
    ASSERT_NE(public_method_result, nullptr);

    const auto public__static_method_result =
        result.find_recursive("public_static_method", ast::ast_entity_type::method_t);
    ASSERT_NE(public__static_method_result, nullptr);

    const auto normal_function_result = result.find_recursive("normal_function", ast::ast_entity_type::function_t);
    ASSERT_NE(normal_function_result, nullptr);

    const auto static_function_result = result.find_recursive("static_function", ast::ast_entity_type::function_t);
    ASSERT_NE(static_function_result, nullptr);

    const auto inlined_function_result = result.find_recursive("inlined_function", ast::ast_entity_type::function_t);
    ASSERT_NE(inlined_function_result, nullptr);
}

TEST(test_reflection, test_reflection_fields)
{
    parser parser;
    const auto result = parser.parse(AEON_REFLECTION_UNITTEST_DATA_PATH "class_with_fields.h");

    const auto test_class_result = result.find_recursive("test_class", ast::ast_entity_type::class_t);
    ASSERT_NE(test_class_result, nullptr);

    const auto &test_class = test_class_result->as<ast::ast_class>();
    ASSERT_NE(std::empty(test_class), true);
}

TEST(test_reflection, test_reflection_basic_printer)
{
    parser parser;
    const auto result = parser.parse(AEON_REFLECTION_UNITTEST_DATA_PATH "functions_and_methods.h");
    print_basic(result);
}

TEST(test_reflection, test_reflection_annotate)
{
    parser parser;
    const auto result = parser.parse(AEON_REFLECTION_UNITTEST_DATA_PATH "annotations.h");

    const auto &test_class1 = result["aeon"]["testing"]["test_class1"].as<ast::ast_class>();
    EXPECT_FALSE(test_class1.has_annotations());

    const auto &test_class2 = result["aeon"]["testing"]["test_class2"].as<ast::ast_class>();
    EXPECT_TRUE(test_class2.has_annotations());
    ASSERT_EQ(1u, std::size(test_class2.annotations()));
    EXPECT_EQ("serialize", test_class2.annotations().at(0));
    EXPECT_TRUE(test_class2.has_annotation("serialize"));
    EXPECT_FALSE(test_class2.has_annotation("something_else"));

    const auto &test_class3 = result["aeon"]["testing"]["test_class3"].as<ast::ast_class>();
    EXPECT_TRUE(test_class3.has_annotations());
    ASSERT_EQ(2u, std::size(test_class3.annotations()));
    EXPECT_EQ("serialize", test_class3.annotations().at(0));
    EXPECT_EQ("something_else", test_class3.annotations().at(1));
    EXPECT_TRUE(test_class3.has_annotation("serialize"));
    EXPECT_TRUE(test_class3.has_annotation("something_else"));

    const auto fields = test_class3.fields();
    const auto field_a = fields.find("a");
    EXPECT_NE(std::end(fields), field_a);
    EXPECT_FALSE((*field_a)->has_annotations());

    const auto field_b = fields.find("b");
    EXPECT_NE(std::end(fields), field_b);
    EXPECT_TRUE((*field_b)->has_annotations());
    EXPECT_TRUE((*field_b)->has_annotation("ignore"));
}
