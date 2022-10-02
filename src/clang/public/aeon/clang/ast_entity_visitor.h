// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/ast/entity.h>
#include <clang-c/Index.h>

namespace aeon::clang
{

void ast_entity_visitor(const CXCursor cursor, ast::ast_entity &ns);

} // namespace aeon::clang
