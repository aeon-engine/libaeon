// Copyright (c) 2012-2019 Robin Degen

#include <gtest/gtest.h>
#include <aeon/sockets/http/url_encoding.h>
#include <aeon/sockets/http/validators.h>
#include <random>

using namespace aeon;

TEST(test_url_encoding, encode_regular_string)
{
    const std::string test_str = "ThisIsATestString123";
    ASSERT_EQ(test_str, sockets::http::url_encode(test_str));
}

TEST(test_url_encoding, encode_spaces)
{
    const std::string test_str = "This Is A Test String 123";
    const std::string expected_str = "This%20Is%20A%20Test%20String%20123";
    ASSERT_EQ(expected_str, sockets::http::url_encode(test_str));
}

static auto generate_random_string(const int length) -> std::string
{
    std::string str;
    str.reserve(length);

    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<unsigned long> uniform_dist;

    int offset = 0;
    auto random_value = uniform_dist(e1);

    for (auto i = 0; i < length; ++i)
    {
        if (offset == sizeof(unsigned long))
        {
            random_value = uniform_dist(e1);
            i = 0;
        }

        str += static_cast<char>((random_value >> (i * 8)) & 0xFF);
        ++offset;
    }

    return str;
}

TEST(test_url_encoding, encode_decode_random)
{
    for (auto i = 0; i < 100; ++i)
    {
        for (auto j = 5; j < 20; ++j)
        {
            const auto str = generate_random_string(j);
            const auto str_encoded = sockets::http::url_encode(str);

            ASSERT_TRUE(sockets::http::detail::validate_uri(str_encoded));

            const auto str_decoded = sockets::http::url_decode(str_encoded);
            ASSERT_EQ(str, str_decoded);
        }
    }
}
