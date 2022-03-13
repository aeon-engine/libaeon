#include <aeon/common/commandline_parser.h>
#include <aeon/common/string_utils.h>
#include <aeon/common/fmtflags.h>
#include <iostream>

namespace aeon::common
{

commandline_parser::commandline_parser() = default;

commandline_parser::~commandline_parser() = default;

void commandline_parser::add_positional(std::string name, std::string description)
{
    positional_.emplace(std::move(name), std::move(description));
}

void commandline_parser::add_option(const std::string &name, std::string description)
{
    std::string arg_name;

    if (std::size(name) == 1)
        arg_name = "-" + name;
    else
        arg_name = "--" + name;

    options_.emplace(std::move(arg_name), std::move(description));
}

void commandline_parser::add_argument(const std::string &name, std::string description)
{
    std::string arg_name;

    if (std::size(name) == 1)
        arg_name = "-" + name;
    else
        arg_name = "--" + name;

    arguments_.emplace(std::move(arg_name), std::move(description));
}

auto commandline_parser::parse(const int argc, char *argv[]) const -> commandline_parse_result
{
    std::vector<std::string_view> arguments;

    arguments.reserve(argc - 1);
    for (auto i = 1; i < argc; ++i)
        arguments.emplace_back(argv[i]);

    return parse(arguments);
}

auto commandline_parser::parse(const std::vector<std::string_view> &args) const -> commandline_parse_result
{
    if (std::size(args) < std::size(positional_))
        return {};

    auto itr = std::begin(args);

    std::vector<std::string_view> positional;
    for (auto i = 0u; i < std::size(positional_); ++i)
    {
        positional.emplace_back(*itr);
        ++itr;
    }

    unordered_flatset<std::string_view> options;
    unordered_flatmap<std::string_view, std::string_view> arguments;

    for (; itr != std::end(args); ++itr)
    {
        if (is_option(*itr))
        {
            options.insert(string_utils::char_stripped_leftsv(*itr, '-'));
        }
        else if (is_argument(*itr))
        {
            const auto arg_name = string_utils::char_stripped_leftsv(*itr, '-');
            ++itr;

            if (itr == std::end(args))
                return {};

            arguments.insert(arg_name, *itr);
        }
        else
        {
            return {};
        }
    }

    return commandline_parse_result{std::move(positional), std::move(options), std::move(arguments)};
}

void commandline_parser::print_help_text(const std::string_view exe_name) const
{
    scoped_fmtflags flags{std::cout};

    std::cout << exe_name << ' ';
    for (const auto &arg : positional_)
    {
        std::cout << arg.first << ' ';
    }

    if (!arguments_.empty())
    {
        std::cout << "[args] ";
    }

    if (!options_.empty())
    {
        std::cout << "[options] ";
    }

    std::cout << '\n';

    constexpr auto arg_column_width = 25;

    if (!positional_.empty())
    {
        std::cout << "\nPositional arguments: \n";
    }

    for (const auto &arg : positional_)
    {
        std::cout << std::left << std::setw(arg_column_width) << arg.first << std::right << std::setw(10) << arg.second
                  << '\n';
    }

    if (!arguments_.empty())
    {
        std::cout << "\nArguments: \n";
    }

    for (const auto &arg : arguments_)
    {
        auto arg_str = arg.first + " value";
        std::cout << std::left << std::setw(arg_column_width) << arg_str << std::right << std::setw(10) << arg.second
                  << '\n';
    }

    if (!options_.empty())
    {
        std::cout << "\nOptions: \n";
    }

    for (const auto &arg : options_)
    {
        std::cout << std::left << std::setw(arg_column_width) << arg.first << std::right << std::setw(10) << arg.second
                  << '\n';
    }
}

auto commandline_parser::is_option(const std::string_view arg) const noexcept -> bool
{
    return options_.contains(std::string{arg});
}

auto commandline_parser::is_argument(const std::string_view arg) const noexcept -> bool
{
    return arguments_.contains(std::string{arg});
}

} // namespace aeon::common
