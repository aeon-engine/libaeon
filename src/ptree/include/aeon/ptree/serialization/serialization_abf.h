// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/ptree/ptree.h>
#include <aeon/streams/idynamic_stream.h>

namespace aeon::ptree::serialization
{

void to_abf(const property_tree &ptree, streams::idynamic_stream &stream);
auto to_abf(const property_tree &ptree) -> std::vector<std::uint8_t>;

void from_abf(streams::idynamic_stream &stream, property_tree &ptree);
auto from_abf(streams::idynamic_stream &stream) -> property_tree;

} // namespace aeon::ptree::serialization
