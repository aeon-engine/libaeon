// Copyright (c) 2012-2019 Robin Degen

#include <aeon/midi/midi_device.h>
#include <rtmidi/RtMidi.h>

namespace aeon::midi
{

[[nodiscard]] auto midi_device::get_port_count() const -> unsigned
{
    return midi_device_.getPortCount();
}

[[nodiscard]] auto midi_device::get_port_name(const unsigned int index) const -> std::string
{
    return midi_device_.getPortName(index);
}

[[nodiscard]] auto midi_device::get_ports() const -> std::vector<std::string>
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

} // namespace aeon::midi
