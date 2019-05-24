// Copyright (c) 2012-2019 Robin Degen

#include <aeon/reflection/basic_printer.h>
#include <aeon/reflection/ast/namespace.h>
#include <aeon/reflection/ast/struct.h>
#include <aeon/reflection/ast/union.h>
#include <aeon/reflection/ast/class.h>
#include <aeon/reflection/ast/enum.h>
#include <aeon/reflection/ast/field.h>
#include <aeon/reflection/ast/method.h>
#include <aeon/reflection/ast/function.h>
#include <aeon/reflection/ast/constructor.h>
#include <aeon/reflection/ast/destructor.h>

namespace aeon::reflection
{

struct ast_basic_print_visitor
{
    explicit ast_basic_print_visitor(std::ostream &stream)
        : stream_{stream}
        , depth_{0}
    {
    }

    void operator()(const ast::ast_namespace &entity, const int depth)
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

    void operator()(const ast::ast_struct &entity, const int depth)
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

    void operator()(const ast::ast_union &entity, const int depth)
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

    void operator()(const ast::ast_class &entity, const int depth)
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

    void operator()(const ast::ast_enum &entity, const int depth)
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

    void operator()(const ast::ast_field &entity, const int depth)
    {
        indent();
        stream_ << entity.type() << ' ' << entity.name() << ";\n";
    }

    void operator()(const ast::ast_method &entity, const int depth)
    {
        operator()(entity.as<ast::ast_function>(), depth);
    }

    void operator()(const ast::ast_function &entity, const int depth)
    {
        indent();
        stream_ << entity.return_type() << ' ' << entity.name() << '(';

        bool first = true;
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

    void operator()(const ast::ast_constructor &entity, const int depth)
    {
        indent();
        stream_ << entity.name() << '(';

        bool first = true;
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

    void operator()(const ast::ast_destructor &entity, const int depth)
    {
        indent();
        stream_ << entity.name() << "();\n";
    }

private:
    void indent()
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

} // namespace aeon::reflection
