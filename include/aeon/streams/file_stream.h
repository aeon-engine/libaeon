/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2015 Robin Degen
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

class file_stream_exception : public stream_exception {};

enum class file_mode
{
    text,
    binary
};

class file_stream : public stream
{
public:
    file_stream(const std::string &filename, int mode, file_mode fm = file_mode::binary);

    file_stream(const std::string &filename, file_mode fm = file_mode::binary);

    explicit file_stream(boost::filesystem::path path, int mode, file_mode fm /*= file_mode::binary*/);
    explicit file_stream(boost::filesystem::path path, file_mode fm /*= file_mode::binary*/);

    virtual std::size_t read(std::uint8_t *data, std::size_t size);

    virtual std::size_t write(const std::uint8_t *data,
        std::size_t size);

    virtual bool peek(std::uint8_t &data, std::ptrdiff_t offset = 0);

    virtual bool seek(std::ptrdiff_t pos, seek_direction direction);

    virtual bool seekw(std::ptrdiff_t pos, seek_direction direction);

    virtual std::size_t tell();

    virtual std::size_t tellw();

    virtual bool eof() const;

    virtual std::size_t size() const;

    virtual void flush();

    virtual bool good() const;

    bool read_line(std::string &line);

    void write_line(const std::string &line);

protected:
    std::ios::openmode to_ios_open_mode_(int mode, file_mode fm);
    std::ios::seekdir seek_direction_to_ios_seekdir_(seek_direction direction);

    std::fstream fstream_;
    std::size_t size_;
};

typedef std::shared_ptr<file_stream> file_stream_ptr;

} // namespace streams
} // namespace aeon
