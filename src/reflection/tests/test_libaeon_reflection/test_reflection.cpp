// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/reflection/reflection.h>
#include <aeon/common/memory.h>
#include <gtest/gtest.h>

using namespace aeon;

class test_class final : public reflection::reflection_object
{
    AEON_REFLECTION_BEGIN(test_class)
    AEON_REFLECTION_FIELD(int, private_integer)
    AEON_REFLECTION_FIELD(float, some_float)
    AEON_REFLECTION_FIELD(std::string, a_string)
    AEON_REFLECTION_END()

public:
    test_class() = default;
    ~test_class() = default;

    test_class(const test_class &) = default;
    auto operator=(const test_class &) -> test_class & = default;

    test_class(test_class &&) noexcept = default;
    auto operator=(test_class &&) noexcept -> test_class & = default;

    [[nodiscard]] auto get_integer() const noexcept
    {
        return private_integer;
    }

    [[nodiscard]] auto get_float() const noexcept
    {
        return some_float;
    }

    [[nodiscard]] const auto &get_string() const noexcept
    {
        return a_string;
    }

private:
    int private_integer = 0;
    float some_float = 0.0f;
    std::string a_string;
};

TEST(test_reflection, test_reflection_rt)
{
    auto test = common::dynamic_unique_ptr_cast<test_class>(test_class::reflection_info().create());
    ASSERT_NE(nullptr, test);

    EXPECT_EQ(test->get_integer(), 0);

    const auto integer = test_class::reflection_info().get_field<int>(*test, u8"private_integer");
    *integer = 5;

    EXPECT_EQ(test->get_integer(), 5);

    EXPECT_EQ(test->get_float(), 0.0);
    const auto flt = test_class::reflection_info().get_field<float>(*test, u8"some_float");
    *flt = 5.0;
    EXPECT_EQ(test->get_float(), 5.0);

    const auto str = test_class::reflection_info().get_field<std::string>(*test, u8"a_string");
    *str = "Hello";
    EXPECT_EQ(test->get_string(), "Hello");
}
