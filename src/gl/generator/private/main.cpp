// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/streams/devices/file_device.h>
#include <aeon/streams/dynamic_stream.h>
#include <aeon/streams/stream_reader.h>
#include <aeon/streams/stream_writer.h>
#include "parser.h"
#include "generator.h"
#include <opengl_registry_info.h>
#include <filesystem>

namespace aeon::gl::generator
{

#define VERSION_FILE_PATH OPENGL_REGISTRY_DESTINATION_PATH "version.txt"

/*!
 * Check if the OpenGL code needs to be regenerated based on the version file.
 */
[[nodiscard]] auto requires_code_generation()
{
    if (!std::filesystem::exists(VERSION_FILE_PATH))
        return true;

    auto stream = streams::make_dynamic_stream(streams::file_source_device{VERSION_FILE_PATH});

    const streams::stream_reader reader{stream};
    return reader.read_to_string() != OPENGL_REGISTRY_VERSION;
}

void write_version_file()
{
    auto stream = streams::make_dynamic_stream(streams::file_sink_device{VERSION_FILE_PATH});

    streams::stream_writer writer{stream};
    writer << OPENGL_REGISTRY_VERSION;
}

} // namespace aeon::gl::generator

void generate_header(const std::filesystem::path &source, const std::filesystem::path &header_destination,
                     const std::filesystem::path &inline_header_destination)
{
    const aeon::gl::generator::parser p{source};
    const aeon::gl::generator::generator g{p.definition()};
    g.write_header(header_destination);
    g.write_inline_header(inline_header_destination);
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
    try
    {
        if (!(argc == 2 && std::string{argv[1]} == std::string{"--force"}))
        {
            if (std::filesystem::exists(OPENGL_REGISTRY_DESTINATION_PATH "/aeon_opengl.h") &&
                std::filesystem::exists(OPENGL_REGISTRY_DESTINATION_PATH "/aeon_opengl_impl.h") &&
                std::filesystem::exists(OPENGL_REGISTRY_DESTINATION_PATH "/aeon_wgl.h") &&
                std::filesystem::exists(OPENGL_REGISTRY_DESTINATION_PATH "/aeon_wgl_impl.h") &&
                std::filesystem::exists(OPENGL_REGISTRY_DESTINATION_PATH "/aeon_glx.h") &&
                std::filesystem::exists(OPENGL_REGISTRY_DESTINATION_PATH "/aeon_glx_impl.h") &&
                !aeon::gl::generator::requires_code_generation())
            {
                std::cout << "Registry headers are up to date. Skipping generation step.\n";
                return 0;
            }
        }
        else
        {
            std::cout << "Forcing regeneration.\n";
        }

        std::cout << "(Re)Generating registry headers.\n";

        generate_header(OPENGL_REGISTRY_XML_PATH "/gl.xml", OPENGL_REGISTRY_DESTINATION_PATH "/aeon_opengl.h",
                        OPENGL_REGISTRY_DESTINATION_PATH "/aeon_opengl_impl.h");
        generate_header(OPENGL_REGISTRY_XML_PATH "/wgl.xml", OPENGL_REGISTRY_DESTINATION_PATH "/aeon_wgl.h",
                        OPENGL_REGISTRY_DESTINATION_PATH "/aeon_wgl_impl.h");
        generate_header(OPENGL_REGISTRY_XML_PATH "/glx.xml", OPENGL_REGISTRY_DESTINATION_PATH "/aeon_glx.h",
                        OPENGL_REGISTRY_DESTINATION_PATH "/aeon_glx_impl.h");

        aeon::gl::generator::write_version_file();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
