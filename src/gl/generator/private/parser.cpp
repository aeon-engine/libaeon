// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include "parser.h"

#include <aeon/ptree/serialization/serialization_xml.h>
#include <aeon/streams/dynamic_stream.h>
#include <aeon/streams/devices/file_device.h>
#include <aeon/common/timer.h>
#include <iostream>

namespace aeon::gl::generator
{

namespace detail
{

[[nodiscard]] auto load_registry(const std::filesystem::path &path)
{
    const common::timer timer;
    std::cout << "Parsing registry " << path.filename() << "... ";
    auto stream = streams::make_dynamic_stream(streams::file_source_device{path});
    auto result = ptree::serialization::from_xml(stream);

    std::cout << " Took: " << std::fixed << timer.get_time_difference<double>() << " seconds.\n";

    return result;
}

[[nodiscard]] auto get_attribute_string(const std::map<std::u8string, variant::converting_variant> &attributes,
                                        const std::u8string &key) -> std::u8string
{
    const auto result = attributes.find(key);
    if (result == std::end(attributes))
        return u8"";

    return result->second.get_value<std::u8string>();
}

} // namespace detail

parser::parser(const std::filesystem::path &path)
    : ptree_{detail::load_registry(path)}
    , document_{ptree_}
    , definition_{path.stem().u8string()}
{
    common::timer timer;

    std::cout << "Parsing type definitions... ";
    parse_type_definitions();
    std::cout << " Took: " << std::fixed << timer.get_time_difference<double>() << " seconds.\n";

    timer.reset();

    std::cout << "Parsing enum definitions... ";
    parse_enum_definitions();
    std::cout << " Took: " << std::fixed << timer.get_time_difference<double>() << " seconds.\n";

    timer.reset();

    std::cout << "Parsing function definitions... ";
    parse_function_definitions();
    std::cout << " Took: " << std::fixed << timer.get_time_difference<double>() << " seconds.\n";
}

auto parser::definition() const -> const opengl_definition &
{
    return definition_;
}

void parser::parse_type_definitions()
{
    const auto types_nodes = document_.child(u8"registry").child(u8"types").children();

    for (const auto &t : types_nodes)
    {
        const auto type_children = t.children();

        std::u8string code_line;

        for (const auto &tc : type_children)
        {
            if (tc.has_name() && tc.name() == u8"name")
                code_line += tc.child().value() + u8" ";

            if (tc.has_value())
                code_line += tc.value() + u8" ";
        }

        common::string_utils::replace(code_line, u8"&lt;", u8"<");
        common::string_utils::replace(code_line, u8"&gt;", u8">");

        if (!std::empty(code_line))
            definition_.add_additional_code(common::string_utils::trimmed(code_line));
    }
}

void parser::parse_enum_definitions()
{
    const auto enums_nodes = document_.child(u8"registry").children(u8"enums");

    for (const auto &e : enums_nodes)
    {
        const auto e_children = e.children();
        for (const auto &ec : e_children)
        {
            if (ec.has_name() && ec.name() == u8"unused")
                continue;

            const auto attributes = ec.attributes();
            const auto api = detail::get_attribute_string(attributes, u8"api");

            if (api == u8"gles2")
                continue;

            auto name = detail::get_attribute_string(attributes, u8"name");
            auto value = detail::get_attribute_string(attributes, u8"value");

            definition_.add_enum_value(std::move(name), std::move(value));
        }
    }
}

void parser::parse_function_definitions()
{
    const auto function_nodes = document_.child(u8"registry").child(u8"commands").children();

    for (const auto &command_node : function_nodes)
    {
        const auto proto_node = command_node.child(u8"proto").children();

        std::u8string return_type;
        std::u8string name;

        for (const auto &tc : proto_node)
        {
            if (std::empty(name))
            {
                if (tc.has_value())
                    return_type += tc.value() + u8" ";
            }

            if (tc.has_name())
            {
                if (tc.name() == u8"ptype")
                    return_type += tc.child().value() + u8" ";
                else if (tc.name() == u8"name")
                    name = tc.child().value();
            }
        }

        opengl_function function{common::string_utils::trimmed(name), common::string_utils::trimmed(return_type)};

        const auto params_nodes = command_node.children(u8"param");
        for (const auto &pc : params_nodes)
        {
            std::u8string param_name;
            std::u8string type_definition;
            for (const auto &pv : pc.children())
            {
                if (pv.has_value())
                    type_definition += pv.value() + u8" ";

                if (pv.has_name())
                {
                    if (pv.name() == u8"name")
                        param_name = pv.child().value();
                    else
                        type_definition += pv.child().value() + u8" ";
                }
            }

            function.add_argument(common::string_utils::trimmed(param_name),
                                  common::string_utils::trimmed(type_definition));
        }

        definition_.add_function(std::move(function));
    }
}

} // namespace aeon::gl::generator
