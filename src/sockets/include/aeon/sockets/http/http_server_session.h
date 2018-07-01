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

#include <map>
#include <string>

namespace aeon::sockets::http
{

class http_server_session
{
public:
    explicit http_server_session();
    virtual ~http_server_session();

    http_server_session(http_server_session &&) = default;
    auto operator=(http_server_session &&) -> http_server_session & = default;

    http_server_session(const http_server_session &) = delete;
    auto operator=(const http_server_session &) -> http_server_session & = delete;

    /*!
     * Register a mime type to a file extension. If the extension already had a
     * mime type, it will be overwritten.
     */
    void register_mine_type(const std::string &extension, const std::string &mime_type);

    /*!
     * Attempt to find a suitable mime type for a given file extension.
     * Returns the default mime type if this could not be found.
     */
    auto find_mime_type_by_extension(const std::string &extension) const -> std::string;

    /*!
     * Attempt to find a suitable file extension for a mime type. Returns an empty
     * string if this could not be found. Since this method is used considerably less
     * than finding a mime type by extension, it's performance will be relatively bad.
     */
    auto find_extension_by_mime_type(const std::string &mime_type) const -> std::string;

    /*!
     * Set the default mime type. This is the mime type that will be used if the
     * file extension is not registered, and thus unknown.
     */
    void set_default_mime_type(const std::string &mime_type);

    /*!
     * Get the default mime type. This is the mime type that will be used if the
     * file extension is not registered, and thus unknown.
     */
    auto get_default_mime_type() const noexcept -> const std::string &;

private:
    /*!
     * Register internal mime types.
     */
    void register_mime_types();

    std::map<std::string, std::string> mime_types_;
    std::string default_mime_type_;
};

} // namespace aeon::sockets::http
