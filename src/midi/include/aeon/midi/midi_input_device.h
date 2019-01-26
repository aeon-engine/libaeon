// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/midi/midi_device.h>
#include <rtmidi/RtMidi.h>
#include <vector>

namespace aeon
{
namespace midi
{

struct midi_message_type
{
    static const int system_exclusive = 0x01;
    static const int time_code = 0x02;
    static const int sense = 0x04;
};

class midi_input_device : public midi_device
{
public:
    midi_input_device();
    virtual ~midi_input_device();

    void open(const unsigned int port);
    auto get_message(std::vector<unsigned char> &message) const -> double;

    void set_message_mask(const int mask);

    auto get_opened_port()
    {
        return port_;
    }

private:
    mutable RtMidiIn midi_input_device_;
    unsigned int port_;
};

} // namespace midi
} // namespace aeon
