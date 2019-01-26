// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <turbojpeg.h>

namespace aeon::imaging::file::jpg::detail
{

class tjhandle_wrapper
{
public:
    tjhandle_wrapper(tjhandle handle);
    ~tjhandle_wrapper();

    tjhandle_wrapper(const tjhandle_wrapper &) = delete;
    auto operator=(const tjhandle_wrapper &) -> tjhandle_wrapper & = delete;

    tjhandle_wrapper(tjhandle_wrapper &&o) = default;
    auto operator=(tjhandle_wrapper &&other) -> tjhandle_wrapper & = default;

    auto handle() const;

private:
    tjhandle handle_;
};

inline tjhandle_wrapper::tjhandle_wrapper(tjhandle handle)
    : handle_(handle)
{
}

inline tjhandle_wrapper::~tjhandle_wrapper()
{
    if (handle_)
        tjDestroy(handle_);
}

inline auto tjhandle_wrapper::handle() const
{
    return handle_;
}

class tjhandle_decompress_wrapper : public tjhandle_wrapper
{
public:
    tjhandle_decompress_wrapper();
    ~tjhandle_decompress_wrapper() = default;

    tjhandle_decompress_wrapper(const tjhandle_decompress_wrapper &) = delete;
    auto operator=(const tjhandle_decompress_wrapper &) -> tjhandle_decompress_wrapper & = delete;

    tjhandle_decompress_wrapper(tjhandle_decompress_wrapper &&o) = default;
    auto operator=(tjhandle_decompress_wrapper &&other) -> tjhandle_decompress_wrapper & = default;
};

inline tjhandle_decompress_wrapper::tjhandle_decompress_wrapper()
    : tjhandle_wrapper(tjInitDecompress())
{
}

class tjhandle_compress_wrapper : public tjhandle_wrapper
{
public:
    tjhandle_compress_wrapper();
    ~tjhandle_compress_wrapper() = default;

    tjhandle_compress_wrapper(const tjhandle_compress_wrapper &) = delete;
    auto operator=(const tjhandle_compress_wrapper &) -> tjhandle_compress_wrapper & = delete;

    tjhandle_compress_wrapper(tjhandle_compress_wrapper &&o) = default;
    auto operator=(tjhandle_compress_wrapper &&other) -> tjhandle_compress_wrapper & = default;
};

inline tjhandle_compress_wrapper::tjhandle_compress_wrapper()
    : tjhandle_wrapper(tjInitCompress())
{
}

} // namespace aeon::imaging::file::jpg::detail
