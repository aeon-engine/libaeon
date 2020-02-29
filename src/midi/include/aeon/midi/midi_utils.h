// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <string>
#include <optional>

namespace aeon::midi::utils
{

/*!
 * Convert a midi note number to its name.
 * For example:
 * 20 -> "G-1"
 * 34 -> "Bb1"
 * 105 -> "A7"
 */
[[nodiscard]] auto note_name(const unsigned char note) -> std::string;

/*!
 * Convert a midi note number to its name.
 * For example:
 * "G-1" -> 20
 * "Bb1" -> 34
 * "A7" -> 105
 */
[[nodiscard]] auto note_name_to_midi(const std::string &note) -> std::optional<unsigned char>;

} // namespace aeon::midi::utils
