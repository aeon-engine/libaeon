// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/common/type_traits.h>
#include <gtest/gtest.h>

TEST(test_type_traits, test_preserve_const)
{
    EXPECT_TRUE((std::is_same_v<aeon::common::type_traits::preserve_const_t<int, float>, float>));
    EXPECT_TRUE((std::is_same_v<aeon::common::type_traits::preserve_const_t<const int, float>, const float>));
    EXPECT_FALSE((std::is_same_v<aeon::common::type_traits::preserve_const_t<int, float>, const float>));
    EXPECT_FALSE((std::is_same_v<aeon::common::type_traits::preserve_const_t<const int, float>, float>));

    EXPECT_TRUE((std::is_same_v<aeon::common::type_traits::preserve_const_t<volatile int, float>, float>));
    EXPECT_TRUE((std::is_same_v<aeon::common::type_traits::preserve_const_t<volatile const int, float>, const float>));
    EXPECT_FALSE((std::is_same_v<aeon::common::type_traits::preserve_const_t<volatile int, float>, const float>));
    EXPECT_FALSE((std::is_same_v<aeon::common::type_traits::preserve_const_t<volatile const int, float>, float>));
}

TEST(test_type_traits, test_preserve_volatile)
{
    EXPECT_TRUE((std::is_same_v<aeon::common::type_traits::preserve_volatile_t<int, float>, float>));
    EXPECT_TRUE((std::is_same_v<aeon::common::type_traits::preserve_volatile_t<volatile int, float>, volatile float>));
    EXPECT_FALSE((std::is_same_v<aeon::common::type_traits::preserve_volatile_t<int, float>, volatile float>));
    EXPECT_FALSE((std::is_same_v<aeon::common::type_traits::preserve_volatile_t<volatile int, float>, float>));

    EXPECT_TRUE((std::is_same_v<aeon::common::type_traits::preserve_volatile_t<const int, float>, float>));
    EXPECT_TRUE(
        (std::is_same_v<aeon::common::type_traits::preserve_volatile_t<const volatile int, float>, volatile float>));
    EXPECT_FALSE((std::is_same_v<aeon::common::type_traits::preserve_volatile_t<const int, float>, volatile float>));
    EXPECT_FALSE((std::is_same_v<aeon::common::type_traits::preserve_volatile_t<const volatile int, float>, float>));
}

TEST(test_type_traits, test_preserve_cv)
{
    EXPECT_TRUE((std::is_same_v<aeon::common::type_traits::preserve_cv_t<int, float>, float>));
    EXPECT_TRUE((std::is_same_v<aeon::common::type_traits::preserve_cv_t<const int, float>, const float>));
    EXPECT_FALSE((std::is_same_v<aeon::common::type_traits::preserve_cv_t<int, float>, const float>));
    EXPECT_FALSE((std::is_same_v<aeon::common::type_traits::preserve_cv_t<const int, float>, float>));

    EXPECT_FALSE((std::is_same_v<aeon::common::type_traits::preserve_cv_t<int, float>, volatile float>));
    EXPECT_FALSE((std::is_same_v<aeon::common::type_traits::preserve_cv_t<volatile int, float>, float>));

    EXPECT_TRUE((std::is_same_v<aeon::common::type_traits::preserve_cv_t<volatile int, float>, volatile float>));
    EXPECT_TRUE(
        (std::is_same_v<aeon::common::type_traits::preserve_cv_t<volatile const int, float>, volatile const float>));
    EXPECT_FALSE((std::is_same_v<aeon::common::type_traits::preserve_cv_t<volatile int, float>, volatile const float>));
    EXPECT_FALSE((std::is_same_v<aeon::common::type_traits::preserve_cv_t<volatile const int, float>, volatile float>));
}
