// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/ptree/ptree.h>
#include <aeon/streams/idynamic_stream.h>

namespace aeon::ptree::serialization
{

enum class abf_deserialize_mode
{
    all,
    skip_blobs
};

void to_abf(const property_tree &ptree, streams::idynamic_stream &stream);
[[nodiscard]] auto to_abf(const property_tree &ptree) -> std::vector<std::uint8_t>;

void from_abf(streams::idynamic_stream &stream, property_tree &ptree,
              const abf_deserialize_mode mode = abf_deserialize_mode::all);
[[nodiscard]] auto from_abf(streams::idynamic_stream &stream,
                            const abf_deserialize_mode mode = abf_deserialize_mode::all) -> property_tree;

} // namespace aeon::ptree::serialization
