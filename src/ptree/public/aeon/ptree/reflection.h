// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/ptree/ptree.h>
#include <aeon/ptree/exception.h>
#include <aeon/reflection/reflection_info.h>
#include <aeon/reflection/reflection_object.h>
#include <aeon/common/memory.h>

namespace aeon::ptree
{

[[nodiscard]] auto to_reflection_object(const reflection::reflection_info &reflection_info, const property_tree &pt)
    -> std::unique_ptr<reflection::reflection_object>;

template <reflection::reflection_object_implementation T>
[[nodiscard]] inline auto to_reflection_object(const property_tree &pt) -> std::unique_ptr<T>
{
    auto object = to_reflection_object(T::reflection_info(), pt);
    auto result = common::dynamic_unique_ptr_cast<T>(std::move(object));

    if (!result)
        throw ptree_exception{};

    return result;
}

[[nodiscard]] auto from_reflection_object(const reflection::reflection_object &obj,
                                          const reflection::reflection_info &reflection_info) -> property_tree;

} // namespace aeon::ptree
