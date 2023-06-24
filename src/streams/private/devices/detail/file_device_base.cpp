// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/streams/devices/detail/file_device_base.h>
#include <aeon/streams/exception.h>

namespace aeon::streams::internal
{

file_device_base::file_device_base(const std::filesystem::path &path, const std::ios::openmode mode, const file_mode fm,
                                   const common::flags<file_flag> flags)
    : iostream_device_base<std::fstream>{}
    , fstream_{}
{
    auto open_mode = mode;

    if (fm == file_mode::binary)
        open_mode |= std::fstream::binary;

    if (flags.is_set(file_flag::at_end))
        open_mode |= std::fstream::ate;

    if (flags.is_set(file_flag::append))
        open_mode |= std::fstream::app;

    if (flags.is_set(file_flag::truncate))
        open_mode |= std::fstream::trunc;

    fstream_.open(path, open_mode);

    if (!fstream_.good())
        throw stream_exception{};

    stream_ = &fstream_;
}

file_device_base::file_device_base(file_device_base &&other) noexcept
    : fstream_{std::move(other.fstream_)}
{
    stream_ = &fstream_;
}

auto file_device_base::operator=(file_device_base &&other) noexcept -> file_device_base &
{
    fstream_ = std::move(other.fstream_);
    stream_ = &fstream_;
    return *this;
}

[[nodiscard]] auto file_device_base::size() const -> std::streamoff
{
    const auto prev_g = stream_->tellg();
    stream_->seekg(0, std::ios::end);
    const auto size = stream_->tellg();
    stream_->seekg(prev_g);
    return size;
}

} // namespace aeon::streams::internal
