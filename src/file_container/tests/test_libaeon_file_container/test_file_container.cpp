// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#include <aeon/file_container/container.h>
#include <aeon/streams/stream_writer.h>
#include <aeon/streams/stream_reader.h>
#include <aeon/streams/make_vector_view_stream.h>
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_resource_file, stream_basic_read_write)
{
    const auto expected_name = "ThisIsAName";
    const auto expected_uuid = common::uuid::generate();

    std::vector<std::uint8_t> data;

    std::string test_data = "This is test data.";

    {
        file_container::container io{expected_name, expected_uuid};
        io.metadata()["test_metadata"] = 1337;
        io.metadata()["another_metadata"] = "This is a string.";

        auto stream = io.stream();
        streams::stream_writer writer{stream};

        writer << test_data;

        auto output_stream = streams::make_vector_view_stream(data);
        io.write(output_stream);
    }

    // Check reading only the header
    {
        auto input_stream = streams::make_vector_view_stream(data);
        file_container::container io{input_stream, file_container::read_items::header};
        EXPECT_EQ(expected_name, io.name());
        EXPECT_EQ(expected_uuid, io.id());
        EXPECT_EQ(0, io.stream().size());
        EXPECT_TRUE(io.metadata().is_null());
    }

    // Check reading only the header and metadata
    {
        auto input_stream = streams::make_vector_view_stream(data);
        file_container::container io{input_stream,
                                     file_container::read_items::header | file_container::read_items::metadata};
        EXPECT_EQ(expected_name, io.name());
        EXPECT_EQ(expected_uuid, io.id());
        EXPECT_EQ(0, io.stream().size());
        EXPECT_FALSE(io.metadata().is_null());

        EXPECT_EQ(1337, io.metadata().at("test_metadata"));
        EXPECT_EQ("This is a string.", io.metadata().at("another_metadata"));
    }

    // Read header and data, no metadata
    {
        auto input_stream = streams::make_vector_view_stream(data);
        file_container::container io{input_stream,
                                     file_container::read_items::header | file_container::read_items::data};
        EXPECT_EQ(expected_name, io.name());
        EXPECT_EQ(expected_uuid, io.id());

        EXPECT_EQ(std::size(test_data), static_cast<std::size_t>(io.stream().size()));

        auto stream = io.stream();
        streams::stream_reader reader{stream};
        EXPECT_EQ(test_data, reader.read_to_string());

        EXPECT_TRUE(io.metadata().is_null());
    }

    // Read all
    {
        auto input_stream = streams::make_vector_view_stream(data);
        file_container::container io{input_stream, file_container::read_items::all};
        EXPECT_EQ(expected_name, io.name());
        EXPECT_EQ(expected_uuid, io.id());
        EXPECT_EQ(std::size(test_data), static_cast<std::size_t>(io.stream().size()));

        auto stream = io.stream();
        streams::stream_reader reader{stream};
        EXPECT_EQ(test_data, reader.read_to_string());

        EXPECT_FALSE(io.metadata().is_null());

        EXPECT_EQ(1337, io.metadata().at("test_metadata"));
        EXPECT_EQ("This is a string.", io.metadata().at("another_metadata"));
    }
}
