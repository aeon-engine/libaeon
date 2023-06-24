// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/common/string.h>
#include <aeon/common/string_view.h>
#include <vector>
#include <cstdint>

namespace aeon::common::base64
{

[[nodiscard]] auto encode(const string_view &data) -> string;
[[nodiscard]] auto encode(const std::vector<std::uint8_t> &data) -> string;
[[nodiscard]] auto encode(const std::uint8_t *data, const std::streamsize size) -> string;

[[nodiscard]] auto decode(const string_view &str) -> std::vector<std::uint8_t>;
[[nodiscard]] auto decode_string(const string_view &str) -> string;

} // namespace aeon::common::base64
