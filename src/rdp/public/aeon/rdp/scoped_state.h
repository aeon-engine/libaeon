// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/rdp/parser.h>
#include <string_view>

namespace aeon::rdp
{

template <common::concepts::string_view_like T>
class scoped_state final
{
public:
    explicit scoped_state(parser<T> &parser) noexcept
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

    scoped_state(const scoped_state<T> &) noexcept = delete;
    auto operator=(const scoped_state<T> &) noexcept -> scoped_state<T> & = delete;

    scoped_state(scoped_state<T> &&) noexcept = delete;
    auto operator=(scoped_state<T> &&) noexcept -> scoped_state<T> & = delete;

    void accept() noexcept
    {
        restore_ = false;
    }

private:
    parser<T> &parser_;
    typename parser<T>::iterator prev_;
    bool restore_;
};

} // namespace aeon::rdp
