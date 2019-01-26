// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <vector>
#include <string>

class RtMidi;

namespace aeon
{
namespace midi
{

class midi_device
{
public:
    auto get_port_count() const -> unsigned int;

    auto get_port_name(const unsigned int index) const -> std::string;

    auto get_ports() const -> std::vector<std::string>;

protected:
    explicit midi_device(RtMidi &midi_device);
    virtual ~midi_device();

private:
    RtMidi &midi_device_;
};

} // namespace midi
} // namespace aeon
