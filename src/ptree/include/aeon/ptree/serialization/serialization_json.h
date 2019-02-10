// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/ptree/ptree.h>

namespace aeon::ptree::serialization
{

void to_json(const property_tree &ptree, std::string &str);
auto to_json(const property_tree &ptree) -> std::string;

void from_json(std::string_view str, property_tree &ptree);
auto from_json(std::string_view str) -> property_tree;

} // namespace aeon::ptree::serialization
