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

midi_input_device::midi_input_device()
    : midi_device(midi_input_device_)
    , midi_input_device_()
    , port_(0)
{
}

midi_input_device::~midi_input_device() = default;

void midi_input_device::open(const unsigned int port)
{
    port_ = port;
    midi_input_device_.openPort(port);
}

auto midi_input_device::get_message(std::vector<unsigned char> &message) -> double
{
    return midi_input_device_.getMessage(&message);
}

void midi_input_device::set_message_mask(const int mask)
{
    midi_input_device_.ignoreTypes(utility::check_bit_flag(mask, midi_message_type::system_exclusive),
                                   utility::check_bit_flag(mask, midi_message_type::time_code),
                                   utility::check_bit_flag(mask, midi_message_type::sense));
}

} // namespace midi
} // namespace aeon
