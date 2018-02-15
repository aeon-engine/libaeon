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

#include <aeon/sockets/http/static_route.h>
#include <aeon/sockets/http/http_server_socket.h>
#include <aeon/sockets/http/http_server_session.h>
#include <aeon/sockets/http/request.h>
#include <aeon/sockets/http/constants.h>
#include <aeon/streams/file_stream.h>
#include <aeon/common/string.h>
#include <cassert>

namespace aeon::sockets::http
{

auto detail::to_url_path(const std::string &path) -> std::string
{
    return common::string::replace_copy(path, "\\", "/");
}

static_route::static_route(const std::string &mount_point, const std::filesystem::path &base_path)
    : static_route(mount_point, base_path, detail::default_files)
{
}

static_route::static_route(const std::string &mount_point, const std::filesystem::path &base_path,
                           const std::vector<std::string> &default_files)
    : route{mount_point}
    , base_path_{std::filesystem::canonical(base_path)}
    , default_files_{default_files}
{
    assert(std::filesystem::is_directory(base_path));
}

void static_route::on_http_request(http_server_socket &source, http_server_session &session, const request &request)
{
    std::filesystem::path uri_path(request.get_uri());

    if (uri_path.u8string().empty())
    {
        bool default_file_found = false;
        for (const auto &default_file : default_files_)
        {
            const auto test_uri_path = base_path_ / uri_path / default_file;

            if (std::filesystem::exists(test_uri_path))
            {
                default_file_found = true;
                uri_path = default_file;
                break;
            }
        }

        if (!default_file_found)
        {
            source.respond_default(status_code::not_found);
            return;
        }
    }

    const auto full_path = std::filesystem::canonical(base_path_ / uri_path);

    if (!std::filesystem::exists(full_path))
    {
        source.respond_default(status_code::not_found);
        return;
    }

    if (!std::filesystem::is_regular_file(full_path))
    {
        source.respond_default(status_code::not_found);
        return;
    }

    // If the full path does not contain the base path, then it's trying to
    // access outside of base path (higher directories). Denied.
    if (!common::string::begins_withsv(full_path.u8string(), base_path_.u8string()))
    {
        source.respond_default(status_code::forbidden);
        return;
    }

    auto extension = full_path.extension().u8string();

    if (extension.empty())
        extension = full_path.stem().u8string();

    const auto mime_type = session.find_mime_type_by_extension(extension);

    streams::file_stream file_stream(full_path);
    source.respond(mime_type, file_stream);
}

} // namespace aeon::sockets::http
