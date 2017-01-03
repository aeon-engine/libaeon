/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2017 Robin Degen
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

#pragma once

namespace aeon
{
namespace curl
{

class url_downloader : public utility::noncopyable
{
public:
    url_downloader();
    ~url_downloader();

    void download(const std::string &url, const std::string &dest_path);

    std::size_t read_event_(aeon::streams::file_stream &dest_stream, void *buffer, std::size_t size);

    easy_wrapper_ptr wrapper_;
};

} // namespace curl
} // namespace aeon
