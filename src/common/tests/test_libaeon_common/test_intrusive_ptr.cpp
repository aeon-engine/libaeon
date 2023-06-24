// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/common/intrusive_ptr.h>
#include <gtest/gtest.h>

using namespace aeon;

struct test_obj
{
    int ref_count = 0;

    void intrusive_ptr_add_ref()
    {
        ref_count++;
    }

    void intrusive_ptr_release()
    {
        ref_count--;

        if (ref_count <= 0)
            delete this;
    }
};

TEST(test_intrusive_ptr, ref_count)
{
    auto var = common::make_intrusive_ptr<test_obj>();
    EXPECT_EQ(var->ref_count, 1);

    auto var2 = var;
    EXPECT_EQ(var->ref_count, 2);
    EXPECT_EQ(var2->ref_count, 2);

    auto var3 = var2;
    EXPECT_EQ(var->ref_count, 3);
    EXPECT_EQ(var2->ref_count, 3);
    EXPECT_EQ(var3->ref_count, 3);

    var2.reset();
    EXPECT_EQ(var2, nullptr);
    EXPECT_EQ(var->ref_count, 2);
    EXPECT_EQ(var3->ref_count, 2);

    var3 = nullptr;
    EXPECT_EQ(var2, nullptr);
    EXPECT_EQ(var3, nullptr);
    EXPECT_EQ(var->ref_count, 1);
}

struct add_release_call_check
{
    int intrusive_ptr_add_ref_calls = 0;
    int intrusive_ptr_release_calls = 0;

    void intrusive_ptr_add_ref()
    {
        intrusive_ptr_add_ref_calls++;
    }

    void intrusive_ptr_release()
    {
        intrusive_ptr_release_calls++;
    }
};

TEST(test_intrusive_ptr, add_release_calls)
{
    add_release_call_check check;

    {
        common::intrusive_ptr<add_release_call_check> obj{&check};

        EXPECT_EQ(check.intrusive_ptr_add_ref_calls, 1);
        EXPECT_EQ(check.intrusive_ptr_release_calls, 0);

        auto obj2 = obj;
        EXPECT_EQ(check.intrusive_ptr_add_ref_calls, 2);
        EXPECT_EQ(check.intrusive_ptr_release_calls, 0);

        obj2.reset();
        EXPECT_EQ(check.intrusive_ptr_add_ref_calls, 2);
        EXPECT_EQ(check.intrusive_ptr_release_calls, 1);
    }

    EXPECT_EQ(check.intrusive_ptr_add_ref_calls, 2);
    EXPECT_EQ(check.intrusive_ptr_release_calls, 2);
}

struct intrusive_ref_counter_test : public common::intrusive_ref_counter<int, intrusive_ref_counter_test>
{
};

TEST(test_intrusive_ptr, intrusive_ref_counter)
{
    auto var = common::make_intrusive_ptr<intrusive_ref_counter_test>();
    EXPECT_EQ(var->intrusive_ptr_ref_count(), 1);

    auto var2 = var;
    EXPECT_EQ(var->intrusive_ptr_ref_count(), 2);
    EXPECT_EQ(var2->intrusive_ptr_ref_count(), 2);

    auto var3 = var2;
    EXPECT_EQ(var->intrusive_ptr_ref_count(), 3);
    EXPECT_EQ(var2->intrusive_ptr_ref_count(), 3);
    EXPECT_EQ(var3->intrusive_ptr_ref_count(), 3);

    var2.reset();
    EXPECT_EQ(var2, nullptr);
    EXPECT_EQ(var->intrusive_ptr_ref_count(), 2);
    EXPECT_EQ(var3->intrusive_ptr_ref_count(), 2);

    var3 = nullptr;
    EXPECT_EQ(var2, nullptr);
    EXPECT_EQ(var3, nullptr);
    EXPECT_EQ(var->intrusive_ptr_ref_count(), 1);
}

struct atomic_intrusive_ref_counter_test
    : public common::intrusive_ref_counter<std::atomic<int>, atomic_intrusive_ref_counter_test>
{
};

TEST(test_intrusive_ptr, atomic_intrusive_ref_counter)
{
    auto var = common::make_intrusive_ptr<atomic_intrusive_ref_counter_test>();
    EXPECT_EQ(var->intrusive_ptr_ref_count(), 1);

    auto var2 = var;
    EXPECT_EQ(var->intrusive_ptr_ref_count(), 2);
    EXPECT_EQ(var2->intrusive_ptr_ref_count(), 2);

    auto var3 = var2;
    EXPECT_EQ(var->intrusive_ptr_ref_count(), 3);
    EXPECT_EQ(var2->intrusive_ptr_ref_count(), 3);
    EXPECT_EQ(var3->intrusive_ptr_ref_count(), 3);

    var2.reset();
    EXPECT_EQ(var2, nullptr);
    EXPECT_EQ(var->intrusive_ptr_ref_count(), 2);
    EXPECT_EQ(var3->intrusive_ptr_ref_count(), 2);

    var3 = nullptr;
    EXPECT_EQ(var2, nullptr);
    EXPECT_EQ(var3, nullptr);
    EXPECT_EQ(var->intrusive_ptr_ref_count(), 1);
}
