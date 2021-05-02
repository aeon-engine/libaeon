// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/common/pmr.h>
#include <gtest/gtest.h>
#include <array>

using namespace aeon;

TEST(test_pmr, test_pmr_make_unique)
{
    std::array<std::byte, 16> buffer;
    std::pmr::monotonic_buffer_resource allocator(std::data(buffer), std::size(buffer),
                                                  std::pmr::null_memory_resource());

    auto ptr = common::pmr::make_unique<std::uint32_t>(&allocator, 0x11223344u);
    EXPECT_EQ(*ptr, 0x11223344u);

    auto ptr2 = common::pmr::make_unique<std::uint32_t>(&allocator, 0x55667788u);
    EXPECT_EQ(*ptr, 0x11223344u);
    EXPECT_EQ(*ptr2, 0x55667788u);

    auto ptr3 = common::pmr::make_unique<std::uint32_t>(&allocator, 0x99aabbccu);
    EXPECT_EQ(*ptr, 0x11223344u);
    EXPECT_EQ(*ptr2, 0x55667788u);
    EXPECT_EQ(*ptr3, 0x99aabbccu);

    auto ptr4 = common::pmr::make_unique<std::uint32_t>(&allocator, 0xddeeff11u);
    EXPECT_EQ(*ptr, 0x11223344u);
    EXPECT_EQ(*ptr2, 0x55667788u);
    EXPECT_EQ(*ptr3, 0x99aabbccu);
    EXPECT_EQ(*ptr4, 0xddeeff11u);

    // After 16 bytes, the buffer is exhausted; so bad_alloc should be thrown.
    EXPECT_THROW([[maybe_unused]] auto ptr5 = common::pmr::make_unique<std::uint32_t>(&allocator, 0x12345678u),
                 std::bad_alloc);
}
