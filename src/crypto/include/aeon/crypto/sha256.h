// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include <string_view>
#include <array>
#include <cstdint>

namespace aeon::crypto
{

class sha256 final
{
public:
    static constexpr auto block_size = (512 / 8);

    sha256() noexcept;
    ~sha256() = default;

    sha256(const sha256 &) noexcept = delete;
    auto operator=(const sha256 &) noexcept -> sha256 & = delete;

    sha256(sha256 &&) noexcept = default;
    auto operator=(sha256 &&) noexcept -> sha256 & = default;

    void write(const char *data, const std::streamsize size) noexcept;
    void write(const std::string_view str) noexcept;

    [[nodiscard]] auto finalize() noexcept -> std::array<std::uint8_t, 32>;
    void reset() noexcept;

private:
    void transform(const unsigned char *message, const std::streamsize size) noexcept;

    std::array<std::uint32_t, 8> hash_;
    std::array<unsigned char, 2 * block_size> block_;
    std::streamsize size_;
    std::streamsize total_size_;
};

} // namespace aeon::crypto
