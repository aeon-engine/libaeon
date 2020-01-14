// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <ios>

namespace aeon::common
{

template <typename stream_t>
class scoped_fmtflags final
{
public:
    explicit scoped_fmtflags(stream_t &stream)
        : stream_{stream}
        , flags_{stream_.flags()}
    {
    }

    ~scoped_fmtflags()
    {
        stream_.flags(flags_);
    }

    scoped_fmtflags(const scoped_fmtflags &) = delete;
    auto operator=(const scoped_fmtflags &) -> scoped_fmtflags & = delete;
    scoped_fmtflags(scoped_fmtflags &&) noexcept = delete;
    auto operator=(scoped_fmtflags &&) noexcept -> scoped_fmtflags & = delete;

private:
    stream_t &stream_;
    std::ios_base::fmtflags flags_;
};

} // namespace aeon::common
