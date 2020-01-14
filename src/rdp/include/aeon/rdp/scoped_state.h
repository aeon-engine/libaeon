// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <aeon/rdp/parser.h>
#include <string_view>

namespace aeon::rdp
{

class scoped_state final
{
public:
    explicit scoped_state(parser &parser) noexcept
        : parser_{parser}
        , prev_{parser.current_}
        , restore_{true}
    {
    }

    ~scoped_state() noexcept
    {
        if (restore_)
            parser_.current_ = prev_;
    }

    scoped_state(const scoped_state &) noexcept = delete;
    auto operator=(const scoped_state &) noexcept -> scoped_state & = delete;

    scoped_state(scoped_state &&) noexcept = delete;
    auto operator=(scoped_state &&) noexcept -> scoped_state & = delete;

    void accept() noexcept
    {
        restore_ = false;
    }

private:
    parser &parser_;
    std::string_view::const_iterator prev_;
    bool restore_;
};

} // namespace aeon::rdp
