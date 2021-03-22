// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/ptree/ptree.h>
#include <aeon/ptree/serialization/serialization_abf.h>
#include <aeon/streams/dynamic_stream.h>
#include <aeon/streams/devices/memory_view_device.h>
#include <gtest/gtest.h>

using namespace aeon;

static const ptree::blob blob = {0x01, 0x02, 0x03, 0x04, 0x05, 0x04, 0x03, 0x02, 0x01};
static const ptree::property_tree pt{{{"test", 3}, {"test2", 2.0}, {"data", blob}}};

TEST(test_ptree, json_serialize_deserialize_blob)
{
    const auto abf = ptree::serialization::to_abf(pt);

    auto device = streams::make_dynamic_stream(streams::memory_view_device{abf});
    const auto pt2 = ptree::serialization::from_abf(device);
    EXPECT_EQ(pt, pt2);

    ASSERT_TRUE(pt2.is_object());
    const auto &data_blob = pt2.object_value().at("data");
    ASSERT_TRUE(data_blob.is_blob());
    EXPECT_EQ(blob, data_blob.blob_value());
}

TEST(test_ptree, json_serialize_deserialize_skip_blob)
{
    const auto abf = ptree::serialization::to_abf(pt);
    auto device = streams::make_dynamic_stream(streams::memory_view_device{abf});
    const auto pt2 = ptree::serialization::from_abf(device, ptree::serialization::abf_deserialize_mode::skip_blobs);
    EXPECT_NE(pt, pt2);

    ASSERT_TRUE(pt2.is_object());
    const auto &data_blob = pt2.object_value().at("data");
    ASSERT_TRUE(data_blob.is_blob());
    EXPECT_TRUE(std::empty(data_blob.blob_value()));
}
