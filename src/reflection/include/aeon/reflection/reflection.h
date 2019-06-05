// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include <aeon/reflection/parser_settings.h>
#include <aeon/reflection/ast/global_namespace.h>
#include <aeon/common/stdfilesystem.h>
#include <memory>

/*!
 * I'll remember the good things how can you forget all the years that we shared in our way
 * Things were changing my life, taking your place in my life and our time drifting away.
 *
 * - On Reflection, Gentle Giant (1975)
 */
namespace aeon::reflection
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

    auto parse(const std::filesystem::path &path, const parser_settings &settings = parser_settings{}) const
        -> ast::global_namespace;
    void parse(const std::filesystem::path &path, ast::global_namespace &ns,
               const parser_settings &settings = parser_settings{}) const;
};

} // namespace aeon::reflection
