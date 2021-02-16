// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/file_container/container.h>
#include <aeon/file_container/exception.h>
#include <aeon/ptree/serialization/serialization_abf.h>
#include <aeon/streams/stream_reader.h>
#include <aeon/streams/stream_writer.h>
#include <aeon/streams/uuid_stream.h>
#include <aeon/streams/length_prefix_string.h>
#include <aeon/common/uuid.h>
#include <aeon/common/fourcc.h>
#include <cstdint>

namespace aeon::file_container
{

namespace internal
{

static constexpr std::uint32_t header_magic = common::fourcc('A', 'F', 'C', '1');

struct header
{
    std::uint32_t fourcc = header_magic;
    common::uuid id{};
    std::uint32_t flags = 0;
    std::uint64_t size = 0;
    std::string name{};
};

template <typename device_t>
inline auto &operator<<(streams::stream_writer<device_t> &writer, const header &h)
{
    writer << h.fourcc;
    writer << h.id;
    writer << h.flags;
    writer << h.size;
    writer << streams::length_prefix_string<std::uint16_t>{h.name};
    return writer;
}

template <typename device_t>
inline auto &operator>>(streams::stream_reader<device_t> &reader, header &h)
{
    reader >> h.fourcc;
    reader >> h.id;
    reader >> h.flags;
    reader >> h.size;
    reader >> streams::length_prefix_string<std::uint16_t>{h.name};
    return reader;
}

} // namespace internal

container::container(streams::idynamic_stream &stream, const common::flags<read_items> items)
    : name_{}
    , id_{}
    , data_{}
    , metadata_{}
{
    streams::stream_reader reader{stream};

    internal::header header;
    reader >> header;

    if (header.fourcc != internal::header_magic)
        throw resource_file_exception{};

    id_ = header.id;
    name_ = std::move(header.name);

    if (items.is_set(read_items::data))
        reader.read_to_vector(data_, static_cast<std::streamoff>(header.size));
    else if (items.is_set(read_items::metadata))
        reader.device().seekg(static_cast<std::streamoff>(header.size), streams::seek_direction::current);

    if (items.is_set(read_items::metadata))
        ptree::serialization::from_abf(stream, metadata_);
}

container::container(std::string name) noexcept
    : container{std::move(name), common::uuid::generate()}
{
}

container::container(std::string name, common::uuid id) noexcept
    : name_{std::move(name)}
    , id_{std::move(id)}
    , data_{}
    , metadata_{}
{
}

container::~container() = default;

void container::name(std::string name) noexcept
{
    name_ = std::move(name);
}

auto container::name() const noexcept -> const std::string &
{
    return name_;
}

void container::id(common::uuid id) noexcept
{
    id_ = std::move(id);
}

auto container::id() const noexcept -> const common::uuid &
{
    return id_;
}

auto container::stream() noexcept -> streams::memory_view_device<std::vector<std::uint8_t>>
{
    return streams::memory_view_device{data_};
}

auto container::stream() const noexcept -> streams::memory_view_device<std::vector<std::uint8_t>>
{
    return streams::memory_view_device{data_};
}

auto container::metadata() noexcept -> ptree::property_tree &
{
    return metadata_;
}

auto container::metadata() const noexcept -> const ptree::property_tree &
{
    return metadata_;
}

void container::write(streams::idynamic_stream &stream) const
{
    internal::header header;
    header.id = id_;
    header.flags = 0;
    header.size = std::size(data_);
    header.name = name_;

    streams::stream_writer writer{stream};
    writer << header;

    writer.vector_write(data_);

    ptree::serialization::to_abf(metadata_, stream);
}

} // namespace aeon::file_container
