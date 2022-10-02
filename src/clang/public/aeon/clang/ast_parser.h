// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/clang/parser_settings.h>
#include <aeon/ast/global_namespace.h>
#include <filesystem>

namespace aeon::clang
{

class ast_parser
{
public:
    ast_parser();
    ~ast_parser() = default;

    ast_parser(const ast_parser &) = delete;
    auto operator=(const ast_parser &) -> ast_parser & = delete;

    ast_parser(ast_parser &&o) noexcept = delete;
    auto operator=(ast_parser &&o) noexcept -> ast_parser & = delete;

    [[nodiscard]] auto parse(const std::filesystem::path &path,
                             const parser_settings &settings = parser_settings{}) const -> ast::global_namespace;
    void parse(const std::filesystem::path &path, ast::global_namespace &ns,
               const parser_settings &settings = parser_settings{}) const;
};

} // namespace aeon::clang
