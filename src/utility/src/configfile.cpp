// Copyright (c) 2012-2019 Robin Degen

#include <aeon/utility/configfile.h>
#include <aeon/streams/stream_reader.h>
#include <aeon/streams/stream_writer.h>
#include <aeon/streams/file_stream.h>
#include <aeon/streams/memory_stream.h>
#include <aeon/streams/stream.h>
#include <aeon/streams/access_mode_mixin.h>

namespace aeon::utility
{

bool configfile::has_entry(const std::string &key) const
{
    const auto itr = entries_.find(key);
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
        streams::stream_reader reader(stream.as<streams::file_stream>());
        while (!stream.eof())
        {
            line = reader.read_line();
            ++linenumber;
            __read_line(line);
        }
    }
    else
    {
        streams::stream_reader reader(stream);
        while (!stream.eof())
        {
            line = reader.read_line();
            ++linenumber;
            __read_line(line);
        }
    }
}

void configfile::save(streams::stream &stream) const
{
    if (!stream.good())
        throw configfile_exception();

    streams::stream_writer writer(stream);

    for (const auto &itr : entries_)
    {
        const auto line = itr.first + "=" + itr.second;
        writer.write_line(line);
    }
}

void configfile::load(const std::filesystem::path &path)
{
    try
    {
        streams::file_stream stream(path, streams::access_mode::read, streams::file_mode::text);
        load(stream);
    }
    catch (const streams::file_stream_exception &)
    {
        throw configfile_exception();
    }
}

void configfile::save(const std::filesystem::path &path) const
{
    streams::file_stream stream(path, streams::access_mode::write | streams::access_mode::truncate,
                                streams::file_mode::text);

    save(stream);
}

void configfile::load(std::vector<std::uint8_t> &&data)
{
    streams::memory_stream stream(std::move(data), streams::access_mode::read);
    load(stream);
}

void configfile::save(std::vector<std::uint8_t> &data) const
{
    streams::memory_stream stream;
    save(stream);
    data = stream.read_to_vector();
}

void configfile::__read_line(const std::string &line)
{
    if (line.empty())
        return;

    // Ignore comments
    if (line[0] == '#')
        return;

    const auto pos = line.find_first_of('=');

    if (pos == std::string::npos || pos == 0)
        return;

    const auto key = line.substr(0, pos);
    const auto val = line.substr(pos + 1);

    entries_[key] = val;
}

} // namespace aeon::utility
