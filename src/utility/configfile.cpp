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

bool configfile::load(aeon::streams::stream_ptr stream)
{
    if (!stream->good())
        return false;

    entries_.clear();

    aeon::streams::stream_reader reader(*stream);

    // Loop through all lines
    int linenumber = 0;
    while (!stream->eof())
    {
        linenumber++;

        std::string line = reader.read_line();

        if (line.empty())
            continue;

        size_t length = line.size();

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

    return true;
}

void configfile::save(aeon::streams::stream_ptr stream)
{
    if (!stream->good())
        return;

    aeon::streams::stream_writer writer(*stream);

    for (auto itr : entries_)
    {
        std::string line = itr.first + "=" + itr.second;
        writer.write_line(line);
    }
}

} // namespace utility
} // namespace aeon
