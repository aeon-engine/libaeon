// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/common/string.h>
#include <string>
#include <string_view>

namespace aeon::common::utf8
{

class utf8_exception : public std::exception
{
};

inline auto bom() -> std::string;

template <typename iterator_t>
inline auto has_bom(const iterator_t itr, const iterator_t end);

inline auto has_bom(const std::string &str);

template <typename iterator_t>
inline auto skip_bom(const iterator_t itr, const iterator_t end);

inline auto strip_bom(std::string &str);

template <typename iterator_t>
inline auto codepoint_length(const iterator_t itr) noexcept;

template <typename iterator_t>
inline void advance_to_next_codepoint(iterator_t &itr, const iterator_t end) noexcept;

template <typename iterator_t>
inline auto read_codepoint(const iterator_t itr, const iterator_t end, char32_t &value);

template <typename iterator_t>
inline auto utf8_strlen(const iterator_t itr, const iterator_t end) -> std::size_t;

inline auto utf8_strlen(const std::string &str) -> std::size_t;

inline auto utf8_strlensv(const std::string_view &str) -> std::size_t;

template <typename iterator_t>
inline auto utf8_append(iterator_t itr, const char32_t c) -> iterator_t;

inline void utf8_append(std::string &str, const char32_t c);

} // namespace aeon::common::utf8

#include <aeon/common/impl/utf8_utils_impl.h>
