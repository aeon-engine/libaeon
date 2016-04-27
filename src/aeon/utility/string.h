/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2016 Robin Degen
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains the property of
 * Robin Degen and its suppliers, if any. The intellectual and technical
 * concepts contained herein are proprietary to Robin Degen and its suppliers
 * and may be covered by U.S. and Foreign Patents, patents in process, and are
 * protected by trade secret or copyright law. Dissemination of this
 * information or reproduction of this material is strictly forbidden unless
 * prior written permission is obtained from Robin Degen.
 */

#pragma once

namespace aeon
{
namespace utility
{
namespace string
{

/*!
 * Split/tokenize a string into a vector of strings based on a delimiter.
 * Appends tokens to the given elements vector and returns it.
 */
std::vector<std::string> &split(const std::string &str, char delim, std::vector<std::string> &elements);

/*!
 * Split/tokenize a string into a vector of strings based on a delimiter.
 * Returns a vector of split elements.
 */
std::vector<std::string> split(const std::string &str, char delim);

/*!
 * Trim from the start of a string
 */
void ltrim(std::string &str);

/*!
 * Trim from the ending of a string
 */
void rtrim(std::string &str);

/*!
 * Trim a string at the start and end.
 */
void trim(std::string &str);

/*!
 * Trim from the start of a string
 */
std::string ltrimmed(const std::string &str);

/*!
 * Trim from the ending of a string
 */
std::string rtrimmed(const std::string &str);

/*!
 * Trim a string at the start and end.
 */
std::string trimmed(const std::string &str);

/*!
 * Get len characters from the left of the string.
 */
std::string left(const std::string &str, int len);

/*!
 * Get len characters from the right of the string.
 */
std::string right(const std::string &str, int len);

/*!
 * Convert standard argc and argv arguments into a vector of strings.
 */
std::vector<std::string> args_to_vector(int argc, char *argv[]);

} // namespace string
} // namespace utility
} // namespace aeon
