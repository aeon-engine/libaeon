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

#include <aeon/utility.h>

namespace aeon
{
namespace utility
{
namespace string
{

std::vector<std::string> &split(const std::string &str, char delim, std::vector<std::string> &elements)
{
    std::stringstream ss(str);
    std::string item;

    while (std::getline(ss, item, delim))
    {
        elements.push_back(item);
    }

    return elements;
}

std::vector<std::string> split(const std::string &str, char delim)
{
    std::vector<std::string> elements;
    split(str, delim, elements);
    return elements;
}

void ltrim(std::string &str)
{
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
}

void rtrim(std::string &str)
{
    str.erase(std::find_if(str.rbegin(), str.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), str.end());
}

void trim(std::string &str)
{
    ltrim(str);
    rtrim(str);
}

std::vector<std::string> args_to_vector(int argc, char *argv[])
{
    std::vector<std::string> vec;

    for (int i = 0; i < argc; ++i)
    {
        vec.push_back(argv[i]);
    }

    return vec;
}

} // namespace string
} // namespace utility
} // namespace aeon
