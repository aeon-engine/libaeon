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

void configfile::load(streams::stream &stream)
{
    if (!stream.good())
        throw configfile_exception();

    entries_.clear();

    // Loop through all lines
    int linenumber = 0;
    std::string line;

    // A stream reader on a file stream is optimized for reading lines if the file was opened in text mode.
    // This will likely break on files opened as binary.
    if (stream.is<streams::file_stream>())
    {
        streams::stream_reader<streams::file_stream> reader(stream.as<streams::file_stream>());
        while (!stream.eof())
        {
            line = reader.read_line();
            ++linenumber;
            __read_line(line);
        }
    }
    else
    {
        streams::stream_reader<streams::stream> reader(stream);
        while (!stream.eof())
        {
            line = reader.read_line();
            ++linenumber;
            __read_line(line);
        }
    }
}

void configfile::save(streams::stream &stream)
{
    if (!stream.good())
        throw configfile_exception();

    streams::stream_writer writer(stream);

    for (auto itr : entries_)
    {
        std::string line = itr.first + "=" + itr.second;
        writer.write_line(line);
    }
}

void configfile::load(const std::string &path)
{
    try
    {
        streams::file_stream stream(path, streams::access_mode::read, streams::file_mode::text);
        load(stream);
    }
    catch(const streams::file_stream_exception&)
    {
        throw configfile_exception();
    }
}

void configfile::save(const std::string &path)
{
    streams::file_stream stream(path, streams::access_mode::read_write | streams::access_mode::truncate,
                                streams::file_mode::text);

    save(stream);
}

void configfile::load(std::vector<std::uint8_t> &&data)
{
    streams::memory_stream stream(std::move(data), streams::access_mode::read);
    load(stream);
}

void configfile::save(std::vector<std::uint8_t> &data)
{
    streams::memory_stream stream;
    save(stream);
    data = std::move(stream.read_to_vector());
}

void configfile::__read_line(const std::string &line)
{
    if (line.empty())
        return;

    // Ignore comments
    if (line[0] == '#')
        return;

    size_t pos = line.find_first_of('=');

    if (pos == std::string::npos || pos == 0)
        return;

    std::string key = line.substr(0, pos);
    std::string val = line.substr(pos + 1);

    entries_[key] = val;
}

} // namespace utility
} // namespace aeon
