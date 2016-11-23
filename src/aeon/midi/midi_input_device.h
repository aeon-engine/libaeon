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
