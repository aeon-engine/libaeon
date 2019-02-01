// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/streams/devices/detail/iostream_device_base.h>
#include <aeon/streams/tags.h>

namespace aeon::streams
{

template <typename T>
class iostream_source_device : internal::iostream_device_base<T>
{
public:
    struct category : input, input_seekable, flushable, has_eof, has_status
    {
    };

    explicit iostream_source_device() noexcept
        : internal::iostream_device_base<T>{nullptr}
    {
    }

    explicit iostream_source_device(T &stream) noexcept
        : internal::iostream_device_base<T>{stream}
    {
    }

    iostream_source_device(iostream_source_device &&) noexcept = default;
    auto operator=(iostream_source_device &&) noexcept -> iostream_source_device & = default;

    iostream_source_device(const iostream_source_device &) noexcept = default;
    auto operator=(const iostream_source_device &) noexcept -> iostream_source_device & = default;

    ~iostream_source_device() = default;

    using internal::iostream_device_base<T>::read;
    using internal::iostream_device_base<T>::seekg;
    using internal::iostream_device_base<T>::tellg;
    using internal::iostream_device_base<T>::eof;
    using internal::iostream_device_base<T>::good;
    using internal::iostream_device_base<T>::fail;
    using internal::iostream_device_base<T>::flush;
};

template <typename T>
class iostream_sink_device : internal::iostream_device_base<T>
{
public:
    struct category : output, output_seekable, flushable, has_eof, has_status
    {
    };

    explicit iostream_sink_device() noexcept
        : internal::iostream_device_base<T>{nullptr}
    {
    }

    explicit iostream_sink_device(T &stream) noexcept
        : internal::iostream_device_base<T>{stream}
    {
    }

    iostream_sink_device(iostream_sink_device &&) noexcept = default;
    auto operator=(iostream_sink_device &&) noexcept -> iostream_sink_device & = default;

    iostream_sink_device(const iostream_sink_device &) noexcept = default;
    auto operator=(const iostream_sink_device &) noexcept -> iostream_sink_device & = default;

    ~iostream_sink_device() = default;

    using internal::iostream_device_base<T>::write;
    using internal::iostream_device_base<T>::seekp;
    using internal::iostream_device_base<T>::tellp;
    using internal::iostream_device_base<T>::eof;
    using internal::iostream_device_base<T>::good;
    using internal::iostream_device_base<T>::fail;
    using internal::iostream_device_base<T>::flush;
};

template <typename T>
class iostream_device : internal::iostream_device_base<T>
{
public:
    struct category : input, input_seekable, output, output_seekable, flushable, has_eof, has_status
    {
    };

    explicit iostream_device() noexcept
        : internal::iostream_device_base<T>{nullptr}
    {
    }

    explicit iostream_device(T &stream) noexcept
        : internal::iostream_device_base<T>{stream}
    {
    }

    iostream_device(iostream_device &&) noexcept = default;
    auto operator=(iostream_device &&) noexcept -> iostream_device & = default;

    iostream_device(const iostream_device &) noexcept = default;
    auto operator=(const iostream_device &) noexcept -> iostream_device & = default;

    ~iostream_device() = default;

    using internal::iostream_device_base<T>::read;
    using internal::iostream_device_base<T>::seekg;
    using internal::iostream_device_base<T>::tellg;
    using internal::iostream_device_base<T>::write;
    using internal::iostream_device_base<T>::seekp;
    using internal::iostream_device_base<T>::tellp;
    using internal::iostream_device_base<T>::eof;
    using internal::iostream_device_base<T>::good;
    using internal::iostream_device_base<T>::fail;
    using internal::iostream_device_base<T>::flush;
};

} // namespace aeon::streams
