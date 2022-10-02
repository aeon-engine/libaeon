// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/common/containers/buffer.h>
#include <aeon/common/platform.h>

#if (defined(AEON_PLATFORM_OS_WINDOWS))
#include <aeon/common/allocators/windows_heap_allocator.h>
#endif

#include <gtest/gtest.h>

using namespace aeon;

TEST(test_containers_buffer, test_containers_buffer_default_create)
{
    common::containers::buffer<int> a;
    EXPECT_EQ(0, a.capacity());
    EXPECT_EQ(nullptr, a.data());

    common::containers::buffer<float> b;
    EXPECT_EQ(0, b.capacity());
    EXPECT_EQ(nullptr, b.data());
}

TEST(test_containers_buffer, test_containers_buffer_create_with_size)
{
    common::containers::buffer<int> a{100};
    EXPECT_EQ(100, a.capacity());
    EXPECT_NE(nullptr, a.data());

    common::containers::buffer<float> b{100};
    EXPECT_EQ(100, b.capacity());
    EXPECT_NE(nullptr, b.data());
}

TEST(test_containers_buffer, test_containers_buffer_resize_from_empty)
{
    common::containers::buffer<int> a;
    EXPECT_EQ(0, a.capacity());
    EXPECT_EQ(nullptr, a.data());

    a.resize(100);
    EXPECT_EQ(100, a.capacity());
    EXPECT_NE(nullptr, a.data());

    common::containers::buffer<float> b;
    EXPECT_EQ(0, b.capacity());
    EXPECT_EQ(nullptr, b.data());

    b.resize(100);
    EXPECT_EQ(100, b.capacity());
    EXPECT_NE(nullptr, b.data());
}

TEST(test_containers_buffer, test_containers_buffer_reset)
{
    common::containers::buffer<int> a{100};
    EXPECT_EQ(100, a.capacity());
    EXPECT_NE(nullptr, a.data());

    a.reset();
    EXPECT_EQ(0, a.capacity());
    EXPECT_EQ(nullptr, a.data());

    common::containers::buffer<float> b{100};
    EXPECT_EQ(100, b.capacity());
    EXPECT_NE(nullptr, b.data());

    b.reset();
    EXPECT_EQ(0, b.capacity());
    EXPECT_EQ(nullptr, b.data());
}

TEST(test_containers_buffer, test_containers_buffer_move_ctor)
{
    common::containers::buffer<int> a(100);
    EXPECT_EQ(100, a.capacity());
    EXPECT_NE(nullptr, a.data());

    const auto data_ptr = a.data();

    common::containers::buffer b{std::move(a)};
    EXPECT_EQ(100, b.capacity());
    EXPECT_EQ(data_ptr, b.data());

    EXPECT_EQ(0, a.capacity());
    EXPECT_EQ(nullptr, a.data());
}

TEST(test_containers_buffer, test_containers_buffer_move_assignment)
{
    common::containers::buffer<int> a(100);
    EXPECT_EQ(100, a.capacity());
    EXPECT_NE(nullptr, a.data());

    const auto data_ptr = a.data();

    common::containers::buffer<int> b(50);
    EXPECT_EQ(50, b.capacity());
    EXPECT_NE(nullptr, b.data());

    const auto b_data_ptr = b.data();

    b = std::move(a);
    EXPECT_EQ(100, b.capacity());
    EXPECT_EQ(data_ptr, b.data());
    EXPECT_NE(b_data_ptr, b.data());

    EXPECT_EQ(0, a.capacity());
    EXPECT_EQ(nullptr, a.data());
}

TEST(test_containers_buffer, test_containers_buffer_copy_ctor)
{
    common::containers::buffer<int> a(100);
    EXPECT_EQ(100, a.capacity());
    EXPECT_NE(nullptr, a.data());

    common::containers::buffer b{a};
    EXPECT_EQ(100, b.capacity());

    EXPECT_EQ(100, a.capacity());
    EXPECT_NE(a.data(), b.data());
}

TEST(test_containers_buffer, test_containers_buffer_copy_assignment)
{
    common::containers::buffer<int> a(100);
    EXPECT_EQ(100, a.capacity());
    EXPECT_NE(nullptr, a.data());

    common::containers::buffer<int> b;
    b = a;

    EXPECT_EQ(100, b.capacity());

    EXPECT_EQ(100, a.capacity());
    EXPECT_NE(a.data(), b.data());
}

TEST(test_containers_buffer, test_containers_buffer_iterators)
{
    common::containers::buffer<int> a(10);

    int value = 0;
    for (auto &val : a)
        val = ++value;

    EXPECT_EQ(10, value);

    value = 0;
    for (auto &val : a)
        EXPECT_EQ(val, ++value);
}

TEST(test_containers_buffer, test_containers_data_is_copied)
{
    common::containers::buffer<int> a(10);

    int value = 0;
    for (auto &val : a)
        val = ++value;

    EXPECT_EQ(10, value);

    common::containers::buffer b(a);

    value = 0;
    for (auto &val : b)
        EXPECT_EQ(val, ++value);
}

#if (defined(AEON_PLATFORM_OS_WINDOWS))
TEST(test_containers_buffer, test_containers_buffer_default_create_windows_heap_allocator)
{
    common::containers::buffer<int, common::allocators::windows_heap_allocator<int>> a;
    EXPECT_EQ(0, a.capacity());
    EXPECT_EQ(nullptr, a.data());

    common::containers::buffer<float, common::allocators::windows_heap_allocator<float>> b;
    EXPECT_EQ(0, b.capacity());
    EXPECT_EQ(nullptr, b.data());
}

