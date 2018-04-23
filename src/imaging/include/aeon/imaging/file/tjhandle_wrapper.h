/*
 * Copyright (c) 2012-2018 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

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
