// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/reflection/ast/entity.h>
#include <iostream>

namespace aeon::reflection
{

void print_basic(const ast::ast_entity &entity);
void print_basic(const ast::ast_entity &entity, std::ostream &stream);

} // namespace aeon::reflection
