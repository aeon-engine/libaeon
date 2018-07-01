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

#include <aeon/sockets/http/route.h>
#include <aeon/sockets/http/constants.h>
#include <aeon/common/stdfilesystem.h>
#include <string>
#include <vector>

namespace aeon::sockets::http
{

namespace detail
{
auto to_url_path(const std::string &path) -> std::string;
auto is_image_extension(const std::string &extension) -> bool;
} // namespace detail

struct static_route_settings
{
    static_route_settings(static_route_settings &&) = default;
    auto operator=(static_route_settings &&) -> static_route_settings & = default;

    static_route_settings(const static_route_settings &) = default;
    auto operator=(const static_route_settings &) -> static_route_settings & = default;

    // Default files that should be displayed when a directory is requested
    // For example: index.html, index.htm
    std::vector<std::string> default_files = detail::default_files;

    // Enable directory listing.
    bool enable_listing = true;

    // Detect if a folder contains only image files, and if so, display
    // the images as tiles instead. This is an experimental feature.
    bool detect_image_folder = false;

    // Files that should not be displayed when listing a directory.
    std::vector<std::string> hidden_files = detail::hidden_files;
};

class static_route : public route
{
public:
    explicit static_route(std::string mount_point, const std::filesystem::path &base_path);
    explicit static_route(std::string mount_point, const std::filesystem::path &base_path,
                          static_route_settings settings);
    virtual ~static_route();

    static_route(static_route &&) = default;
    auto operator=(static_route &&) -> static_route & = default;

    static_route(const static_route &) = delete;
    auto operator=(const static_route &) -> static_route & = delete;

private:
    struct directory_listing_entry
    {
        std::string display_name;
        bool is_directory = false;
    };

    void on_http_request(http_server_socket &source, routable_http_server_session &session,
                         const request &request) override;

    auto get_path_for_default_files(const std::filesystem::path &path) const -> std::filesystem::path;

    void reply_file(http_server_socket &source, routable_http_server_session &session,
                    const std::filesystem::path &file) const;
    void reply_folder(http_server_socket &source, routable_http_server_session &session,
                      const std::filesystem::path &path) const;

    auto get_current_directory_header_name(const std::filesystem::path &path) const -> std::string;
    auto get_directory_listing_entries(const std::filesystem::path &path) const -> std::vector<directory_listing_entry>;
    auto is_image_folder(const std::vector<directory_listing_entry> &entries) const -> bool;
    auto is_hidden_file(const std::string &filename) const -> bool;
    auto generate_hyperlink_html(const std::string &name, const std::string &destination) const -> std::string;

    std::filesystem::path base_path_;
    static_route_settings settings_;
};

} // namespace aeon::sockets::http
