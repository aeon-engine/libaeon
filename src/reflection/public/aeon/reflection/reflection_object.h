// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

/*!
 * I'll remember the good things how can you forget all the years that we shared in our way
 * Things were changing my life, taking your place in my life and our time drifting away.
 *
 * - On Reflection, Gentle Giant (1975)
 */
namespace aeon::reflection
{

class reflection_object
{
public:
    reflection_object() = default;
    virtual ~reflection_object() = default;

    reflection_object(const reflection_object &) = default;
    auto operator=(const reflection_object &) -> reflection_object & = default;

    reflection_object(reflection_object &&) noexcept = default;
    auto operator=(reflection_object &&) noexcept -> reflection_object & = default;
};

template <typename T>
concept reflection_object_implementation = std::is_base_of_v<reflection_object, T>;

} // namespace aeon::reflection
