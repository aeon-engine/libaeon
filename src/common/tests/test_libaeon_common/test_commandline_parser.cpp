// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/common/commandline_parser.h>
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_commandline_parser, test_commandline_parser_positional)
{
    common::commandline_parser parser;
    parser.add_positional("a", "description 1");
    parser.add_positional("b", "description 2");
    parser.add_positional("c", "description 3");

    const auto result = parser.parse({"1", "2", "3"});

    EXPECT_TRUE(result);
    EXPECT_TRUE(result.success());
    EXPECT_FALSE(result.failed());

    EXPECT_EQ(result.positional(0), "1");
    EXPECT_EQ(result.positional(1), "2");
    EXPECT_EQ(result.positional(2), "3");

    EXPECT_ANY_THROW([[maybe_unused]] auto arg = result.positional(3));
}

TEST(test_commandline_parser, test_commandline_parser_short_options)
{
    common::commandline_parser parser;
    parser.add_option("a", "description 1");
    parser.add_option("b", "description 2");

    const auto result = parser.parse({"-a", "-b"});

    EXPECT_TRUE(result);
    EXPECT_TRUE(result.success());
    EXPECT_FALSE(result.failed());

    EXPECT_TRUE(result.has_option("a"));
    EXPECT_TRUE(result.has_option("b"));
    EXPECT_FALSE(result.has_option("c"));

    EXPECT_TRUE(parser.parse({"-a"}));
    EXPECT_TRUE(parser.parse({"-b"}));
    EXPECT_FALSE(parser.parse({"-c"}));
    EXPECT_FALSE(parser.parse({"--a"}));
    EXPECT_FALSE(parser.parse({"--b"}));
    EXPECT_FALSE(parser.parse({"--a", "--b"}));
}

TEST(test_commandline_parser, test_commandline_parser_long_options)
{
    common::commandline_parser parser;
    parser.add_option("aaa", "description 1");
    parser.add_option("bbb", "description 2");

    const auto result = parser.parse({"--aaa", "--bbb"});

    EXPECT_TRUE(result);
    EXPECT_TRUE(result.success());
    EXPECT_FALSE(result.failed());

    EXPECT_TRUE(result.has_option("aaa"));
    EXPECT_TRUE(result.has_option("bbb"));
    EXPECT_FALSE(result.has_option("ccc"));

    EXPECT_TRUE(parser.parse({"--aaa"}));
    EXPECT_TRUE(parser.parse({"--bbb"}));
    EXPECT_FALSE(parser.parse({"-aaa"}));
    EXPECT_FALSE(parser.parse({"-bbb"}));
    EXPECT_FALSE(parser.parse({"--ccc"}));
    EXPECT_FALSE(parser.parse({"-aaa", "-bbb"}));
}

TEST(test_commandline_parser, test_commandline_parser_mixed_options)
{
    common::commandline_parser parser;
    parser.add_option("aaa", "description 1");
    parser.add_option("bbb", "description 2");
    parser.add_option("a", "description 3");
    parser.add_option("b", "description 4");

    const auto result = parser.parse({"--aaa", "--bbb", "-a", "-b"});

    EXPECT_TRUE(result);
    EXPECT_TRUE(result.success());
    EXPECT_FALSE(result.failed());

    EXPECT_TRUE(result.has_option("aaa"));
    EXPECT_TRUE(result.has_option("bbb"));
    EXPECT_TRUE(result.has_option("a"));
    EXPECT_TRUE(result.has_option("b"));
    EXPECT_FALSE(result.has_option("ccc"));

    EXPECT_TRUE(parser.parse({"--aaa"}));
    EXPECT_TRUE(parser.parse({"--bbb"}));
    EXPECT_TRUE(parser.parse({"-a"}));
    EXPECT_TRUE(parser.parse({"-b"}));
    EXPECT_TRUE(parser.parse({"--aaa", "-a"}));
    EXPECT_TRUE(parser.parse({"--bbb", "-b"}));
    EXPECT_FALSE(parser.parse({"-aaa", "--a"}));
    EXPECT_FALSE(parser.parse({"-bbb", "--b"}));
    EXPECT_FALSE(parser.parse({"-aaa"}));
    EXPECT_FALSE(parser.parse({"-bbb"}));
    EXPECT_FALSE(parser.parse({"--a"}));
    EXPECT_FALSE(parser.parse({"--b"}));
}

TEST(test_commandline_parser, test_commandline_parser_short_args)
{
    common::commandline_parser parser;
    parser.add_argument("a", "description 1");
    parser.add_argument("b", "description 2");

    const auto result = parser.parse({"-a", "value_a", "-b", "value_b"});

    EXPECT_TRUE(result);
    EXPECT_TRUE(result.success());
    EXPECT_FALSE(result.failed());

    ASSERT_TRUE(result.has_argument("a"));
    EXPECT_EQ("value_a", result.get_argument("a"));
    ASSERT_TRUE(result.has_argument("b"));
    EXPECT_EQ("value_b", result.get_argument("b"));

    EXPECT_TRUE(parser.parse({"-a", "value_a"}));
    EXPECT_FALSE(parser.parse({"-a", "value_a", "-b"}));
    EXPECT_FALSE(parser.parse({"--a", "value_a"}));
}

TEST(test_commandline_parser, test_commandline_parser_long_args)
{
    common::commandline_parser parser;
    parser.add_argument("aaa", "description 1");
    parser.add_argument("bbb", "description 2");

    const auto result = parser.parse({"--aaa", "value_a", "--bbb", "value_b"});

    EXPECT_TRUE(result);
    EXPECT_TRUE(result.success());
    EXPECT_FALSE(result.failed());

    ASSERT_TRUE(result.has_argument("aaa"));
    EXPECT_EQ("value_a", result.get_argument("aaa"));
    ASSERT_TRUE(result.has_argument("bbb"));
    EXPECT_EQ("value_b", result.get_argument("bbb"));

    EXPECT_TRUE(parser.parse({"--aaa", "value_a"}));
    EXPECT_FALSE(parser.parse({"--aaa", "value_a", "--bbb"}));
    EXPECT_FALSE(parser.parse({"-aaa", "value_a"}));
}

TEST(test_commandline_parser, test_commandline_parser_all_mixed)
{
    common::commandline_parser parser;
    parser.add_positional("a", "description 1");
    parser.add_positional("bbb", "description 2");
    parser.add_option("c", "description 3");
    parser.add_option("ccc", "description 4");
    parser.add_argument("d", "description 5");
    parser.add_argument("ddd", "description 6");

    const auto result = parser.parse({"1", "2", "--ccc", "-c", "--ddd", "value_ddd", "-d", "value_d"});

    EXPECT_TRUE(result);
    EXPECT_TRUE(result.success());
    EXPECT_FALSE(result.failed());

    EXPECT_EQ(result.positional(0), "1");
    EXPECT_EQ(result.positional(1), "2");
    EXPECT_TRUE(result.has_option("c"));
    EXPECT_TRUE(result.has_option("ccc"));
    ASSERT_TRUE(result.has_argument("ddd"));
    EXPECT_EQ("value_ddd", result.get_argument("ddd"));
    ASSERT_TRUE(result.has_argument("d"));
    EXPECT_EQ("value_d", result.get_argument("d"));
}
