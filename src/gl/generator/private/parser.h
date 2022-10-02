// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/ptree/xml_dom/xml_document.h>
#include "model.h"
#include <filesystem>

namespace aeon::gl::generator
{

class parser final
{
public:
    explicit parser(const std::filesystem::path &path);
    ~parser() = default;

    parser(const parser &) = delete;
    auto operator=(const parser &) -> parser & = delete;

    parser(parser &&) noexcept = delete;
    auto operator=(parser &&) noexcept -> parser & = delete;

    [[nodiscard]] auto definition() const -> const opengl_definition &;

private:
    void parse_type_definitions();
    void parse_enum_definitions();
    void parse_function_definitions();

    ptree::property_tree ptree_;
    ptree::xml_dom::xml_document document_;
    opengl_definition definition_;
};

} // namespace aeon::gl::generator
