// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/vulkan/instance.h>
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_vulkan, test_create_instance)
{
    const vulkan::application_info app_info{"test", common::version3<std::uint32_t>{1, 0}, "engine",
                                            common::version3<std::uint32_t>{1, 0}};
    vulkan::instance i{app_info, {}, {}};

    EXPECT_NE(nullptr, i.handle());
    EXPECT_FALSE(std::empty(i.physical_devices()));
}

TEST(test_vulkan, test_instance_available_layers)
{
    EXPECT_FALSE(std::empty(vulkan::instance::available_layers()));
}

TEST(test_vulkan, test_instance_available_extensions)
{
    EXPECT_FALSE(std::empty(vulkan::instance::available_extensions()));
}
