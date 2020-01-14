// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <aeon/common/bits.h>
#include <aeon/common/listener_subject.h>

#include <vector>
#include <array>
#include <cassert>

namespace aeon::midi
{

class midi_input_device;

static const int max_midi_channels = 16;

struct midi_note_parser
{
    explicit midi_note_parser(const std::vector<unsigned char> &buffer)
        : message(buffer[0])
        , channel(common::bits::low_nibble(message))
        , note(buffer[1])
        , velocity(buffer[2])
    {
    }

    unsigned char message;
    unsigned char channel;
    unsigned char note;
    unsigned char velocity;
};

struct midi_note
{
    explicit midi_note(const midi_note_parser &parser)
        : note(parser.note)
        , velocity(parser.velocity)
    {
    }

    explicit midi_note(const unsigned char note, const unsigned char velocity)
        : note(note)
        , velocity(velocity)
    {
    }

    unsigned char note;
    unsigned char velocity;
};

class midi_input_manager;

class midi_input_listener
{
public:
    midi_input_listener() = default;
    virtual ~midi_input_listener() = default;

    virtual void on_midi_input(midi_input_manager &manager, const std::vector<unsigned char> &data,
                               const double time_code) = 0;
};

class midi_input_manager : public common::listener_subject<midi_input_listener>
{
public:
    explicit midi_input_manager(midi_input_device &device);
    ~midi_input_manager();

    void run_one();

    [[nodiscard]] auto &get_input_device()
    {
        return input_device_;
    }

    [[nodiscard]] const auto &get_pressed_notes(const unsigned int channel) const
    {
        assert(channel < max_midi_channels);
        return notes_[channel];
    }

private:
    void __parse_note_data(const std::vector<unsigned char> &data);

    midi_input_device &input_device_;
    std::vector<unsigned char> receive_buffer_;

    std::array<std::vector<midi_note>, max_midi_channels> notes_;
};

} // namespace aeon::midi
