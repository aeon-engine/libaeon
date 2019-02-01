// Copyright (c) 2012-2019 Robin Degen

#include <gtest/gtest.h>

#define ENABLE_TEMPORARY_FILE_FIXTURE
#include <aeon/testing/temporary_file_fixture.h>
#include <aeon/utility/configfile.h>
#include <aeon/streams/dynamic_stream.h>
#include <aeon/streams/devices/memory_device.h>
#include <string>

using namespace std::string_literals;

using namespace aeon::testutils;

TEST_F(temporary_file_fixture, test_configfile_create)
{
    ASSERT_NO_THROW(aeon::utility::configfile file);
}

TEST_F(temporary_file_fixture, test_configfile_load_empty)
{
    aeon::utility::configfile file;
    ASSERT_THROW(file.load(get_temporary_file_path()), aeon::utility::configfile_exception);
}

TEST_F(temporary_file_fixture, test_configfile_save)
{
    aeon::utility::configfile file;

    file.set("entry_test", 1337);
    file.set("entry_something", 42);
    file.set("one_or_another", 42.42f);

    ASSERT_NO_THROW(file.save(get_temporary_file_path()));
}

TEST_F(temporary_file_fixture, test_configfile_save_and_load)
{
    {
        aeon::utility::configfile file;

        file.set("entry_test", 1337);
        file.set("entry_something", "42"s);
        file.set("one_or_another", 42.42f);
        file.set("one_theone", false);

        ASSERT_NO_THROW(file.save(get_temporary_file_path()));
    }
    {
        aeon::utility::configfile file;
        ASSERT_NO_THROW(file.load(get_temporary_file_path()));

        ASSERT_TRUE(file.has_entry("entry_test"));
        ASSERT_TRUE(file.has_entry("entry_something"));
        ASSERT_TRUE(file.has_entry("one_or_another"));
        ASSERT_TRUE(file.has_entry("one_theone"));

        ASSERT_EQ(1337, file.get("entry_test", 0));
        ASSERT_EQ("42", file.get("entry_something", ""s));
        ASSERT_FLOAT_EQ(42.42f, file.get("one_or_another", 0.0f));
        ASSERT_EQ(false, file.get("one_theone", true));
    }
}

TEST_F(temporary_file_fixture, test_configfile_has_value)
{
    aeon::utility::configfile file;

    ASSERT_FALSE(file.has_entry("entry_test"));

    file.set("entry_test", 1337);

    ASSERT_TRUE(file.has_entry("entry_test"));
}

TEST_F(temporary_file_fixture, test_configfile_default_value)
{
    aeon::utility::configfile file;

    ASSERT_EQ(42, file.get("entry_test", 42));

    file.set("entry_test", 1337);

    ASSERT_EQ(1337, file.get("entry_test", 42));
}

TEST(test_configfile, test_configfile_read_from_memory)
{
    const std::string data = "test=123\nblah=42\nsomething=hello\n";
    aeon::utility::configfile file;

    auto stream = aeon::streams::make_dynamic_stream(aeon::streams::memory_device{data});
    ASSERT_NO_THROW(file.load(stream));

    ASSERT_TRUE(file.has_entry("test"));
    ASSERT_TRUE(file.has_entry("blah"));
    ASSERT_TRUE(file.has_entry("something"));

    ASSERT_EQ(123, file.get("test", 0));
    ASSERT_EQ(42, file.get("blah", 0));
    ASSERT_EQ("hello", file.get("something", ""s));
}

TEST(test_configfile, test_configfile_read_to_memory)
{
    aeon::utility::configfile file;

    file.set("entry_test", 1337);
    file.set("entry_something", "42"s);
    file.set("one_or_another", 42.42f);
    file.set("one_theone", false);

    std::vector<char> vec;
    ASSERT_NO_THROW(file.save(vec));
    ASSERT_FALSE(vec.empty());
}
