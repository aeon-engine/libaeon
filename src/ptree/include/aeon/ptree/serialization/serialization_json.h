// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/ptree/ptree.h>
#include <aeon/streams/idynamic_stream.h>

namespace aeon::ptree::serialization
{

/*!
 * Deserialize a ptree to a json string. Note that a UUID will always serialize into a string due to limitations in JSON
 */
void to_json(const property_tree &ptree, streams::idynamic_stream &stream);

/*!
 * Deserialize a ptree to a json string. Note that a UUID will always serialize into a string due to limitations in JSON
 */
auto to_json(const property_tree &ptree) -> std::string;

/*!
 * Deserialize a string to a ptree. Note that a UUID will always deserialize into a string due to limitations in JSON
 */
void from_json(streams::idynamic_stream &stream, property_tree &ptree);

/*!
 * Deserialize a string to a ptree. Note that a UUID will always deserialize into a string due to limitations in JSON
 */
auto from_json(streams::idynamic_stream &stream) -> property_tree;

} // namespace aeon::ptree::serialization
