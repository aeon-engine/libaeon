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

#include <aeon/curl.h>

namespace aeon
{
namespace curl
{

easy_wrapper::easy_wrapper()
    : curl_(nullptr)
{
    global_wrapper_ = global_wrapper::get();

    curl_ = curl_easy_init();

    if (!curl_)
        throw easy_init_exception();

    if (curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, &easy_wrapper::static_read_event_) != CURLE_OK)
        throw easy_wrapper_exception();

    if (curl_easy_setopt(curl_, CURLOPT_WRITEDATA, this) != CURLE_OK)
        throw easy_wrapper_exception();
}

easy_wrapper::~easy_wrapper()
{
    if (curl_)
        curl_easy_cleanup(curl_);

    curl_ = nullptr;
    global_wrapper_ = nullptr;
}

void easy_wrapper::get(const std::string &url, easy_wrapper_read_event on_read,
                       long milliseconds /*= AEON_CURL_DEFAULT_TIMEOUT_MS*/)
{
    if (!curl_ || url.empty() || !on_read || milliseconds == 0)
        throw easy_wrapper_exception();

    if (curl_easy_setopt(curl_, CURLOPT_TIMEOUT_MS, milliseconds) != CURLE_OK)
        throw easy_wrapper_exception();

    if (curl_easy_setopt(curl_, CURLOPT_URL, url.c_str()) != CURLE_OK)
        throw easy_wrapper_exception();

    read_event_ = on_read;

    if (curl_easy_perform(curl_) != CURLE_OK)
        throw easy_wrapper_exception();
}

size_t easy_wrapper::static_read_event_(void *buffer, size_t size, size_t nmemb, easy_wrapper *wrapper)
{
    return wrapper->read_event_(buffer, size * nmemb);
}

} // namespace curl
} // namespace aeon
