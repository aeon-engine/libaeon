// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/ptree/ptree.h>
#include <aeon/ptree/serialization/exception.h>
#include <aeon/streams/idynamic_stream.h>

namespace aeon::ptree::serialization
{

class ptree_unsupported_ini_format final : public ptree_serialization_exception
{
};

/*!
 * Serialize to a utf-8 encoded ini file.
 *
 * The ini format poses some limitations on the format of the ptree.
 * - The root ptree must be an object type
 * - The keys of this root are used as the segments
 * - The values must also be an object type as their key-values are mapped
 *   directly to key value pairs under the segments.
 * - Values can not be an array or object.
 *
 * Any other format will throw an ptree_unsupported_ini_format exception.
 *
 * It is recommended to use the config_file wrapper when using ini format
 * serialization. The config_file wrapper will always read and write in
 * the expected format as described above.
 */
void to_ini(const property_tree &ptree, streams::idynamic_stream &stream);
auto to_ini(const property_tree &ptree) -> std::string;

void from_ini(streams::idynamic_stream &stream, property_tree &ptree);
auto from_ini(streams::idynamic_stream &stream) -> property_tree;
auto from_ini(const std::string &str) -> property_tree;

} // namespace aeon::ptree::serialization
