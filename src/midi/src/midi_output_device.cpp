/*
 * Copyright (c) 2012-2018 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include <aeon/midi/midi_output_device.h>
#include <aeon/midi/midi_messages.h>
#include <cassert>

namespace aeon
{
namespace midi
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

} // namespace midi
} // namespace aeon
