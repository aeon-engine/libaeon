// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#include <aeon/clang/reflection.h>
#include "clang_translation_unit.h"
#include "entity_visitor.h"

namespace aeon::clang
{

parser::parser() = default;

auto parser::parse(const std::filesystem::path &path, const parser_settings &settings) const -> ast::global_namespace
{
    ast::global_namespace unit;
    parse(path, unit, settings);
    return unit;
}

void parser::parse(const std::filesystem::path &path, ast::global_namespace &ns, const parser_settings &settings) const
{
    const auto args = settings.args();
    const internal::clang_translation_unit translation_unit{path, args};
    internal::entity_visitor(translation_unit.get_cursor(), ns);
}

} // namespace aeon::clang
