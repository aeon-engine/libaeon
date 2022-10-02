// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/streams/idynamic_stream.h>
#include "model.h"

namespace aeon::gl::generator
{

class generator final
{
public:
    explicit generator(const opengl_definition &definition);
    ~generator() = default;

    generator(const generator &) = delete;
    auto operator=(const generator &) -> generator & = delete;

    generator(generator &&) noexcept = delete;
    auto operator=(generator &&) noexcept -> generator & = delete;

    void write_header(const std::filesystem::path &path) const;
    void write_inline_header(const std::filesystem::path &path) const;

private:
    void generate_header(streams::idynamic_stream &output_file) const;
    void generate_footer(streams::idynamic_stream &output_file) const;

    void generate_header_additional_source_lines(streams::idynamic_stream &output_file) const;
    void generate_header_enum_definitions(streams::idynamic_stream &output_file) const;
    void generate_header_function_definitions(streams::idynamic_stream &output_file) const;

    void generate_inline_header_function_definitions(streams::idynamic_stream &output_file) const;
    void generate_inline_header_initialize_impl(streams::idynamic_stream &output_file) const;

    const opengl_definition &definition_;
};

} // namespace aeon::gl::generator
