/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2016 Robin Degen
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains the property of
 * Robin Degen and its suppliers, if any. The intellectual and technical
 * concepts contained herein are proprietary to Robin Degen and its suppliers
 * and may be covered by U.S. and Foreign Patents, patents in process, and are
 * protected by trade secret or copyright law. Dissemination of this
 * information or reproduction of this material is strictly forbidden unless
 * prior written permission is obtained from Robin Degen.
 */

#include <aeon/midi.h>
#include <algorithm>

namespace aeon
{
namespace midi
{

static const int receive_buffer_reserve_size = 16;
static const int notes_pressed_reserve_size = 16;

midi_input_manager::midi_input_manager(midi_input_device &device)
    : input_device_(device)
    , receive_buffer_()
    , notes_()
{
    receive_buffer_.reserve(receive_buffer_reserve_size);

    for (auto &n : notes_)
        n.reserve(notes_pressed_reserve_size);
}

midi_input_manager::~midi_input_manager() = default;

void midi_input_manager::run_one()
{
    auto time_code = input_device_.get_message(receive_buffer_);

    if (receive_buffer_.empty())
        return;

    __parse_note_data(receive_buffer_);

    for (auto listener : listeners_)
    {
        listener->on_midi_input(*this, receive_buffer_, time_code);
    }
}

void midi_input_manager::__parse_note_data(const std::vector<unsigned char> &data)
{
    auto message = data[0];
    if ((message & 0xF0) == messages::note_on)
    {
        auto note_info = midi_note_parser(data);
        notes_[note_info.channel].push_back(midi_note(note_info));
    }
    else if ((message & 0xF0) == messages::note_off)
    {
        auto note_info = midi_note_parser(data);
        auto &note_vector = notes_[note_info.channel];

        note_vector.erase(std::remove_if(note_vector.begin(), note_vector.end(),
                                         [&note_info](const midi_note &note) { return note.note == note_info.note; }),
                          note_vector.end());
    }
}

} // namespace midi
} // namespace aeon
