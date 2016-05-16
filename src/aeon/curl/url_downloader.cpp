/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2016 Robin Degen
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains the property of
 * Robin Degen and its suppliers, if any. The intellectual and technical
 * concepts contained herein are proprietary to Robin Degen and its suppliers
 * and may be covered by U.S. and Foreign Patents, patents in process, and are
 * protected by trade secret or copyright law. Dissemination of this
 * information or reproduction of this material is strictly forbidden unless
 * prior written permission is obtained from Robin Degen.
 */

#include <aeon/curl.h>

namespace aeon
{
namespace curl
{

url_downloader::url_downloader()
{
    wrapper_ = std::make_shared<easy_wrapper>();
}

url_downloader::~url_downloader()
{
    wrapper_ = nullptr;
}

void url_downloader::download(const std::string &url, const std::string &dest_path)
{
    aeon::streams::file_stream f(dest_path, aeon::streams::access_mode::write | aeon::streams::access_mode::truncate);

    if (!f.good())
        throw url_downloader_exception();

    auto func =
        std::bind(&url_downloader::read_event_, this, std::ref(f), std::placeholders::_1, std::placeholders::_2);
    wrapper_->get(url, func);

    f.flush();
}

std::size_t url_downloader::read_event_(aeon::streams::file_stream &dest_stream, void *buffer, std::size_t size)
{
    std::size_t result = dest_stream.write((std::uint8_t *)buffer, size);

    if (result != size)
        throw url_downloader_exception();

    return size;
}

} // namespace curl
} // namespace aeon
