// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/midi/midi_device.h>

#include <RtMidi.h>

#include <string>
#include <vector>

namespace aeon::midi
{

class midi_output_device : public midi_device
{
public:
    midi_output_device();
    virtual ~midi_output_device();

    void open(const unsigned int port);
    void open_virtual(const std::string &name);

    void send_message(std::vector<unsigned char> &message);

    void send_note_off(unsigned char channel, unsigned char note, unsigned char velocity);

    void send_note_on(unsigned char channel, unsigned char note, unsigned char velocity);

private:
    void __send_note_message(unsigned char message, unsigned char note, unsigned char velocity);

    RtMidiOut midi_output_device_;
    std::vector<unsigned char> note_output_buffer_;
};

} // namespace aeon::midi
