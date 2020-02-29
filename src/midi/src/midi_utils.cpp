// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#include <aeon/midi/midi_utils.h>
#include <aeon/common/string.h>
#include <array>
#include <stdexcept>

namespace aeon::midi::utils
{

namespace internal
{

static constexpr auto notes_per_octave = 12;
static const std::array<std::string, notes_per_octave> note_names = {"C",  "C#", "D",  "Eb", "E",  "F",
                                                                     "F#", "G",  "Ab", "A",  "Bb", "B"};

static const std::array<std::string, notes_per_octave> alt_note_names = {"C",  "Db", "D",  "D#", "E",  "F",
                                                                         "Gb", "G",  "G#", "A",  "A#", "B"};

static const std::array<std::string, notes_per_octave> octave_names = {"-1", "0", "1", "2", "3", "4",
                                                                       "5",  "6", "7", "8", "9"};

static constexpr auto c0_note = 12;

[[nodiscard]] auto find_note_name_index(const std::string &note, const std::array<std::string, 12> &note_list) -> int
{
    auto index = 0;
    auto best_match = -1;
    for (const auto &note_name : note_list)
    {
        if (common::string::begins_with(note, note_name))
        {
            if (std::size(internal::note_names[index]) == 2)
                return index;

            best_match = index;
        }

        ++index;
    }

    return best_match;
}

} // namespace internal

[[nodiscard]] auto note_name(const unsigned char note) -> std::string
{
    if (note > 127)
        throw std::out_of_range{"Midi notes must be 0-127."};

    const auto note_value = static_cast<int>(note);
    const auto note_name_offset = note_value % std::size(internal::note_names);
    const auto note_octave = (note_value) / static_cast<int>(std::size(internal::note_names));
    return internal::note_names[note_name_offset] + internal::octave_names[note_octave];
}

[[nodiscard]] auto note_name_to_midi(const std::string &note) -> std::optional<unsigned char>
{
    // First find the note index
    auto index = internal::find_note_name_index(note, internal::note_names);

    if (index == -1)
        index = internal::find_note_name_index(note, internal::alt_note_names);

    if (index == -1)
        return std::nullopt;

    const auto note_name_length = std::size(internal::note_names[index]);

    // If no octave number was specified, assume 0.
    if (std::size(note) == note_name_length)
        return static_cast<unsigned char>(internal::c0_note + index);

    const auto remaining = common::string::stripped_left(note, note_name_length);

    auto octave_index = 0;
    for (const auto &octave_name : internal::octave_names)
    {
        if (remaining == octave_name)
            return static_cast<unsigned char>((octave_index * internal::notes_per_octave) + index);

        ++octave_index;
    }

    return std::nullopt;
}

} // namespace aeon::midi::utils
