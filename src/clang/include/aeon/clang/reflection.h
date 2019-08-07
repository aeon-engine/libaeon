// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include <aeon/clang/parser_settings.h>
#include <aeon/ast/global_namespace.h>
#include <filesystem>

namespace aeon::clang
{

class parser
{
public:
    parser();
    ~parser() = default;

    parser(const parser &) = delete;
    auto operator=(const parser &) -> parser & = delete;

    parser(parser &&o) noexcept = delete;
    auto operator=(parser &&o) noexcept -> parser & = delete;

    [[nodiscard]] auto parse(const std::filesystem::path &path,
                             const parser_settings &settings = parser_settings{}) const -> ast::global_namespace;
    void parse(const std::filesystem::path &path, ast::global_namespace &ns,
               const parser_settings &settings = parser_settings{}) const;
};

} // namespace aeon::clang
