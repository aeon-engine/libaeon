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

bool configfile::has_entry(const std::string &key)
{
    auto itr = entries_.find(key);

    return (itr != entries_.end());
}

void configfile::load(aeon::streams::file_stream_ptr stream)
{
    if (!stream->good())
        throw configfile_exception();

    entries_.clear();

    // Loop through all lines
    int linenumber = 0;
    std::string line;
    while (stream->read_line(line))
    {
        ++linenumber;

        if (line.empty())
            continue;

        // Ignore comments
        if (line[0] == '#')
            continue;

        size_t pos = line.find_first_of('=');

        if (pos == std::string::npos || pos == 0)
            continue;

        std::string key = line.substr(0, pos);
        std::string val = line.substr(pos + 1);

        entries_[key] = val;
    }
}

void configfile::save(aeon::streams::file_stream_ptr stream)
{
    if (!stream->good())
        throw configfile_exception();

    for (auto itr : entries_)
    {
        std::string line = itr.first + "=" + itr.second;
        stream->write_line(line);
    }
}

} // namespace utility
} // namespace aeon
