// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/streams/stream_reader.h>
#include <aeon/streams/stream_writer.h>

namespace aeon::streams
{

template <typename T>
inline auto &operator<<(stream_writer &writer, const std::vector<T> &val)
{
    for (const auto &v : val)
        writer << v;

    return writer;
}

} // namespace aeon::streams
