// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

namespace aeon::midi::messages
{

// Channel based messages. The second nibble is used for the midi channel.
static const unsigned char note_off = 0x80;
static const unsigned char note_on = 0x90;
static const unsigned char polyphonic_key_pressure = 0xA0;
static const unsigned char controller_change = 0xB0;
static const unsigned char program_change = 0xC0;
static const unsigned char channel_pressure = 0xD0;
static const unsigned char pitch_bend = 0xE0;

// Regular messages
static const unsigned char system_exclusive = 0xF0;
static const unsigned char time_code_quarter_frame = 0xF1;
static const unsigned char song_position_pointer = 0xF2;
static const unsigned char song_select = 0xF3;
static const unsigned char tune_request = 0xF6;
static const unsigned char end_of_exclusive = 0xF7;
static const unsigned char meta = 0xFF;

// Realtime messages
static const unsigned char timing_clock = 0xF8;
static const unsigned char start_sequence = 0xFA;
static const unsigned char continue_sequence = 0xFB;
static const unsigned char stop_sequence = 0xFC;
static const unsigned char active_sensing = 0xFE;
static const unsigned char reset = 0xFF;

} // namespace aeon::midi::messages
