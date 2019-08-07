// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#include <aeon/clang/ast_parser.h>
#include <aeon/clang/translation_unit.h>
#include <aeon/clang/ast_entity_visitor.h>

namespace aeon::clang
{

ast_parser::ast_parser() = default;

auto ast_parser::parse(const std::filesystem::path &path, const parser_settings &settings) const
    -> ast::global_namespace
{
    ast::global_namespace unit;
    parse(path, unit, settings);
    return unit;
}

void ast_parser::parse(const std::filesystem::path &path, ast::global_namespace &ns,
                       const parser_settings &settings) const
{
    const auto args = settings.args();
    const translation_unit translation_unit{path, args};
    ast_entity_visitor(translation_unit.get_cursor(), ns);
}

} // namespace aeon::clang
