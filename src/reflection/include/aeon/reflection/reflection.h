// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include <aeon/reflection/reflection_info.h>

/*!
 * I'll remember the good things how can you forget all the years that we shared in our way
 * Things were changing my life, taking your place in my life and our time drifting away.
 *
 * - On Reflection, Gentle Giant (1975)
 */
namespace aeon::reflection
{
} // namespace aeon::reflection

// clang-format off
#define AEON_REFLECTION_BEGIN(classname)                                                                               \
    class reflection_info_impl final : public aeon::reflection::reflection_info                                        \
    {                                                                                                                  \
    public:                                                                                                            \
        reflection_info_impl() noexcept = default;                                                                     \
        ~reflection_info_impl() override = default;                                                                    \
                                                                                                                       \
        reflection_info_impl(const reflection_info_impl &) noexcept = default;                                         \
        auto operator=(const reflection_info_impl &) noexcept -> reflection_info_impl & = default;                     \
                                                                                                                       \
        reflection_info_impl(reflection_info_impl &&) noexcept = default;                                              \
        auto operator=(reflection_info_impl &&) noexcept -> reflection_info_impl & = default;                          \
                                                                                                                       \
    private:                                                                                                           \
        [[nodiscard]] auto get_field_info() const noexcept                                                             \
            -> const std::vector<aeon::reflection::field_info> & override                                              \
        {                                                                                                              \
            using reflection_class_type = classname;                                                                   \
                                                                                                                       \
            static std::vector<aeon::reflection::field_info> info = {

#define AEON_REFLECTION_FIELD(type, name)                                                                              \
    {(#name), (#type),                                                                                                 \
     reinterpret_cast<std::ptrdiff_t>(                                                                                 \
         &reinterpret_cast<std::uint8_t const &>((static_cast<reflection_class_type *>(nullptr)->name)))},

#define AEON_REFLECTION_END()                                                                                          \
        };                                                                                                             \
                                                                                                                       \
        return info;                                                                                                   \
    }                                                                                                                  \
};                                                                                                                     \
                                                                                                                       \
public:                                                                                                                \
    [[nodiscard]] static auto reflection_info() noexcept->const aeon::reflection::reflection_info &                    \
    {                                                                                                                  \
        static reflection_info_impl info;                                                                              \
        return info;                                                                                                   \
    }                                                                                                                  \
                                                                                                                       \
private:
// clang-format on
