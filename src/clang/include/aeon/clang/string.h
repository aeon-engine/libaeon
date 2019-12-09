// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include <clang-c/CXString.h>
#include <string>

namespace aeon::clang
{

class scoped_cxstring final
{
public:
    explicit scoped_cxstring(const CXString str) noexcept;

    ~scoped_cxstring();

    scoped_cxstring(const scoped_cxstring &) = delete;
    auto operator=(const scoped_cxstring &) -> scoped_cxstring & = delete;

    scoped_cxstring(scoped_cxstring &&other) noexcept;
    auto operator=(scoped_cxstring &&other) noexcept -> scoped_cxstring &;

    [[nodiscard]] auto to_std_string() const -> std::string;

private:
    void dispose() noexcept;

    CXString str_;
};

/*!
 * Convert the given CXString to an std::string and dispose it
 */
[[nodiscard]] inline auto to_std_string(const CXString str) -> std::string
{
    const scoped_cxstring string{str};
    return string.to_std_string();
}

} // namespace aeon::clang
