// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <cstdint>

namespace aeon::common::base64
{

[[nodiscard]] auto encode(const std::string_view &data) -> std::string;
[[nodiscard]] auto encode(const std::vector<std::uint8_t> &data) -> std::string;
[[nodiscard]] auto encode(const std::uint8_t *data, const std::streamsize size) -> std::string;

[[nodiscard]] auto decode(const std::string_view &str) -> std::vector<std::uint8_t>;
[[nodiscard]] auto decode_string(const std::string_view &str) -> std::string;

} // namespace aeon::common::base64
