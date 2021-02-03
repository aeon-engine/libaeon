// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/streams/devices/detail/iostream_device_base.h>
#include <aeon/common/flags.h>
#include <filesystem>
#include <cstdint>
#include <fstream>

namespace aeon::streams
{

enum class file_mode
{
    text,
    binary
};

enum class file_flag : std::uint32_t
{
    none = 0x00,
    at_end = 0x01,
    append = 0x02,
    truncate = 0x04
};

aeon_declare_flag_operators(file_flag);

namespace internal
{

class file_device_base : public iostream_device_base<std::fstream>
{
public:
    file_device_base(const file_device_base &) noexcept = delete;
    auto operator=(const file_device_base &) noexcept -> file_device_base & = delete;

protected:
    explicit file_device_base(const std::filesystem::path &path, const std::ios::openmode mode, const file_mode fm,
                              const common::flags<file_flag> flags);

    ~file_device_base() = default;

    file_device_base(file_device_base &&other) noexcept;
    auto operator=(file_device_base &&other) noexcept -> file_device_base &;

    [[nodiscard]] auto size() const -> std::streamoff;

private:
    std::fstream fstream_;
};

} // namespace internal
} // namespace aeon::streams
