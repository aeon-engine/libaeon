// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/streams/stream.h>
#include <aeon/common/stdfilesystem.h>

#include <fstream>

namespace aeon::streams
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
    explicit file_stream(const std::string &filename, const common::flags<access_mode> mode,
                         const file_mode fm = file_mode::binary);

    explicit file_stream(const std::string &filename, const file_mode fm = file_mode::binary);

    explicit file_stream(const std::filesystem::path &path, const common::flags<access_mode> mode,
                         const file_mode fm = file_mode::binary);

    explicit file_stream(const std::filesystem::path &path, const file_mode fm = file_mode::binary);

    file_stream(file_stream &&) = default;
    auto operator=(file_stream &&) -> file_stream & = default;

    file_stream(const file_stream &) = delete;
    auto operator=(const file_stream &) -> file_stream & = delete;

    virtual ~file_stream() = default;

    auto read(std::uint8_t *data, std::size_t size) -> std::size_t override;

    auto write(const std::uint8_t *data, std::size_t size) -> std::size_t override;

    auto peek(std::uint8_t *data, std::size_t size) -> std::size_t override;

    auto seek(std::ptrdiff_t pos, seek_direction direction) -> bool override;

    auto seekw(std::ptrdiff_t pos, seek_direction direction) -> bool override;

    auto tell() -> std::size_t override;

    auto tellw() -> std::size_t override;

    auto eof() const -> bool override;

    auto size() const -> std::size_t override;

    void flush() override;

    auto good() const -> bool override;

    auto read_line() -> std::string;

    void write(const std::string &str);

    void write_line();

    void write_line(const std::string &line);

    auto get_filename() const -> const std::string &;

protected:
    auto to_ios_open_mode_(const common::flags<access_mode> mode, const file_mode fm) const -> std::ios::openmode;
    auto seek_direction_to_ios_seekdir_(seek_direction direction) const -> std::ios::seekdir;

    std::fstream fstream_;
    std::size_t size_;
    std::string filename_;
};

} // namespace aeon::streams
