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

#include <aeon/imaging/file/jpg_file.h>
#include <aeon/imaging/file/tjhandle_wrapper.h>
#include <aeon/streams/file_stream.h>
#include <aeon/common/assert.h>
#include <turbojpeg.h>

namespace aeon::imaging::file::jpg
{

namespace detail
{

auto subsample_mode_to_tjsamp(const subsample_mode mode) -> TJSAMP
{
    switch (mode)
    {
        case subsample_mode::subsample_444:
            return TJSAMP_444;
        case subsample_mode::subsample_440:
            return TJSAMP_440;
        case subsample_mode::subsample_422:
            return TJSAMP_422;
        case subsample_mode::subsample_420:
            return TJSAMP_420;
        case subsample_mode::subsample_411:
            return TJSAMP_411;
        case subsample_mode::subsample_grayscale:
            return TJSAMP_GRAY;
    }

    throw save_exception();
}

} // namespace detail

auto load(const std::filesystem::path &path) -> dynamic_image
{
    auto stream = streams::file_stream{path, streams::access_mode::read, streams::file_mode::binary};
    return load(stream);
}

auto load(streams::stream &stream) -> dynamic_image
{
    detail::tjhandle_decompress_wrapper wrapper;

    auto data = stream.read_to_vector();
    const auto data_size = static_cast<unsigned long>(data.size());

    int width = 0;
    int height = 0;

    if (tjDecompressHeader(wrapper.handle(), data.data(), data_size, &width, &height) != 0)
        throw load_exception();

    const image_descriptor<rgb24> d{static_cast<dimension>(width), static_cast<dimension>(height)};
    image<rgb24> loaded_image{d};

    if (tjDecompress2(wrapper.handle(), data.data(), data_size, view(loaded_image).data<std::uint8_t>(), width, 0,
                      height, TJPF_RGB, TJFLAG_FASTDCT) != 0)
        throw load_exception();

    return dynamic_image{std::move(loaded_image)};
}

void save(const dynamic_image &image, const subsample_mode subsample, int quality, const std::filesystem::path &path)
{
    auto stream = streams::file_stream{path, streams::access_mode::write, streams::file_mode::binary};
    save(image, subsample, quality, stream);
}

void save(const dynamic_image &image, const subsample_mode subsample, int quality, streams::stream &stream)
{
    aeon_assert(encoding(image) == pixel_encoding::rgb24, "Encoding mismatch.");
    process_image(image, save, subsample, quality, stream);
}

template <typename T>
void save(const image_view<T> &image, const subsample_mode subsample, int quality, const std::filesystem::path &path)
{
    auto stream = streams::file_stream{path, streams::access_mode::write, streams::file_mode::binary};
    save(image, subsample, quality, stream);
}

template void save<rgb24>(const image_view<rgb24> &image, const subsample_mode subsample, int quality,
                          const std::filesystem::path &path);

template <typename T>
void save(const image_view<T> &image, const subsample_mode subsample, int quality, streams::stream &stream)
{
    aeon_assert_value_in_range(quality, 1, 100);

    detail::tjhandle_compress_wrapper wrapper;

    const auto tjsubsample = detail::subsample_mode_to_tjsamp(subsample);
    std::vector<std::uint8_t> dest_buffer(tjBufSize(width(image), height(image), tjsubsample));
    auto dest_buffer_data = dest_buffer.data();

    auto actual_size = static_cast<unsigned long>(dest_buffer.size());
    if (tjCompress2(wrapper.handle(), image.template data<std::uint8_t>(), width(image),
                    static_cast<int>(stride_y(image)), height(image), TJPF_RGB, &dest_buffer_data, &actual_size,
                    tjsubsample, quality, TJFLAG_NOREALLOC) != 0)
        throw save_exception();

    dest_buffer.resize(actual_size);

    stream.vector_write(dest_buffer);
    stream.flush();
}

template void save<rgb24>(const image_view<rgb24> &image, const subsample_mode subsample, int quality,
                          streams::stream &stream);

} // namespace aeon::imaging::file::jpg
