// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include <aeon/reflection/ast/namespace.h>
#include <clang-c/Index.h>
#include <memory>

namespace aeon::reflection::internal
{

void entity_visitor(const CXCursor cursor, ast::ast_entity &ns);

} // namespace aeon::reflection::internal
