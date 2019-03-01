// Copyright (c) 2012-2019 Robin Degen

#include <aeon/ptree/serialization/serialization_abf.h>
#include <aeon/ptree/serialization/exception.h>
#include <aeon/streams/devices/memory_view_device.h>
#include <aeon/streams/dynamic_stream.h>
#include <aeon/streams/stream_writer.h>
#include <aeon/streams/stream_reader.h>
#include <aeon/streams/length_prefix_string.h>
#include <aeon/utility/uuid_stream.h>

namespace aeon::ptree::serialization
{

namespace internal
{

static constexpr std::uint8_t chunk_type_null = 0x00;
static constexpr std::uint8_t chunk_type_array = 0x01;
static constexpr std::uint8_t chunk_type_object = 0x02;
static constexpr std::uint8_t chunk_type_string = 0x03;
static constexpr std::uint8_t chunk_type_integer = 0x04;
static constexpr std::uint8_t chunk_type_double = 0x05;
static constexpr std::uint8_t chunk_type_bool = 0x06;
static constexpr std::uint8_t chunk_type_uuid = 0x07;

void to_abf(const std::monostate, streams::idynamic_stream &);
void to_abf(const array &arr, streams::idynamic_stream &stream);
void to_abf(const object &obj, streams::idynamic_stream &stream);
void to_abf(const std::string &obj_str, streams::idynamic_stream &stream);
void to_abf(const utility::uuid &uuid, streams::idynamic_stream &stream);
void to_abf(const std::int64_t val, streams::idynamic_stream &stream);
void to_abf(const double val, streams::idynamic_stream &stream);
void to_abf(const bool val, streams::idynamic_stream &stream);

void to_abf(const property_tree &ptree, streams::idynamic_stream &stream)
{
    std::visit([&stream](auto &&arg) { internal::to_abf(arg, stream); }, ptree.value());
}

void to_abf(const std::monostate, streams::idynamic_stream &stream)
{
    streams::stream_writer writer{stream};
    writer << chunk_type_null;
}

void to_abf(const array &arr, streams::idynamic_stream &stream)
{
    streams::stream_writer writer{stream};
    writer << chunk_type_array;

    writer << static_cast<std::uint64_t>(std::size(arr));

    for (const auto &pt : arr)
    {
        to_abf(pt, stream);
    }
}

void to_abf(const object &obj, streams::idynamic_stream &stream)
{
    streams::stream_writer writer{stream};
    writer << chunk_type_object;

    writer << static_cast<std::uint64_t>(std::size(obj));

    for (const auto &[key, val] : obj)
    {
        writer << streams::length_prefix_string<streams::varint>{key};
        to_abf(val, stream);
    }
}

void to_abf(const std::string &obj_str, streams::idynamic_stream &stream)
{
    streams::stream_writer writer{stream};
    writer << chunk_type_string;
    writer << streams::length_prefix_string<streams::varint>{obj_str};
}

void to_abf(const utility::uuid &uuid, streams::idynamic_stream &stream)
{
    streams::stream_writer writer{stream};
    writer << chunk_type_uuid;
    writer << uuid;
}

void to_abf(const std::int64_t val, streams::idynamic_stream &stream)
{
    streams::stream_writer writer{stream};
    writer << chunk_type_integer;
    writer << val;
}

void to_abf(const double val, streams::idynamic_stream &stream)
{
    streams::stream_writer writer{stream};
    writer << chunk_type_double;
    writer << val;
}

void to_abf(const bool val, streams::idynamic_stream &stream)
{
    streams::stream_writer writer{stream};
    writer << chunk_type_bool;
    writer << static_cast<std::uint8_t>(val);
}

class abf_parser final
{
public:
    explicit abf_parser(streams::idynamic_stream &view)
        : reader_{view}
    {
    }

    [[nodiscard]] auto parse() -> property_tree
    {
        std::uint8_t chunk_type = 0;
        reader_ >> chunk_type;

        switch (chunk_type)
        {
            case chunk_type_null:
                return nullptr;
            case chunk_type_array:
                return parse_array();
            case chunk_type_object:
                return parse_object();
            case chunk_type_string:
            {
                std::string str;
                reader_ >> streams::length_prefix_string<streams::varint>{str};
                return str;
            }
            case chunk_type_integer:
            {
                std::int64_t val = 0;
                reader_ >> val;
                return val;
            }
            case chunk_type_double:
            {
                double val = 0.0;
                reader_ >> val;
                return val;
            }
            case chunk_type_bool:
            {
                std::uint8_t val = 0;
                reader_ >> val;
                return static_cast<bool>(val);
            }
            case chunk_type_uuid:
            {
                utility::uuid uuid;
                reader_ >> uuid;
                return uuid;
            }
            default:
                throw ptree_serialization_exception{};
        }
    }

private:
    [[nodiscard]] auto parse_object() -> property_tree
    {
        object data;

        std::uint64_t count = 0;
        reader_ >> count;

        data.reserve(count);

        while (count != 0)
        {
            std::string key;
            reader_ >> streams::length_prefix_string<streams::varint>{key};
            data.emplace(std::move(key), parse());
            --count;
        }

        return data;
    }

    [[nodiscard]] auto parse_array() -> property_tree
    {
        array data;

        std::uint64_t count = 0;
        reader_ >> count;

        data.reserve(count);

        while (count != 0)
        {
            data.push_back(parse());
            --count;
        }

        return data;
    }

    streams::stream_reader<streams::idynamic_stream> reader_;
};

} // namespace internal

void to_abf(const property_tree &ptree, streams::idynamic_stream &stream)
{
    internal::to_abf(ptree, stream);
}

[[nodiscard]] auto to_abf(const property_tree &ptree) -> std::vector<std::uint8_t>
{
    std::vector<std::uint8_t> data;
    auto stream = streams::make_dynamic_stream(streams::memory_view_device{data});
    to_abf(ptree, stream);
    return data;
}

void from_abf(streams::idynamic_stream &stream, property_tree &ptree)
{
    internal::abf_parser parser{stream};
    ptree = parser.parse();
}

[[nodiscard]] auto from_abf(streams::idynamic_stream &stream) -> property_tree
{
    property_tree pt;
    from_abf(stream, pt);
    return pt;
}

} // namespace aeon::ptree::serialization
