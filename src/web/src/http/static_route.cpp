// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#include <aeon/web/http/static_route.h>
#include <aeon/web/http/http_server_socket.h>
#include <aeon/web/http/routable_http_server_session.h>
#include <aeon/web/http/url_encoding.h>
#include <aeon/web/http/request.h>
#include <aeon/web/http/constants.h>
#include <aeon/streams/devices/file_device.h>
#include <aeon/streams/dynamic_stream.h>
#include <aeon/common/string.h>
#include <cassert>

namespace aeon::web::http
{

auto detail::to_url_path(const std::string &path) -> std::string
{
    return common::string::replace_copy<char>(path, "\\", "/");
}

auto detail::is_image_extension(const std::string &extension) -> bool
{
    const auto extension_lower = common::string::to_lower_copy(extension);
    return extension_lower == ".jpg" || extension_lower == ".jpeg" || extension_lower == ".png" ||
           extension_lower == ".gif";
}

static_route::static_route(std::string mount_point, const std::filesystem::path &base_path)
    : static_route(std::move(mount_point), base_path, static_route_settings{})
{
}

static_route::static_route(std::string mount_point, const std::filesystem::path &base_path,
                           static_route_settings settings)
    : route{std::move(mount_point)}
    , base_path_{std::filesystem::canonical(base_path)}
    , settings_{std::move(settings)}
{
    assert(std::filesystem::is_directory(base_path));
}

static_route::~static_route() = default;

void static_route::on_http_request(http_server_socket &source, routable_http_server_session &session,
                                   const request &request)
{
    std::filesystem::path uri_path(request.get_uri());

    // If a directory was given, check the default files.
    if (std::filesystem::is_directory(base_path_ / uri_path))
        uri_path = get_path_for_default_files(uri_path);

    std::error_code error;
    const auto full_path = std::filesystem::canonical(base_path_ / uri_path, error);

    if (error || !std::filesystem::exists(full_path))
    {
        source.respond_default(status_code::not_found);
        return;
    }

    // If the full path does not contain the base path, then it's trying to
    // access outside of base path (higher directories). Denied.
    if (!common::string::begins_with(full_path.u8string(), base_path_.u8string()))
    {
        source.respond_default(status_code::forbidden);
        return;
    }

    if (std::filesystem::is_regular_file(full_path))
    {
        reply_file(source, session, full_path);
    }
    else
    {
        if (settings_.enable_listing)
        {
            reply_folder(source, session, full_path);
        }
        else
        {
            source.respond_default(status_code::not_found);
        }
    }
}

auto static_route::get_path_for_default_files(const std::filesystem::path &path) const -> std::filesystem::path
{
    auto uri_path = path;
    if (path.u8string().empty())
    {
        for (const auto &default_file : settings_.default_files)
        {
            const auto test_uri_path = base_path_ / path / default_file;

            if (std::filesystem::exists(test_uri_path))
            {
                uri_path = default_file;
                break;
            }
        }
    }

    return uri_path;
}

void static_route::reply_file(http_server_socket &source, routable_http_server_session &session,
                              const std::filesystem::path &file) const
{
    auto extension = file.extension().u8string();

    if (extension.empty())
        extension = file.stem().u8string();

    const auto mime_type = session.find_mime_type_by_extension(extension);

    auto file_stream = streams::make_dynamic_stream(streams::file_source_device{file});
    source.respond(mime_type, file_stream);
}

void static_route::reply_folder(http_server_socket &source, [[maybe_unused]] routable_http_server_session &session,
                                const std::filesystem::path &path) const
{
    const auto header_name = get_current_directory_header_name(path);
    const auto entries = get_directory_listing_entries(path);

    std::string reply = "<h1>";
    reply += header_name;
    reply += "</h1><hr><pre>";

    if (path != base_path_)
    {
        reply += generate_hyperlink_html("../", "../");
        reply += '\n';
    }

    bool display_full_thumbnails = false;

    if (settings_.detect_image_folder)
        display_full_thumbnails = is_image_folder(entries);

    if (display_full_thumbnails)
    {
        reply += '\n';

        auto image_per_line_count = 0;
        for (const auto &entry : entries)
        {
            std::string thumbnail_html = "<img src=\"";
            thumbnail_html += entry.display_name;
            thumbnail_html += R"(" width="128" style="margin:10px">)";

            reply += generate_hyperlink_html(thumbnail_html, entry.display_name);

            if (++image_per_line_count >= 10)
            {
                image_per_line_count = 0;
                reply += '\n';
            }
        }
    }
    else
    {
        for (const auto &entry : entries)
        {
            reply += generate_hyperlink_html(entry.display_name, entry.display_name);
            reply += '\n';
        }
    }

    reply += "</pre><hr>";

    source.respond("text/html", reply);
}

auto static_route::get_current_directory_header_name(const std::filesystem::path &path) const -> std::string
{
    return path.stem().u8string();
}

auto static_route::get_directory_listing_entries(const std::filesystem::path &path) const
    -> std::vector<directory_listing_entry>
{
    std::vector<directory_listing_entry> entries;
    for (const auto &file_entry : std::filesystem::directory_iterator(path))
    {
        directory_listing_entry entry;

        if (std::filesystem::is_regular_file(file_entry))
        {
            const auto filename = file_entry.path().filename().u8string();

            if (is_hidden_file(filename))
                continue;

            entry.is_directory = false;
            entry.display_name = filename;
        }
        else if (std::filesystem::is_directory(file_entry))
        {
            entry.is_directory = true;
            entry.display_name = file_entry.path().filename().u8string() + "/";
        }
        else // If it's not a regular file or folder... carry on.
        {
            continue;
        }

        entries.push_back(entry);
    }

    return entries;
}

auto static_route::is_image_folder(const std::vector<directory_listing_entry> &entries) const -> bool
{
    bool is_image_folder = true;

    for (const auto &entry : entries)
    {
        if (!detail::is_image_extension(std::filesystem::path(entry.display_name).extension().u8string()))
        {
            is_image_folder = false;
            break;
        }
    }

    return is_image_folder;
}

auto static_route::is_hidden_file(const std::string &filename) const -> bool
{
    const auto filename_str = common::string::to_lower_copy(filename);

    for (const auto &hidden_file : settings_.hidden_files)
    {
        if (filename_str == hidden_file)
            return true;
    }

    return false;
}

auto static_route::generate_hyperlink_html(const std::string &name, const std::string &destination) const -> std::string
{
    std::string reply = "<a href=\"";
    reply += url_encode(destination);
    reply += "\">";
    reply += name;
    reply += "</a>";
    return reply;
}

} // namespace aeon::web::http
