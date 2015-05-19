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

std::string configfile::get_string(const std::string &key,
                                   const std::string &default_val)
{
    auto itr = entries_.find(key);

    // If it could not find the key...
    if (itr == entries_.end())
    {
        set_string(key, default_val);
        return default_val;
    }

    return itr->second;
}

int configfile::get_integer(const std::string &key, int default_val)
{
    auto itr = entries_.find(key);

    // If it could not find the key...
    if (itr == entries_.end())
    {
        set_integer(key, default_val);
        return default_val;
    }

    return std::stoi(itr->second);
}

float configfile::get_float(const std::string &key, float default_val)
{
    auto itr = entries_.find(key);

    if (itr == entries_.end())
    {
        set_float(key, default_val);
        return default_val;
    }

    return std::stof(itr->second);
}

bool configfile::get_boolean(const std::string &key, bool default_val)
{
    auto itr = entries_.find(key);

    // If it could not find the key...
    if (itr == entries_.end())
    {
        set_boolean(key, default_val);
        return default_val;
    }

    return itr->second == "1" || itr->second == "true";
}

void configfile::set_string(const std::string &key, const std::string &val)
{
    entries_[key] = val;
}

void configfile::set_integer(const std::string &key, int val)
{
    set_string(key, std::to_string(val));
}

void configfile::set_float(const std::string &key, float val)
{
    set_string(key, std::to_string(val));
}

void configfile::set_boolean(const std::string &key, bool val)
{
    set_string(key, val ? "1" : "0");
}

void configfile::load(aeon::streams::file_stream_ptr stream)
{
    if (!stream->good())
        throw configfile_exception();

    if (!stream->is_text())
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

    if (!stream->is_text())
        throw configfile_exception();

    aeon::streams::stream_writer writer(*stream);

    for (auto itr : entries_)
    {
        std::string line = itr.first + "=" + itr.second;
        writer.write_line(line);
    }
}

} // namespace utility
} // namespace aeon
