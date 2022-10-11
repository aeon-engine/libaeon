// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/common/version.h>
#include <aeon/common/string.h>

struct VkLayerProperties;

namespace aeon::vulkan
{

class layer final
{
public:
    explicit layer(common::string name, const common::version3<uint32_t> &spec_version,
                   const common::version3<uint32_t> &implementation_version, common::string description);
    explicit layer(const VkLayerProperties &extension_properties);
    ~layer() = default;

    layer(const layer &) = default;
    auto operator=(const layer &) -> layer & = default;

    layer(layer &&) noexcept = default;
    auto operator=(layer &&) noexcept -> layer & = default;

    [[nodiscard]] auto name() const noexcept -> const common::string &;
    [[nodiscard]] auto spec_version() const noexcept -> const common::version3<uint32_t> &;
    [[nodiscard]] auto implementation_version() const noexcept -> const common::version3<uint32_t> &;
    [[nodiscard]] auto description() const noexcept -> const common::string &;

    auto operator==(const layer &other) const noexcept -> bool;
    auto operator!=(const layer &other) const noexcept -> bool;

private:
    common::string name_;
    common::version3<uint32_t> spec_version_;
    common::version3<uint32_t> implementation_version_;
    common::string description_;
};

template <typename device_t>
inline auto operator<<(std::ostream &stream, const layer &val)
{
    stream << val.name() << " (Spec: " << val.spec_version() << ", Impl: " << val.implementation_version() << ")\n";
    return stream;
}

} // namespace aeon::vulkan
