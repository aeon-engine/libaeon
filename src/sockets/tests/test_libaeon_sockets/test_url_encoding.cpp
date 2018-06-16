/*
 * Copyright (c) 2012-2018 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

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
