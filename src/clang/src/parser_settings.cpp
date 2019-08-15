// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#include <aeon/clang/parser_settings.h>
#include <reflection_path.h>

namespace aeon::clang
{

parser_settings::parser_settings(const cpp_standard standard)
{
    // Make sure clang knows we're parsing C++, even if we only provide a header file
    args_.emplace_back("-x");
    args_.emplace_back("c++");

    switch (standard)
    {
        case cpp_standard::cpp17:
            args_.emplace_back("-std=c++17");
            break;
        case cpp_standard::cpp2a:
            args_.emplace_back("-std=c++2a");
            break;
    }

    add_define("__AEON_REFLECTION__");
    add_include_path(AEON_REFLECTION_INCLUDE_DIR);
}

void parser_settings::add_argument(std::string arg)
{
    args_.push_back(std::move(arg));
}

void parser_settings::add_include_path(const std::filesystem::path &path)
{
    args_.emplace_back("-I" + path.u8string());
}

void parser_settings::add_include_paths(const std::vector<std::filesystem::path> &include_paths)
{
    for (const auto &path : include_paths)
        add_include_path(path);
}

void parser_settings::add_define(const std::string &define)
{
    args_.emplace_back("-D" + define);
}

} // namespace aeon::clang
