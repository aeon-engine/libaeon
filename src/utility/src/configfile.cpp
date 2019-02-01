// Copyright (c) 2012-2019 Robin Degen

#include <aeon/utility/configfile.h>
#include <aeon/streams/dynamic_stream_reader.h>
#include <aeon/streams/dynamic_stream_writer.h>
#include <aeon/streams/devices/file_device.h>
#include <aeon/streams/devices/span_device.h>
#include <aeon/streams/devices/memory_device.h>
#include <aeon/streams/dynamic_stream.h>

namespace aeon::utility
{

bool configfile::has_entry(const std::string &key) const
{
    const auto itr = entries_.find(key);
    return (itr != entries_.end());
}

void configfile::load(streams::idynamic_stream &stream)
{
    if (stream.has_status() && !stream.good())
        throw configfile_exception();

    entries_.clear();

    // Loop through all lines
    auto line_number = 0;
    streams::dynamic_stream_reader reader(stream);
    while (!stream.eof())
    {
        const auto line = reader.read_line();
        ++line_number;
        __read_line(line);
    }
}

void configfile::save(streams::idynamic_stream &stream) const
{
    if (stream.has_status() && !stream.good())
        throw configfile_exception();

    streams::dynamic_stream_writer writer(stream);

    for (const auto &itr : entries_)
    {
        const auto line = itr.first + "=" + itr.second;
        writer << line << '\n';
    }
}

void configfile::load(const std::filesystem::path &path)
{
    try
    {
        auto stream = streams::make_dynamic_stream(streams::file_source_device{path, streams::file_mode::binary});
        load(stream);
    }
    catch (const streams::stream_exception &)
    {
        throw configfile_exception();
    }
}

void configfile::save(const std::filesystem::path &path) const
{
    auto stream = streams::make_dynamic_stream(
        streams::file_sink_device{path, streams::file_mode::binary, streams::file_flag::truncate});
    save(stream);
}

void configfile::load(const std::vector<char> &data)
{
    // TODO: Fix issue with const vector
    auto stream = streams::make_dynamic_stream(streams::memory_device{data});
    load(stream);
}

void configfile::save(std::vector<char> &data) const
{
    auto stream = streams::make_dynamic_stream(streams::memory_device<char>{});
    save(stream);

    streams::dynamic_stream_reader reader(stream);
    reader.read_to_vector(data);
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
