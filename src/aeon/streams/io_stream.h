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
namespace streams
{

class io_stream_exception : public stream_exception
{
};

class io_stream : public stream, public io_stream_colors_mixin
{
public:
    explicit io_stream(int mode = aeon::streams::access_mode::write);

    std::size_t read(std::uint8_t *data, std::size_t size) override;

    std::size_t write(const std::uint8_t *data, std::size_t size) override;

    bool peek(std::uint8_t &data, std::ptrdiff_t offset = 0) override;

    bool seek(std::ptrdiff_t pos, seek_direction direction) override;

    bool seekw(std::ptrdiff_t pos, seek_direction direction) override;

    std::size_t tell() override;

    std::size_t tellw() override;

    bool eof() const override;

    std::size_t size() const override;

    void flush() override;

    bool good() const override;
};

typedef std::shared_ptr<io_stream> io_stream_ptr;

} // namespace streams
} // namespace aeon
