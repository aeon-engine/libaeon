/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2017 Robin Degen
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

class file_stream_exception : public stream_exception
{
};

enum class file_mode
{
    text,
    binary
};

class file_stream : public stream
{
public:
    explicit file_stream(const std::string &filename, int mode, file_mode fm = file_mode::binary);

    explicit file_stream(const std::string &filename, file_mode fm = file_mode::binary);

    file_stream(file_stream &&o) = default;

    file_stream &operator=(file_stream &&other) = default;

    virtual ~file_stream() = default;

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

    std::string read_line();

    void write_line(const std::string &line);

    const std::string &get_filename() const;

protected:
    std::ios::openmode to_ios_open_mode_(int mode, file_mode fm) const;
    std::ios::seekdir seek_direction_to_ios_seekdir_(seek_direction direction) const;

    std::fstream fstream_;
    std::size_t size_;
    std::string filename_;
};

typedef std::shared_ptr<file_stream> file_stream_ptr;

} // namespace streams
} // namespace aeon
