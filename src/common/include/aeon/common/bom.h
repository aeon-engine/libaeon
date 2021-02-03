// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <string>
#include <array>

namespace aeon::common::bom
{

namespace utf8
{

/*!
 * The signature of a UTF-8 byte order marker.
 */
static constexpr std::array<const char8_t, 3> signature{0xef, 0xbb, 0xbf};

/*!
 * Generate a UTF-8 byte order marker as u8string.
 */
inline auto u8string()
{
    return std::u8string{std::begin(signature), std::end(signature)};
}

/*!
 * Generate a UTF-8 byte order marker as regular string.
 */
inline auto string()
{
    return std::string{std::begin(signature), std::end(signature)};
}

} // namespace utf8

namespace utf16
{

/*!
 * The signature of a UTF-16 byte order marker.
 */
static constexpr char16_t signature = 0xfeff;

/*!
 * The signature of a UTF-16 byte order marker in big endian.
 */
static constexpr char16_t big_endian_signature = 0xfeff;

} // namespace utf16

} // namespace aeon::common::bom
