// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <string>
#include <vector>

namespace aeon::web::http::detail
{

static const auto content_length_key = u8"content-length";
static const auto content_type_key = u8"content-type";

static const auto default_response_content_type = u8"text/plain";

static const auto http_version_string = std::u8string{u8"HTTP/1.1"};

static const auto default_file_mime_type = std::u8string{u8"application/octet-stream"};

static const auto default_files = std::vector<std::u8string>{u8"index.html", u8"index.htm"};

static const auto hidden_files = std::vector<std::u8string>{u8".ds_store", u8"thumbs.db"};

} // namespace aeon::web::http::detail
