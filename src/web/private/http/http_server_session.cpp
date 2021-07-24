// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/web/http/http_server_session.h>
#include <aeon/web/http/constants.h>
#include <aeon/common/container.h>

namespace aeon::web::http
{

http_server_session::http_server_session()
    : mime_types_{}
    , default_mime_type_{detail::default_file_mime_type}
{
    register_mime_types();
}

http_server_session::~http_server_session() = default;

void http_server_session::register_mine_type(const std::u8string &extension, const std::u8string &mime_type)
{
    mime_types_.emplace(extension, mime_type);
}

auto http_server_session::find_mime_type_by_extension(const std::u8string &extension) const -> std::u8string
{
    const auto result = mime_types_.find(extension);

    if (result != mime_types_.end())
        return result->second;

    return detail::default_file_mime_type;
}

auto http_server_session::find_extension_by_mime_type(const std::u8string &mime_type) const -> std::u8string
{
    const auto result = common::container::find_in_map_by_value(mime_types_, mime_type);

    if (result != mime_types_.end())
        return result->second;

    return u8"";
}

void http_server_session::set_default_mime_type(const std::u8string &mime_type)
{
    default_mime_type_ = mime_type;
}

auto http_server_session::get_default_mime_type() const noexcept -> const std::u8string &
{
    return default_mime_type_;
}

void http_server_session::register_mime_types()
{
    mime_types_.emplace(u8".7z", u8"application/x-7z-compressed");
    mime_types_.emplace(u8".aac", u8"audio/aac");
    mime_types_.emplace(u8".asm", u8"text/plain");
    mime_types_.emplace(u8".avi", u8"video/x-msvideo");
    mime_types_.emplace(u8".bin", u8"application/octet-stream");
    mime_types_.emplace(u8".bmp", u8"image/bmp");
    mime_types_.emplace(u8".bz", u8"application/x-bzip");
    mime_types_.emplace(u8".bz2", u8"application/x-bzip2");
    mime_types_.emplace(u8".c", u8"text/plain");
    mime_types_.emplace(u8".cc", u8"text/plain");
    mime_types_.emplace(u8".cmake", u8"text/plain");
    mime_types_.emplace(u8".com", u8"application/octet-stream");
    mime_types_.emplace(u8".cpp", u8"text/plain");
    mime_types_.emplace(u8".cs", u8"text/plain");
    mime_types_.emplace(u8".css", u8"text/css");
    mime_types_.emplace(u8".cxx", u8"text/plain");
    mime_types_.emplace(u8".dll", u8"application/octet-stream");
    mime_types_.emplace(u8".doc", u8"application/msword");
    mime_types_.emplace(u8".docx", u8"application/vnd.openxmlformats-officedocument.wordprocessingml.document");
    mime_types_.emplace(u8".dot", u8"application/msword");
    mime_types_.emplace(u8".dylib", u8"application/octet-stream");
    mime_types_.emplace(u8".epub", u8"application/epub+zip");
    mime_types_.emplace(u8".exe", u8"application/octet-stream");
    mime_types_.emplace(u8".f", u8"text/plain");
    mime_types_.emplace(u8".f77", u8"text/plain");
    mime_types_.emplace(u8".f90", u8"text/plain");
    mime_types_.emplace(u8".gif", u8"image/gif");
    mime_types_.emplace(u8".glsl", u8"text/plain");
    mime_types_.emplace(u8".gz", u8"application/x-gzip");
    mime_types_.emplace(u8".gzip", u8"application/x-gzip");
    mime_types_.emplace(u8".h", u8"text/plain");
    mime_types_.emplace(u8".hh", u8"text/plain");
    mime_types_.emplace(u8".hpp", u8"text/plain");
    mime_types_.emplace(u8".htm", u8"text/html");
    mime_types_.emplace(u8".html", u8"text/html");
    mime_types_.emplace(u8".htmls", u8"text/html");
    mime_types_.emplace(u8".ico", u8"image/x-icon");
    mime_types_.emplace(u8".ini", u8"text/plain");
    mime_types_.emplace(u8".jar", u8"application/java-archive");
    mime_types_.emplace(u8".java", u8"text/plain");
    mime_types_.emplace(u8".jfif", u8"image/jpeg");
    mime_types_.emplace(u8".jpe", u8"image/jpeg");
    mime_types_.emplace(u8".jpeg", u8"image/jpeg");
    mime_types_.emplace(u8".jpg", u8"image/jpeg");
    mime_types_.emplace(u8".js", u8"application/x-javascript");
    mime_types_.emplace(u8".json", u8"application/json");
    mime_types_.emplace(u8".kar", u8"audio/midi");
    mime_types_.emplace(u8".latex", u8"application/x-latex");
    mime_types_.emplace(u8".lib", u8"application/octet-stream");
    mime_types_.emplace(u8".m", u8"text/plain");
    mime_types_.emplace(u8".m1v", u8"video/mpeg");
    mime_types_.emplace(u8".m2a", u8"audio/mpeg");
    mime_types_.emplace(u8".m2v", u8"audio/mpeg");
    mime_types_.emplace(u8".m3u", u8"audio/x-mpequrl");
    mime_types_.emplace(u8".mid", u8"audio/midi");
    mime_types_.emplace(u8".midi", u8"audio/midi");
    mime_types_.emplace(u8".mime", u8"www/mime");
    mime_types_.emplace(u8".mm", u8"application/base64");
    mime_types_.emplace(u8".mod", u8"audio/mod");
    mime_types_.emplace(u8".mov", u8"video/quicktime");
    mime_types_.emplace(u8".mp2", u8"video/mpeg");
    mime_types_.emplace(u8".mp3", u8"audio/mpeg");
    mime_types_.emplace(u8".mpa", u8"audio/mpeg");
    mime_types_.emplace(u8".mpeg", u8"video/mpeg");
    mime_types_.emplace(u8".mpga", u8"audio/mpeg");
    mime_types_.emplace(u8".mpjg", u8"video/x-motion-jpeg");
    mime_types_.emplace(u8".o", u8"application/octet-stream");
    mime_types_.emplace(u8".ogg", u8"audio/ogg");
    mime_types_.emplace(u8".p", u8"text/plain");
    mime_types_.emplace(u8".pdf", u8"application/pdf");
    mime_types_.emplace(u8".pl", u8"text/plain");
    mime_types_.emplace(u8".png", u8"image/png");
    mime_types_.emplace(u8".ppt", u8"application/vnd.ms-powerpoint");
    mime_types_.emplace(u8".pptx", u8"application/vnd.openxmlformats-officedocument.presentationml.presentation");
    mime_types_.emplace(u8".py", u8"text/plain");
    mime_types_.emplace(u8".rar", u8"application/x-rar-compressed");
    mime_types_.emplace(u8".rmi", u8"audio/midi");
    mime_types_.emplace(u8".rt", u8"text/richtext");
    mime_types_.emplace(u8".rtf", u8"application/rtf");
    mime_types_.emplace(u8".rtf", u8"text/richtext");
    mime_types_.emplace(u8".s", u8"text/plain");
    mime_types_.emplace(u8".s3m", u8"audio/s3m");
    mime_types_.emplace(u8".sh", u8"application/x-sh");
    mime_types_.emplace(u8".so", u8"application/octet-stream");
    mime_types_.emplace(u8".svg", u8"image/svg+xml");
    mime_types_.emplace(u8".swf", u8"application/x-shockwave-flash");
    mime_types_.emplace(u8".text", u8"text/plain");
    mime_types_.emplace(u8".tif", u8"image/tiff");
    mime_types_.emplace(u8".tiff", u8"image/tiff");
    mime_types_.emplace(u8".ttf", u8"font/ttf");
    mime_types_.emplace(u8".txt", u8"text/plain");
    mime_types_.emplace(u8".wav", u8"audio/wave");
    mime_types_.emplace(u8".weba", u8"audio/webm");
    mime_types_.emplace(u8".webm", u8"video/webm");
    mime_types_.emplace(u8".webp", u8"image/webp");
    mime_types_.emplace(u8".xhtml", u8"application/xhtml+xml");
    mime_types_.emplace(u8".xls", u8"application/vnd.ms-excel");
    mime_types_.emplace(u8".xlsx", u8"application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");
    mime_types_.emplace(u8".xml", u8"application/xml");
    mime_types_.emplace(u8".z", u8"application/x-compressed");
    mime_types_.emplace(u8".zip", u8"application/zip");

    mime_types_.emplace(u8"Makefile", u8"text/plain");
}

} // namespace aeon::web::http
