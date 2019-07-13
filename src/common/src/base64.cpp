// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

// Based on an implementation by Megumi Tomita, https://gist.github.com/tomykaira/f0fd86b6c73063283afe550bc5d77594

#include <aeon/common/base64.h>
#include <aeon/common/bits.h>
#include <stdexcept>

namespace aeon::common::base64
{

namespace internal
{

// clang-format off
static constexpr char encode_lookup[] =
{
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
    'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
    'w', 'x', 'y', 'z', '0', '1', '2', '3',
    '4', '5', '6', '7', '8', '9', '+', '/'
};

static constexpr unsigned char decode_lookup[] =
{
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 62, 64, 64, 64, 63,
    52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 64, 64, 64, 64, 64, 64,
    64,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
    15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 64, 64, 64, 64, 64,
    64, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
    41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64
};
// clang-format on

auto decode_part(const std::string_view &str, unsigned int &i)
{
    return str[i] == '=' ? 0 & i++ : decode_lookup[static_cast<int>(str[i++])];
}

} // namespace internal

auto encode(const std::string_view &data) -> std::string
{
    return encode(reinterpret_cast<const std::uint8_t *>(std::data(data)),
                  static_cast<std::streamsize>(std::size(data)));
}

auto encode(const std::vector<std::uint8_t> &data) -> std::string
{
    return encode(std::data(data), static_cast<std::streamsize>(std::size(data)));
}

auto encode(const std::uint8_t *data, const std::streamsize size) -> std::string
{
    const auto output_length = 4 * ((size + 2) / 3);

    if (output_length == 0)
        return "";

    std::string result(output_length, '\0');

    auto p = std::data(result);

    auto i = 0u;
    for (; i < size - 2; i += 3)
    {
        *p++ = internal::encode_lookup[data[i] >> 2 & 0x3F];
        *p++ = internal::encode_lookup[(data[i] & 0x3) << 4 | static_cast<int>(data[i + 1] & 0xF0) >> 4];
        *p++ = internal::encode_lookup[(data[i + 1] & 0xF) << 2 | static_cast<int>(data[i + 2] & 0xC0) >> 6];
        *p++ = internal::encode_lookup[data[i + 2] & 0x3F];
    }

    if (i < size)
    {
        *p++ = internal::encode_lookup[data[i] >> 2 & 0x3F];
        if (i == (size - 1))
        {
            *p++ = internal::encode_lookup[((data[i] & 0x3) << 4)];
            *p++ = '=';
        }
        else
        {
            *p++ = internal::encode_lookup[(data[i] & 0x3) << 4 | static_cast<int>(data[i + 1] & 0xF0) >> 4];
            *p++ = internal::encode_lookup[((data[i + 1] & 0xF) << 2)];
        }
        *p++ = '=';
    }

    return result;
}

auto decode(const std::string_view &str) -> std::vector<std::uint8_t>
{
    if (std::empty(str))
        return {};

    const auto len = std::size(str);

    if (len % 4 != 0)
        throw std::invalid_argument{"Base64 requires multiple of 4."};

    auto output_length = len / 4 * 3;

    if (str[len - 1] == '=')
        --output_length;

    if (str[len - 2] == '=')
        --output_length;

    std::vector<std::uint8_t> result(output_length);

    for (auto i = 0u, j = 0u; i < len;)
    {
        const auto triple = (internal::decode_part(str, i) << 3 * 6) + (internal::decode_part(str, i) << 2 * 6) +
                            (internal::decode_part(str, i) << 1 * 6) + (internal::decode_part(str, i) << 0 * 6);

        if (j < output_length)
            result[j++] = bits::mask_u8(triple >> 2 * 8);

        if (j < output_length)
            result[j++] = bits::mask_u8(triple >> 1 * 8);

        if (j < output_length)
            result[j++] = bits::mask_u8(triple >> 0 * 8);
    }

    return result;
}

auto decode_string(const std::string_view &str) -> std::string
{
    const auto result = decode(str);
    return {std::begin(result), std::end(result)};
}

} // namespace aeon::common::base64
