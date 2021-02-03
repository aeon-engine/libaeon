// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/ast/basic_printer.h>
#include <aeon/ast/namespace.h>
#include <aeon/ast/struct.h>
#include <aeon/ast/union.h>
#include <aeon/ast/class.h>
#include <aeon/ast/enum.h>
#include <aeon/ast/field.h>
#include <aeon/ast/method.h>
#include <aeon/ast/function.h>
#include <aeon/ast/constructor.h>
#include <aeon/ast/destructor.h>

namespace aeon::ast
{

struct ast_basic_print_visitor
{
    explicit ast_basic_print_visitor(std::ostream &stream)
        : stream_{stream}
        , depth_{0}
    {
    }

    void operator()(const ast::ast_namespace &entity)
    {
        indent();
        stream_ << "namespace " << entity.name() << '\n';
        indent();
        stream_ << "{\n";

        ++depth_;
        entity.visit(*this, false);
        --depth_;

        indent();
        stream_ << "} // namespace " << entity.name() << '\n';
    }

    void operator()(const ast::ast_struct &entity)
    {
        indent();
        stream_ << "struct " << entity.name() << '\n';
        indent();
        stream_ << "{\n";

        ++depth_;
        entity.visit(*this, false);
        --depth_;

        indent();
        stream_ << "};\n";
    }

    void operator()(const ast::ast_union &entity)
    {
        indent();
        stream_ << "union " << entity.name() << '\n';
        indent();
        stream_ << "{\n";

        ++depth_;
        entity.visit(*this, false);
        --depth_;

        indent();
        stream_ << "};\n";
    }

    void operator()(const ast::ast_class &entity)
    {
        indent();
        stream_ << "class " << entity.name() << '\n';
        indent();
        stream_ << "{\n";

        ++depth_;
        entity.visit(*this, false);
        --depth_;

        indent();
        stream_ << "};\n";
    }

    void operator()(const ast::ast_enum &entity) const
    {
        indent();
        stream_ << "enum class " << entity.name() << '\n';
        indent();
        stream_ << "{\n";

        for (const auto &item : entity.constants())
        {
            stream_ << item << ",\n";
        }

        indent();
        stream_ << "};" << entity.name() << '\n';
    }

    void operator()(const ast::ast_field &entity) const
    {
        indent();
        stream_ << entity.type() << ' ' << entity.name() << ";\n";
    }

    void operator()(const ast::ast_method &entity) const
    {
        operator()(entity.as<ast::ast_function>());
    }

    void operator()(const ast::ast_function &entity) const
    {
        indent();
        stream_ << entity.return_type() << ' ' << entity.name() << '(';

        auto first = true;
        for (const auto &parameter : entity.parameters())
        {
            if (first)
            {
                stream_ << ',';
                first = false;
            }

            stream_ << parameter.type() << ' ' << parameter.name();
        }

        stream_ << ')' << ";\n";
    }

    void operator()(const ast::ast_constructor &entity) const
    {
        indent();
        stream_ << entity.name() << '(';

        auto first = true;
        for (const auto &parameter : entity.parameters())
        {
            if (first)
            {
                stream_ << ',';
                first = false;
            }

            stream_ << parameter.type() << ' ' << parameter.name();
        }

        stream_ << ')' << ";\n";
    }

    void operator()(const ast::ast_destructor &entity) const
    {
        indent();
        stream_ << entity.name() << "();\n";
    }

private:
    void indent() const
    {
        stream_ << std::string(depth_ * 4, ' ');
    }

    std::ostream &stream_;
    int depth_;
};

void print_basic(const ast::ast_entity &entity)
{
    print_basic(entity, std::cout);
}

void print_basic(const ast::ast_entity &entity, std::ostream &stream)
{
    entity.visit(ast_basic_print_visitor{stream}, false);
}

} // namespace aeon::ast
