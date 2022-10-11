// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/common/string.h>
#include <vector>

namespace aeon::web::http::detail
{

static const auto content_length_key = "content-length";
static const auto content_type_key = "content-type";

static const auto default_response_content_type = "text/plain";

static const auto http_version_string = common::string{"HTTP/1.1"};

static const auto default_file_mime_type = common::string{"application/octet-stream"};

static const auto default_files = std::vector<common::string>{"index.html", "index.htm"};

static const auto hidden_files = std::vector<common::string>{".ds_store", "thumbs.db"};

} // namespace aeon::web::http::detail
