// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#include <aeon/ptree/reflection.h>
#include <aeon/reflection/reflection.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace aeon;

static const ptree::property_tree test_class_pt{{{"integer_value", 3},
                                                 {"double_value", 2.0},
                                                 {"string_value", "Hello"},
                                                 {"blob_value", ptree::blob{0x10, 0x20, 0x30}}}};

class test_class final : public reflection::reflection_object
{
    AEON_REFLECTION_BEGIN(test_class)
    AEON_REFLECTION_FIELD(std::int64_t, integer_value)
    AEON_REFLECTION_FIELD(double, double_value)
    AEON_REFLECTION_FIELD(std::string, string_value)
    AEON_REFLECTION_FIELD(std::vector<std::uint8_t>, blob_value)
    AEON_REFLECTION_END()

public:
    test_class() = default;
    ~test_class() = default;

    test_class(const test_class &) = default;
    auto operator=(const test_class &) -> test_class & = default;

    test_class(test_class &&) noexcept = default;
    auto operator=(test_class &&) noexcept -> test_class & = default;

    std::int64_t integer_value = 0;
    double double_value = 0.0;
    std::string string_value;
    std::vector<std::uint8_t> blob_value;
};

TEST(test_ptree, ptree_to_reflection_object)
{
    const auto result = ptree::to_reflection_object<test_class>(test_class_pt);

    ASSERT_NE(nullptr, result);

    EXPECT_EQ(3, result->integer_value);
    EXPECT_EQ(2.0, result->double_value);
    EXPECT_EQ("Hello", result->string_value);
    const auto expected_blob_value = std::vector<std::uint8_t>{0x10, 0x20, 0x30};
    EXPECT_EQ(expected_blob_value, result->blob_value);
}

TEST(test_ptree, ptree_from_reflection_object)
{
    test_class test;
    test.integer_value = 3;
    test.double_value = 2.0;
    test.string_value = "Hello";
    test.blob_value = {0x10, 0x20, 0x30};

    const auto pt = ptree::from_reflection_object(test, test_class::reflection_info());
    EXPECT_EQ(test_class_pt, pt);
}

TEST(test_ptree, ptree_from_reflection_object2)
{
    const auto result = ptree::to_reflection_object<test_class>(test_class_pt);
    ASSERT_NE(nullptr, result);
    const auto pt = ptree::from_reflection_object(*result, test_class::reflection_info());

    EXPECT_EQ(test_class_pt, pt);
}
