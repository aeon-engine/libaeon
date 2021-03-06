// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/midi/midi_output_device.h>
#include <aeon/midi/midi_messages.h>
#include <cassert>

namespace aeon::midi
{

static const int note_output_buffer_size = 3;

midi_output_device::midi_output_device()
    : midi_device(midi_output_device_)
    , midi_output_device_()
    , note_output_buffer_(note_output_buffer_size, 0)
{
}

midi_output_device::~midi_output_device()
{
    if (midi_output_device_.isPortOpen())
        midi_output_device_.closePort();
}

void midi_output_device::open(const unsigned int port)
{
    midi_output_device_.openPort(port);
}

void midi_output_device::open_virtual(const std::string &name)
{
    midi_output_device_.openVirtualPort(name);
}

void midi_output_device::send_message(std::vector<unsigned char> &message)
{
    midi_output_device_.sendMessage(&message);
}

void midi_output_device::send_note_off(unsigned char channel, unsigned char note, unsigned char velocity)
{
    assert(channel <= 15);
    __send_note_message(messages::note_off + channel, note, velocity);
}

void midi_output_device::send_note_on(unsigned char channel, unsigned char note, unsigned char velocity)
{
    assert(channel <= 15);
    __send_note_message(messages::note_on + channel, note, velocity);
}

void midi_output_device::__send_note_message(unsigned char message, unsigned char note, unsigned char velocity)
{
    assert(note <= 127);
    assert(velocity <= 127);

    const auto data = note_output_buffer_.data();
    data[0] = message;
    data[1] = note;
    data[2] = velocity;
    midi_output_device_.sendMessage(&note_output_buffer_);
}

} // namespace aeon::midi
