// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <aeon/crypto/sha256.h>
#include <aeon/streams/filters/filter.h>
#include <aeon/streams/tags.h>
#include <iostream>
#include <array>

namespace aeon::crypto::stream_filters
{

class sha256_filter : public streams::filter
{
public:
    struct category : streams::output
    {
    };

    sha256_filter() noexcept
        : sha256_{}
    {
    }

    sha256_filter(sha256_filter &&) noexcept = default;
    auto operator=(sha256_filter &&) noexcept -> sha256_filter & = default;

    sha256_filter(const sha256_filter &) = delete;
    auto operator=(const sha256_filter &) -> sha256_filter & = delete;

    ~sha256_filter() = default;

    template <typename sink_t>
    auto write(sink_t &sink, const char *data, const std::streamsize size) -> std::streamsize
    {
        sha256_.write(data, size);
        return sink.write(data, size);
    }

    [[nodiscard]] auto finalize() noexcept -> std::array<std::uint8_t, 32>
    {
        return sha256_.finalize();
    }

    void reset() noexcept
    {
        sha256_.reset();
    }

private:
    sha256 sha256_;
};

} // namespace aeon::crypto::stream_filters
