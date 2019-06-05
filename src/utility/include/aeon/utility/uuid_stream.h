// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include <aeon/utility/uuid.h>
#include <aeon/streams/stream_writer.h>
#include <aeon/streams/stream_reader.h>

namespace aeon::utility
{

template <typename device_t>
inline auto operator<<(streams::stream_writer<device_t> &stream, const uuid &val)
{
    const auto size = static_cast<std::streamsize>(val.size());

    if (stream.device().write(reinterpret_cast<const char *>(val.data.data()), size) != size)
        throw streams::stream_exception{};

    return stream;
}

template <typename device_t>
inline auto operator>>(streams::stream_reader<device_t> &stream, uuid &val)
{
    const auto size = static_cast<std::streamsize>(val.size());

    if (stream.device().read(reinterpret_cast<char *>(val.data.data()), size) != size)
        throw streams::stream_exception{};

    return stream;
}

} // namespace aeon::utility
