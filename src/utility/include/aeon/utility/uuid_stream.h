// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/utility/uuid.h>
#include <aeon/streams/stream_writer.h>
#include <aeon/streams/stream_reader.h>

namespace aeon::utility
{

inline auto operator<<(streams::stream_writer &stream, const uuid &val) -> streams::stream_writer &
{
    stream.internal_stream().write(val.data.data(), val.size());
    return stream;
}

template <typename T>
inline auto operator>>(streams::stream_reader<T> &stream, uuid &val) -> streams::stream_reader<T> &
{
    stream.internal_stream().read(val.data.data(), val.size());
    return stream;
}

} // namespace aeon::utility
