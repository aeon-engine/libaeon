// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include <aeon/ast/entity.h>
#include <iostream>

namespace aeon::ast
{

void print_basic(const ast_entity &entity);
void print_basic(const ast_entity &entity, std::ostream &stream);

} // namespace aeon::ast
