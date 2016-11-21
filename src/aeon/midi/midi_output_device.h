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

#pragma once

namespace aeon
{
namespace midi
{

class midi_output_device : public midi_device
{
public:
    midi_output_device();
    virtual ~midi_output_device();

    void open(const unsigned int port);
    void open_virtual(const std::string &name);

    void send_message(std::vector<unsigned char> &message);

    void send_note_off(unsigned char channel, unsigned char note, unsigned char velocity)
    {
        assert(channel <= 15);
        send_note_message(messages::note_off + channel, note, velocity);
    }

    void send_note_on(unsigned char channel, unsigned char note, unsigned char velocity)
    {
        assert(channel <= 15);
        send_note_message(messages::note_on + channel, note, velocity);
    }

private:
    void send_note_message(unsigned char message, unsigned char note, unsigned char velocity)
    {
        assert(note <= 127);
        assert(velocity <= 127);

        auto data = note_output_buffer_.data();
        data[0] = message;
        data[1] = note;
        data[2] = velocity;
        midi_output_device_.sendMessage(&note_output_buffer_);
    }

    RtMidiOut midi_output_device_;
    std::vector<unsigned char> note_output_buffer_;
};

} // namespace midi
} // namespace aeon
