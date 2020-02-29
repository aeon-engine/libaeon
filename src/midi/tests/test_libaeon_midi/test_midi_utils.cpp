// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#include <aeon/midi/midi_utils.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace aeon;

TEST(test_midi_utils, test_note_names)
{
    EXPECT_EQ("C-1", midi::utils::note_name(0));
    EXPECT_EQ("C0", midi::utils::note_name(12));
    EXPECT_EQ("C4", midi::utils::note_name(60));
    EXPECT_EQ("Ab4", midi::utils::note_name(68));
    EXPECT_EQ("E7", midi::utils::note_name(100));
    EXPECT_EQ("G9", midi::utils::note_name(127));
    EXPECT_THROW([[maybe_unused]] auto result = midi::utils::note_name(128), std::out_of_range);
}

TEST(test_midi_utils, test_note_name_to_midi_note)
{
    for (unsigned char note = 0; note <= 127; ++note)
    {
        EXPECT_EQ(midi::utils::note_name_to_midi(midi::utils::note_name(note)), note);
    }
}

TEST(test_midi_utils, test_note_name_to_midi_note_default_zero_octave)
{
    EXPECT_EQ(12, midi::utils::note_name_to_midi("C"));
    EXPECT_EQ(21, midi::utils::note_name_to_midi("A"));
}

TEST(test_midi_utils, test_note_name_to_midi_note_invalid_notes)
{
    EXPECT_EQ(std::nullopt, midi::utils::note_name_to_midi("H"));
    EXPECT_EQ(std::nullopt, midi::utils::note_name_to_midi("A10"));
    EXPECT_EQ(std::nullopt, midi::utils::note_name_to_midi("A-2"));
    EXPECT_EQ(std::nullopt, midi::utils::note_name_to_midi("Abb"));
    EXPECT_EQ(std::nullopt, midi::utils::note_name_to_midi("CC"));
}
