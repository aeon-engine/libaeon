// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#include <aeon/common/tribool.h>
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_tribool, test_tribool_default_false)
{
    EXPECT_FALSE(common::tribool{});
}

TEST(test_tribool, test_tribool_boolean_constructor)
{
    EXPECT_TRUE(common::tribool{true});
    EXPECT_FALSE(common::tribool{false});
}

TEST(test_tribool, test_tribool_indeterminate_constructor)
{
    EXPECT_FALSE(common::tribool{common::indeterminate});

    common::tribool val{common::indeterminate};

    EXPECT_FALSE(val);
    EXPECT_TRUE(common::indeterminate(val));
    EXPECT_TRUE(val.is_indeterminate());
}

TEST(test_tribool, test_tribool_and)
{
    common::tribool val1{true};
    common::tribool val2{true};
    common::tribool val3{false};
    common::tribool val4{common::indeterminate};
    common::tribool val5{common::indeterminate};

    EXPECT_TRUE(val1 && val2);
    EXPECT_FALSE(val1 && val3);
    EXPECT_FALSE(val1 && val2 && val3);
    EXPECT_FALSE(val1 && val4);
    EXPECT_FALSE(val1 && val2 && val4);
    EXPECT_FALSE(val4 && val5);

    EXPECT_FALSE(val1 && val2 && common::indeterminate);
    EXPECT_FALSE(common::indeterminate && val1 && val2);
    EXPECT_FALSE(val1 && common::indeterminate);
    EXPECT_FALSE(common::indeterminate && val1);
}

TEST(test_tribool, test_tribool_or)
{
    common::tribool val1{true};
    common::tribool val2{true};
    common::tribool val3{false};
    common::tribool val4{false};
    common::tribool val5{common::indeterminate};
    common::tribool val6{common::indeterminate};

    EXPECT_TRUE(val1 || val2);
    EXPECT_TRUE(val1 || val3);
    EXPECT_TRUE(val2 || val3);
    EXPECT_TRUE(val1 || val6);
    EXPECT_FALSE(val3 || val4);
    EXPECT_FALSE(val4 || val5);
    EXPECT_FALSE(val5 || val6);
    EXPECT_FALSE(val3 || val6);

    EXPECT_TRUE(val1 || val3 || val5);
    EXPECT_TRUE(val2 || val5 || val6);
    EXPECT_FALSE(val3 || val5 || val6);

    EXPECT_TRUE(val1 || val2 || common::indeterminate);
    EXPECT_TRUE(val1 || val3 || common::indeterminate);
    EXPECT_TRUE(val2 || val3 || common::indeterminate);
    EXPECT_TRUE(val1 || val6 || common::indeterminate);
}

TEST(test_tribool, test_tribool_equals_tribool)
{
    common::tribool val1{true};
    common::tribool val2{true};
    common::tribool val3{false};
    common::tribool val4{false};
    common::tribool val5{common::indeterminate};
    common::tribool val6{common::indeterminate};

    EXPECT_TRUE(val1 == val2);
    EXPECT_FALSE(val1 == val3);
    EXPECT_FALSE(val1 == val5);

    EXPECT_TRUE(val3 == val4);
    EXPECT_FALSE(val3 == val1);
    EXPECT_FALSE(val3 == val5);

    // Indeterminate does never equal another indeterminate
    EXPECT_FALSE(val5 == val6);
    EXPECT_FALSE(val5 == val1);
    EXPECT_FALSE(val5 == val3);
}

TEST(test_tribool, test_tribool_equals_bool)
{
    common::tribool val1{true};
    common::tribool val2{false};
    common::tribool val3{common::indeterminate};

    EXPECT_TRUE(val1 == true);
    EXPECT_FALSE(val1 == false);
    EXPECT_TRUE(true == val1);
    EXPECT_FALSE(false == val1);

    EXPECT_TRUE(val2 == false);
    EXPECT_FALSE(val2 == true);
    EXPECT_TRUE(false == val2);
    EXPECT_FALSE(true == val2);

    // Indeterminate does never equal true or false
    EXPECT_FALSE(val3 == false);
    EXPECT_FALSE(val3 == true);
    EXPECT_FALSE(false == val3);
    EXPECT_FALSE(true == val3);
}

TEST(test_tribool, test_tribool_equals_indeterminate)
{
    common::tribool val1{true};
    common::tribool val2{false};
    common::tribool val3{common::indeterminate};

    EXPECT_FALSE(val1 == common::indeterminate);
    EXPECT_FALSE(common::indeterminate == val1);

    EXPECT_FALSE(val2 == common::indeterminate);
    EXPECT_FALSE(common::indeterminate == val2);

    // Indeterminate does never equal another indeterminate
    EXPECT_FALSE(val3 == common::indeterminate);
    EXPECT_FALSE(common::indeterminate == val3);
}

TEST(test_tribool, test_tribool_not_equals_tribool)
{
    common::tribool val1{true};
    common::tribool val2{true};
    common::tribool val3{false};
    common::tribool val4{false};
    common::tribool val5{common::indeterminate};
    common::tribool val6{common::indeterminate};

    EXPECT_FALSE(val1 != val2);
    EXPECT_TRUE(val1 != val3);
    EXPECT_TRUE(val1 != val5);

    EXPECT_FALSE(val3 != val4);
    EXPECT_TRUE(val3 != val1);
    EXPECT_TRUE(val3 != val5);

    // Indeterminate does never equal another indeterminate
    EXPECT_TRUE(val5 != val6);
    EXPECT_TRUE(val5 != val1);
    EXPECT_TRUE(val5 != val3);
}

TEST(test_tribool, test_tribool_not_equals_bool)
{
    common::tribool val1{true};
    common::tribool val2{false};
    common::tribool val3{common::indeterminate};

    EXPECT_FALSE(val1 != true);
    EXPECT_FALSE(true != val1);
    EXPECT_TRUE(val1 != false);
    EXPECT_TRUE(false != val1);

    EXPECT_FALSE(val2 != false);
    EXPECT_FALSE(false != val2);
    EXPECT_TRUE(val2 != true);
    EXPECT_TRUE(true != val2);

    EXPECT_TRUE(val3 != false);
    EXPECT_TRUE(false != val3);
    EXPECT_TRUE(val3 != true);
    EXPECT_TRUE(true != val3);
}

TEST(test_tribool, test_tribool_not_equals_indeterminate)
{
    common::tribool val1{true};
    common::tribool val2{false};
    common::tribool val3{common::indeterminate};

    EXPECT_TRUE(val1 != common::indeterminate);
    EXPECT_TRUE(common::indeterminate != val1);

    EXPECT_TRUE(val2 != common::indeterminate);
    EXPECT_TRUE(common::indeterminate != val2);

    // Indeterminate does never equal another indeterminate
    EXPECT_TRUE(val3 != common::indeterminate);
    EXPECT_TRUE(common::indeterminate != val3);
}
