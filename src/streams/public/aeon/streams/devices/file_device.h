// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/streams/devices/detail/file_device_base.h>
#include <aeon/streams/tags.h>

namespace aeon::streams
{

class file_source_device : private internal::file_device_base
{
public:
    struct category : input, input_seekable, flushable, has_size, has_status, has_eof
    {
    };

    explicit file_source_device(const std::filesystem::path &path, const file_mode fm = file_mode::binary)
        : internal::file_device_base{path, std::fstream::in, fm, file_flag::none}
    {
    }

    ~file_source_device() = default;

    file_source_device(file_source_device &&) = default;
    auto operator=(file_source_device &&) -> file_source_device & = default;

    file_source_device(const file_source_device &) noexcept = delete;
    auto operator=(const file_source_device &) noexcept -> file_source_device & = delete;

    using file_device_base::eof;
    using file_device_base::fail;
    using file_device_base::file_device_base;
    using file_device_base::flush;
    using file_device_base::good;
    using file_device_base::read;
    using file_device_base::seekg;
    using file_device_base::size;
    using file_device_base::tellg;
};

class file_sink_device : private internal::file_device_base
{
public:
    struct category : output, output_seekable, flushable, has_status
    {
    };

    explicit file_sink_device(const std::filesystem::path &path, const file_mode fm = file_mode::binary)
        : internal::file_device_base{path, std::fstream::out, fm, file_flag::none}
    {
    }

    explicit file_sink_device(const std::filesystem::path &path, const file_mode fm,
                              const common::flags<file_flag> flags)
        : internal::file_device_base{path, std::fstream::out, fm, flags}
    {
    }

    ~file_sink_device() = default;

    file_sink_device(file_sink_device &&) = default;
    auto operator=(file_sink_device &&) -> file_sink_device & = default;

    file_sink_device(const file_sink_device &) noexcept = delete;
    auto operator=(const file_sink_device &) noexcept -> file_sink_device & = delete;

    using file_device_base::eof;
    using file_device_base::fail;
    using file_device_base::flush;
    using file_device_base::good;
    using file_device_base::seekp;
    using file_device_base::tellp;
    using file_device_base::write;
};

class file_device : private internal::file_device_base
{
public:
    struct category : input, input_seekable, output, output_seekable, flushable, has_size, has_status, has_eof
    {
    };

    explicit file_device(const std::filesystem::path &path, const file_mode fm = file_mode::binary)
        : internal::file_device_base{path, static_cast<std::ios::openmode>(0), fm, file_flag::none}
    {
    }

    explicit file_device(const std::filesystem::path &path, const file_mode fm, const common::flags<file_flag> flags)
        : internal::file_device_base{path, static_cast<std::ios::openmode>(0), fm, flags}
    {
    }

    ~file_device() = default;

    file_device(file_device &&) = default;
    auto operator=(file_device &&) -> file_device & = default;

    file_device(const file_device &) noexcept = delete;
    auto operator=(const file_device &) noexcept -> file_device & = delete;

    using file_device_base::eof;
    using file_device_base::fail;
    using file_device_base::flush;
    using file_device_base::good;
    using file_device_base::read;
    using file_device_base::seekg;
    using file_device_base::seekp;
    using file_device_base::size;
    using file_device_base::tellg;
    using file_device_base::tellp;
    using file_device_base::write;
};

} // namespace aeon::streams
