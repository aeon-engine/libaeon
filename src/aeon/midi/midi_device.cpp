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

auto midi_device::get_port_count() const -> unsigned
{
    return midi_device_.getPortCount();
}

auto midi_device::get_port_name(const unsigned int index) const -> std::string
{
    return midi_device_.getPortName(index);
}

auto midi_device::get_ports() const -> std::vector<std::string>
{
    auto port_count = get_port_count();
    auto ports = std::vector<std::string>(port_count);

    for (auto i = 0ul; i < port_count; ++i)
    {
        ports[i] = get_port_name(i);
    }

    return ports;
}

midi_device::midi_device(RtMidi &midi_device)
    : midi_device_(midi_device)
{
}

midi_device::~midi_device() = default;

} // namespace midi
} // namespace aeon
