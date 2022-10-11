// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

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
[[nodiscard]] auto to_json(const property_tree &ptree) -> common::string;

/*!
 * Deserialize a string to a ptree. Note that a UUID will always deserialize into a string due to limitations in JSON
 */
void from_json(streams::idynamic_stream &stream, property_tree &ptree);

/*!
 * Deserialize a stream to a ptree. Note that a UUID will always deserialize into a string due to limitations in JSON
 */
[[nodiscard]] auto from_json(streams::idynamic_stream &stream) -> property_tree;

/*!
 * Deserialize a string to a ptree. Note that a UUID will always deserialize into a string due to limitations in JSON
 */
[[nodiscard]] auto from_json(const common::string &str) -> property_tree;

} // namespace aeon::ptree::serialization
