// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/ptree/ptree.h>
#include <aeon/streams/idynamic_stream.h>
#include <aeon/streams/devices/memory_view_device.h>
#include <aeon/common/uuid.h>
#include <aeon/common/flags.h>
#include <filesystem>
#include <vector>
#include <string>
#include <cstdint>

namespace aeon::file_container
{

enum class read_items : std::uint32_t
{
    header = 0x00,
    metadata = 0x01,
    data = 0x02,
    all = 0xff
};

aeon_declare_flag_operators(read_items);

class container final
{
public:
    explicit container(streams::idynamic_stream &stream, const common::flags<read_items> items = read_items::all);
    explicit container(std::string name) noexcept;
    explicit container(std::string name, common::uuid id) noexcept;
    ~container();

    container(container &&) = delete;
    container &operator=(container &&) = delete;

    container(const container &) = delete;
    auto operator=(const container &) -> container & = delete;

    void name(std::string name) noexcept;
    [[nodiscard]] auto name() const noexcept -> const std::string &;

    void id(common::uuid id) noexcept;
    [[nodiscard]] auto id() const noexcept -> const common::uuid &;

    [[nodiscard]] auto stream() noexcept -> streams::memory_view_device<std::vector<std::uint8_t>>;
    [[nodiscard]] auto stream() const noexcept -> streams::memory_view_device<std::vector<std::uint8_t>>;

    [[nodiscard]] auto metadata() noexcept -> ptree::property_tree &;
    [[nodiscard]] auto metadata() const noexcept -> const ptree::property_tree &;

    void write(streams::idynamic_stream &stream) const;

private:
    std::string name_;
    common::uuid id_;
    std::vector<std::uint8_t> data_;
    ptree::property_tree metadata_;
};

} // namespace aeon::file_container