TEST(test_containers_buffer, test_containers_buffer_create_with_size_windows_heap_allocator)
{
    common::containers::buffer<int, common::allocators::windows_heap_allocator<int>> a{100};
    EXPECT_EQ(100, a.capacity());
    EXPECT_NE(nullptr, a.data());

    common::containers::buffer<float, common::allocators::windows_heap_allocator<float>> b{100};
    EXPECT_EQ(100, b.capacity());
    EXPECT_NE(nullptr, b.data());
}

TEST(test_containers_buffer, test_containers_buffer_resize_from_empty_windows_heap_allocator)
{
    common::containers::buffer<int, common::allocators::windows_heap_allocator<int>> a;
    EXPECT_EQ(0, a.capacity());
    EXPECT_EQ(nullptr, a.data());

    a.resize(100);
    EXPECT_EQ(100, a.capacity());
    EXPECT_NE(nullptr, a.data());

    common::containers::buffer<float, common::allocators::windows_heap_allocator<float>> b;
    EXPECT_EQ(0, b.capacity());
    EXPECT_EQ(nullptr, b.data());

    b.resize(100);
    EXPECT_EQ(100, b.capacity());
    EXPECT_NE(nullptr, b.data());
}

TEST(test_containers_buffer, test_containers_buffer_reset_windows_heap_allocator)
{
    common::containers::buffer<int, common::allocators::windows_heap_allocator<int>> a{100};
    EXPECT_EQ(100, a.capacity());
    EXPECT_NE(nullptr, a.data());

    a.reset();
    EXPECT_EQ(0, a.capacity());
    EXPECT_EQ(nullptr, a.data());

    common::containers::buffer<float, common::allocators::windows_heap_allocator<float>> b{100};
    EXPECT_EQ(100, b.capacity());
    EXPECT_NE(nullptr, b.data());

    b.reset();
    EXPECT_EQ(0, b.capacity());
    EXPECT_EQ(nullptr, b.data());
}

TEST(test_containers_buffer, test_containers_buffer_move_ctor_windows_heap_allocator)
{
    common::containers::buffer<int, common::allocators::windows_heap_allocator<int>> a(100);
    EXPECT_EQ(100, a.capacity());
    EXPECT_NE(nullptr, a.data());

    const auto data_ptr = a.data();

    common::containers::buffer b{std::move(a)};
    EXPECT_EQ(100, b.capacity());
    EXPECT_EQ(data_ptr, b.data());

    EXPECT_EQ(0, a.capacity());
    EXPECT_EQ(nullptr, a.data());
}

TEST(test_containers_buffer, test_containers_buffer_move_assignment_windows_heap_allocator)
{
    common::containers::buffer<int, common::allocators::windows_heap_allocator<int>> a(100);
    EXPECT_EQ(100, a.capacity());
    EXPECT_NE(nullptr, a.data());

    const auto data_ptr = a.data();

    common::containers::buffer<int, common::allocators::windows_heap_allocator<int>> b(50);
    EXPECT_EQ(50, b.capacity());
    EXPECT_NE(nullptr, b.data());

    const auto b_data_ptr = b.data();

    b = std::move(a);
    EXPECT_EQ(100, b.capacity());
    EXPECT_EQ(data_ptr, b.data());
    EXPECT_NE(b_data_ptr, b.data());

    EXPECT_EQ(0, a.capacity());
    EXPECT_EQ(nullptr, a.data());
}

TEST(test_containers_buffer, test_containers_buffer_copy_ctor_windows_heap_allocator)
{
    common::containers::buffer<int, common::allocators::windows_heap_allocator<int>> a(100);
    EXPECT_EQ(100, a.capacity());
    EXPECT_NE(nullptr, a.data());

    common::containers::buffer b{a};
    EXPECT_EQ(100, b.capacity());

    EXPECT_EQ(100, a.capacity());
    EXPECT_NE(a.data(), b.data());
}

TEST(test_containers_buffer, test_containers_buffer_copy_assignment_windows_heap_allocator)
{
    common::containers::buffer<int, common::allocators::windows_heap_allocator<int>> a(100);
    EXPECT_EQ(100, a.capacity());
    EXPECT_NE(nullptr, a.data());

    common::containers::buffer<int, common::allocators::windows_heap_allocator<int>> b;
    b = a;

    EXPECT_EQ(100, b.capacity());

    EXPECT_EQ(100, a.capacity());
    EXPECT_NE(a.data(), b.data());
}

TEST(test_containers_buffer, test_containers_buffer_iterators_windows_heap_allocator)
{
    common::containers::buffer<int, common::allocators::windows_heap_allocator<int>> a(10);

    int value = 0;
    for (auto &val : a)
        val = ++value;

    EXPECT_EQ(10, value);

    value = 0;
    for (auto &val : a)
        EXPECT_EQ(val, ++value);
}

TEST(test_containers_buffer, test_containers_data_is_copied_windows_heap_allocator)
{
    common::containers::buffer<int, common::allocators::windows_heap_allocator<int>> a(10);

    int value = 0;
    for (auto &val : a)
        val = ++value;

    EXPECT_EQ(10, value);

    common::containers::buffer b(a);

    value = 0;
    for (auto &val : b)
        EXPECT_EQ(val, ++value);
}
#endif
