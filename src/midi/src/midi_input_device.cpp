// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#include <aeon/midi/midi_input_device.h>
#include <aeon/common/bitflags.h>

namespace aeon::midi
{

midi_input_device::midi_input_device()
    : midi_device(midi_input_device_)
    , midi_input_device_()
    , port_(0)
{
}

midi_input_device::~midi_input_device()
{
    if (midi_input_device_.isPortOpen())
        midi_input_device_.closePort();
}

void midi_input_device::open(const unsigned int port)
{
    port_ = port;
    midi_input_device_.openPort(port);
}

[[nodiscard]] auto midi_input_device::get_message(std::vector<unsigned char> &message) const -> double
{
    return midi_input_device_.getMessage(&message);
}

void midi_input_device::set_message_mask(const int mask)
{
    midi_input_device_.ignoreTypes(common::check_bit_flag(mask, midi_message_type::system_exclusive),
                                   common::check_bit_flag(mask, midi_message_type::time_code),
                                   common::check_bit_flag(mask, midi_message_type::sense));
}

} // namespace aeon::midi
