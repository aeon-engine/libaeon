// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include <vector>
#include <string>

class RtMidi;

namespace aeon::midi
{

class midi_device
{
public:
    [[nodiscard]] auto get_port_count() const -> unsigned int;

    [[nodiscard]] auto get_port_name(const unsigned int index) const -> std::string;

    [[nodiscard]] auto get_ports() const -> std::vector<std::string>;

protected:
    explicit midi_device(RtMidi &midi_device);
    virtual ~midi_device();

private:
    RtMidi &midi_device_;
};

} // namespace aeon::midi
