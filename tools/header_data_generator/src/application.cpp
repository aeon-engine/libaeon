// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include "application.h"
#include <aeon/streams/devices/file_device.h>
#include <aeon/streams/stream_reader.h>
#include <aeon/streams/stream_writer.h>
#include <aeon/common/commandline_parser.h>
#include <aeon/common/string.h>
#include <filesystem>
#include <iostream>

namespace aeon::header_data_generator
{

constexpr auto exe_name = "aeon_reflection_generator";
constexpr auto default_namespace_name = "aeon::data";
constexpr auto default_data_type = "std::uint8_t";

constexpr auto max_hex_bytes_per_line = 16;

[[nodiscard]] auto parse_arguments(common::commandline_parser &parser, int argc, char *argv[])
{
    parser.add_positional("source_file", "The source header file for which to generate reflection data.");
    parser.add_positional("dest_file", "The destination for the generated reflection data.");
    parser.add_option("v", "Verbose.");
    parser.add_option("h", "Show help text.");
    parser.add_argument("n", "Set a custom name for the namespace. The default is aeon::data");
    parser.add_argument(
        "d", "Set a custom name for the data variable. The default is to base this on the source file name.");
    parser.add_argument("t", "Override the std::uint8_t type with a custom one (must be 8 bits)");

    return parser.parse(argc, argv);
}

[[nodiscard]] auto generate_variable_name(const std::filesystem::path &path)
{
    auto filename = path.filename().string();
    common::string::trim(filename);
    common::string::replace<char>(filename, " ", "-");
    common::string::replace<char>(filename, ".", "_");
    common::string::to_lower(filename);
    return filename;
}

[[nodiscard]] auto read_source_data(const std::filesystem::path &source)
{
    streams::file_source_device src_device{source};
    const streams::stream_reader src_reader{src_device};
    return src_reader.read_to_vector<std::uint8_t>();
}

void generate(const std::filesystem::path &source, const std::filesystem::path &destination,
              const std::string_view namespace_name, const std::string_view data_name, const std::string_view data_type,
              bool verbose)
{
    if (verbose)
        std::cout << "Reading source file.\n";

    const auto data = read_source_data(source);

    if (verbose)
        std::cout << "Opening destination file for writing.\n";

    streams::file_sink_device dst_device{destination};
    streams::stream_writer dst_writer{dst_device};

    if (verbose)
        std::cout << "Generating header...\n";

    dst_writer << "// This is a generated file. Do not modify.\n\n";
    dst_writer << "#pragma once\n\n";
    dst_writer << "#include <cstdint>\n\n";
    dst_writer << "namespace " << namespace_name << "\n";
    dst_writer << "{\n\n";

    dst_writer << "constexpr static " << data_type << " " << data_name << "[] =\n";
    dst_writer << "{\n";

    dst_writer << "    ";

    auto hex_bytes_per_line = 0;
    for (const auto b : data)
    {
        dst_writer << "0x" << common::string::uint8_to_hex_string(b) << ", ";

        if (++hex_bytes_per_line >= max_hex_bytes_per_line)
        {
            dst_writer << "\n    ";
            hex_bytes_per_line = 0;
        }
    }

    dst_writer << "\n};\n\n";

    dst_writer << "} // namespace " << namespace_name << "\n";

    dst_device.flush();

    if (verbose)
        std::cout << "Done.\n";
}

auto application::main(const int argc, char *argv[]) noexcept -> int // NOLINT(bugprone-exception-escape)
{
    common::commandline_parser commandline_parser;
    auto args = parse_arguments(commandline_parser, argc, argv);

    if (!args)
    {
        std::cerr << "Invalid arguments.\n";
        commandline_parser.print_help_text(exe_name);
        return 1;
    }

    if (args.has_option("h"))
    {
        commandline_parser.print_help_text(exe_name);
        return 0;
    }

    const auto source_file = std::filesystem::path{args.positional(0)};
    const auto destination_file = std::filesystem::path{args.positional(1)};

    if (!std::filesystem::exists(source_file))
    {
        std::cerr << "Source file does not exist.\n";
        return 1;
    }

    const auto namespace_name = args.get_argument("n", default_namespace_name);
    const auto generated_variable_name = generate_variable_name(source_file);
    const auto data_name = args.get_argument("d", generated_variable_name);
    const auto data_type = args.get_argument("t", default_data_type);
    const auto verbose = args.has_option("v");

    generate(source_file, destination_file, namespace_name, data_name, data_type, verbose);

    return 0;
}

} // namespace aeon::header_data_generator
