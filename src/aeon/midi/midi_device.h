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
