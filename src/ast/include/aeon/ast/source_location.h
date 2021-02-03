// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <filesystem>

namespace aeon::ast
{

class ast_source_location final
{
public:
    explicit ast_source_location(std::filesystem::path path) noexcept
        : path_{std::move(path)}
        , line_{0u}
        , column_{0u}
    {
    }

    explicit ast_source_location(std::filesystem::path path, const unsigned int line,
                                 const unsigned int column) noexcept
        : path_{std::move(path)}
        , line_{line}
        , column_{column}
    {
    }

    ~ast_source_location() = default;

    ast_source_location(const ast_source_location &) = delete;
    auto operator=(const ast_source_location &) -> ast_source_location & = delete;

    ast_source_location(ast_source_location &&) noexcept = default;
    auto operator=(ast_source_location &&) noexcept -> ast_source_location & = default;

    [[nodiscard]] const auto &path() const noexcept
    {
        return path_;
    }

    [[nodiscard]] auto line() const noexcept
    {
        return line_;
    }

    [[nodiscard]] auto column() const noexcept
    {
        return column_;
    }

private:
    std::filesystem::path path_;
    unsigned int line_;
    unsigned int column_;
};

} // namespace aeon::ast
