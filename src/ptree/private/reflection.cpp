// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/ptree/reflection.h>

namespace aeon::ptree
{

[[nodiscard]] auto to_reflection_object(const reflection::reflection_info &reflection_info, const property_tree &pt)
    -> std::unique_ptr<reflection::reflection_object>
{
    if (!pt.is_object())
        throw ptree_exception{};

    auto obj = reflection_info.create();

    if (!obj)
        throw ptree_exception{};

    const auto &field_info = reflection_info.get_field_info();

    const auto &pt_object = pt.object_value();

    for (const auto &field : field_info)
    {
        const auto field_name_str = field.name();
        const auto result = pt_object.find(common::string{field_name_str});

        if (result == std::end(pt_object))
            continue;

        if (field.type() == "std::int64_t")
        {
            if (!result->second.is_integer())
                throw ptree_exception{};

            field.set(*obj, result->second.integer_value());
        }
        else if (field.type() == "int")
        {
            if (!result->second.is_integer())
                throw ptree_exception{};

            field.set(*obj, static_cast<int>(result->second.integer_value()));
        }
        else if (field.type() == "float")
        {
            if (!result->second.is_double())
                throw ptree_exception{};

            field.set(*obj, static_cast<float>(result->second.double_value()));
        }
        else if (field.type() == "double")
        {
            if (!result->second.is_double())
                throw ptree_exception{};

            field.set(*obj, result->second.double_value());
        }
        else if (field.type() == "bool")
        {
            if (!result->second.is_bool())
                throw ptree_exception{};

            field.set(*obj, result->second.bool_value());
        }
        else if (field.type() == "aeon::common::string")
        {
            if (!result->second.is_string())
                throw ptree_exception{};

            field.set(*obj, result->second.string_value());
        }
        else if (field.type() == "aeon::common::uuid")
        {
            if (!result->second.is_uuid())
                throw ptree_exception{};

            field.set(*obj, result->second.uuid_value());
        }
        else if (field.type() == "std::vector<std::uint8_t>")
        {
            if (!result->second.is_blob())
                throw ptree_exception{};

            field.set(*obj, result->second.blob_value());
        }
        else
            throw ptree_exception{};
    }

    return obj;
}

auto from_reflection_object(const reflection::reflection_object &obj,
                            const reflection::reflection_info &reflection_info) -> property_tree
{
    object pt_obj;

    const auto &field_info = reflection_info.get_field_info();

    for (const auto &field : field_info)
    {
        const auto field_name = common::string{field.name()};

        if (field.type() == "std::int64_t")
        {
            pt_obj.insert(field_name, field.get<std::int64_t>(obj));
        }
        else if (field.type() == "int")
        {
            pt_obj.insert(field_name, field.get<int>(obj));
        }
        else if (field.type() == "float")
        {
            pt_obj.insert(field_name, field.get<float>(obj));
        }
        else if (field.type() == "double")
        {
            pt_obj.insert(field_name, field.get<double>(obj));
        }
        else if (field.type() == "bool")
        {
            pt_obj.insert(field_name, field.get<bool>(obj));
        }
        else if (field.type() == "aeon::common::string")
        {
            pt_obj.insert(field_name, field.get<common::string>(obj));
        }
        else if (field.type() == "aeon::common::uuid")
        {
            pt_obj.insert(field_name, field.get<common::uuid>(obj));
        }
        else if (field.type() == "std::vector<std::uint8_t>")
        {
            pt_obj.insert(field_name, field.get<std::vector<std::uint8_t>>(obj));
        }
        else
            throw ptree_exception{};
    }

    return pt_obj;
}

} // namespace aeon::ptree
