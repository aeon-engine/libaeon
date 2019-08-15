// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include <aeon/common/container.h>
#include <filesystem>
#include <vector>
#include <string>

namespace aeon::clang
{

enum class cpp_standard
{
    cpp17,
    cpp2a,
    latest = cpp2a
};

class parser_settings final
{
public:
    explicit parser_settings(const cpp_standard standard = cpp_standard::cpp17);
    ~parser_settings() = default;

    parser_settings(const parser_settings &) = delete;
    auto operator=(const parser_settings &) -> parser_settings & = delete;

    parser_settings(parser_settings &&o) noexcept = default;
    auto operator=(parser_settings &&o) noexcept -> parser_settings & = default;

    void add_argument(std::string arg);
    void add_include_path(const std::filesystem::path &path);
    void add_include_paths(const std::vector<std::filesystem::path> &include_paths);
    void add_define(const std::string &define);

    [[nodiscard]] auto args() const
    {
        return common::container::transform<const char *>(args_, [](const auto &arg) { return std::data(arg); });
    }

private:
    std::vector<std::string> args_;
};

} // namespace aeon::clang
