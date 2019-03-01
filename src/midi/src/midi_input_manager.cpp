// Copyright (c) 2012-2019 Robin Degen

#include <aeon/midi/midi_input_manager.h>
#include <aeon/midi/midi_input_device.h>
#include <aeon/midi/midi_messages.h>
#include <algorithm>

namespace aeon::midi
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
    const auto time_code = input_device_.get_message(receive_buffer_);

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
    const auto message = data[0];
    if ((message & 0xF0) == messages::note_on)
    {
        const auto note_info = midi_note_parser(data);
        notes_[note_info.channel].emplace_back(note_info);
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

} // namespace aeon::midi
