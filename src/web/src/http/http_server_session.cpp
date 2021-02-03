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

void http_server_session::register_mine_type(const std::string &extension, const std::string &mime_type)
{
    mime_types_.emplace(extension, mime_type);
}

auto http_server_session::find_mime_type_by_extension(const std::string &extension) const -> std::string
{
    const auto result = mime_types_.find(extension);

    if (result != mime_types_.end())
        return result->second;

    return detail::default_file_mime_type;
}

auto http_server_session::find_extension_by_mime_type(const std::string &mime_type) const -> std::string
{
    const auto result = common::container::find_in_map_by_value(mime_types_, mime_type);

    if (result != mime_types_.end())
        return result->second;

    return "";
}

void http_server_session::set_default_mime_type(const std::string &mime_type)
{
    default_mime_type_ = mime_type;
}

auto http_server_session::get_default_mime_type() const noexcept -> const std::string &
{
    return default_mime_type_;
}

void http_server_session::register_mime_types()
{
    mime_types_.emplace(".7z", "application/x-7z-compressed");
    mime_types_.emplace(".aac", "audio/aac");
    mime_types_.emplace(".asm", "text/plain");
    mime_types_.emplace(".avi", "video/x-msvideo");
    mime_types_.emplace(".bin", "application/octet-stream");
    mime_types_.emplace(".bmp", "image/bmp");
    mime_types_.emplace(".bz", "application/x-bzip");
    mime_types_.emplace(".bz2", "application/x-bzip2");
    mime_types_.emplace(".c", "text/plain");
    mime_types_.emplace(".cc", "text/plain");
    mime_types_.emplace(".cmake", "text/plain");
    mime_types_.emplace(".com", "application/octet-stream");
    mime_types_.emplace(".cpp", "text/plain");
    mime_types_.emplace(".cs", "text/plain");
    mime_types_.emplace(".css", "text/css");
    mime_types_.emplace(".cxx", "text/plain");
    mime_types_.emplace(".dll", "application/octet-stream");
    mime_types_.emplace(".doc", "application/msword");
    mime_types_.emplace(".docx", "application/vnd.openxmlformats-officedocument.wordprocessingml.document");
    mime_types_.emplace(".dot", "application/msword");
    mime_types_.emplace(".dylib", "application/octet-stream");
    mime_types_.emplace(".epub", "application/epub+zip");
    mime_types_.emplace(".exe", "application/octet-stream");
    mime_types_.emplace(".f", "text/plain");
    mime_types_.emplace(".f77", "text/plain");
    mime_types_.emplace(".f90", "text/plain");
    mime_types_.emplace(".gif", "image/gif");
    mime_types_.emplace(".glsl", "text/plain");
    mime_types_.emplace(".gz", "application/x-gzip");
    mime_types_.emplace(".gzip", "application/x-gzip");
    mime_types_.emplace(".h", "text/plain");
    mime_types_.emplace(".hh", "text/plain");
    mime_types_.emplace(".hpp", "text/plain");
    mime_types_.emplace(".htm", "text/html");
    mime_types_.emplace(".html", "text/html");
    mime_types_.emplace(".htmls", "text/html");
    mime_types_.emplace(".ico", "image/x-icon");
    mime_types_.emplace(".ini", "text/plain");
    mime_types_.emplace(".jar", "application/java-archive");
    mime_types_.emplace(".java", "text/plain");
    mime_types_.emplace(".jfif", "image/jpeg");
    mime_types_.emplace(".jpe", "image/jpeg");
    mime_types_.emplace(".jpeg", "image/jpeg");
    mime_types_.emplace(".jpg", "image/jpeg");
    mime_types_.emplace(".js", "application/x-javascript");
    mime_types_.emplace(".json", "application/json");
    mime_types_.emplace(".kar", "audio/midi");
    mime_types_.emplace(".latex", "application/x-latex");
    mime_types_.emplace(".lib", "application/octet-stream");
    mime_types_.emplace(".m", "text/plain");
    mime_types_.emplace(".m1v", "video/mpeg");
    mime_types_.emplace(".m2a", "audio/mpeg");
    mime_types_.emplace(".m2v", "audio/mpeg");
    mime_types_.emplace(".m3u", "audio/x-mpequrl");
    mime_types_.emplace(".mid", "audio/midi");
    mime_types_.emplace(".midi", "audio/midi");
    mime_types_.emplace(".mime", "www/mime");
    mime_types_.emplace(".mm", "application/base64");
    mime_types_.emplace(".mod", "audio/mod");
    mime_types_.emplace(".mov", "video/quicktime");
    mime_types_.emplace(".mp2", "video/mpeg");
    mime_types_.emplace(".mp3", "audio/mpeg");
    mime_types_.emplace(".mpa", "audio/mpeg");
    mime_types_.emplace(".mpeg", "video/mpeg");
    mime_types_.emplace(".mpga", "audio/mpeg");
    mime_types_.emplace(".mpjg", "video/x-motion-jpeg");
    mime_types_.emplace(".o", "application/octet-stream");
    mime_types_.emplace(".ogg", "audio/ogg");
    mime_types_.emplace(".p", "text/plain");
    mime_types_.emplace(".pdf", "application/pdf");
    mime_types_.emplace(".pl", "text/plain");
    mime_types_.emplace(".png", "image/png");
    mime_types_.emplace(".ppt", "application/vnd.ms-powerpoint");
    mime_types_.emplace(".pptx", "application/vnd.openxmlformats-officedocument.presentationml.presentation");
    mime_types_.emplace(".py", "text/plain");
    mime_types_.emplace(".rar", "application/x-rar-compressed");
    mime_types_.emplace(".rmi", "audio/midi");
    mime_types_.emplace(".rt", "text/richtext");
    mime_types_.emplace(".rtf", "application/rtf");
    mime_types_.emplace(".rtf", "text/richtext");
    mime_types_.emplace(".s", "text/plain");
    mime_types_.emplace(".s3m", "audio/s3m");
    mime_types_.emplace(".sh", "application/x-sh");
    mime_types_.emplace(".so", "application/octet-stream");
    mime_types_.emplace(".svg", "image/svg+xml");
    mime_types_.emplace(".swf", "application/x-shockwave-flash");
    mime_types_.emplace(".text", "text/plain");
    mime_types_.emplace(".tif", "image/tiff");
    mime_types_.emplace(".tiff", "image/tiff");
    mime_types_.emplace(".ttf", "font/ttf");
    mime_types_.emplace(".txt", "text/plain");
    mime_types_.emplace(".wav", "audio/wave");
    mime_types_.emplace(".weba", "audio/webm");
    mime_types_.emplace(".webm", "video/webm");
    mime_types_.emplace(".webp", "image/webp");
    mime_types_.emplace(".xhtml", "application/xhtml+xml");
    mime_types_.emplace(".xls", "application/vnd.ms-excel");
    mime_types_.emplace(".xlsx", "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");
    mime_types_.emplace(".xml", "application/xml");
    mime_types_.emplace(".z", "application/x-compressed");
    mime_types_.emplace(".zip", "application/zip");

    mime_types_.emplace("Makefile", "text/plain");
}

} // namespace aeon::web::http
