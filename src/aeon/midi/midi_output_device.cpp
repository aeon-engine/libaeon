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

} // namespace midi
} // namespace aeon
