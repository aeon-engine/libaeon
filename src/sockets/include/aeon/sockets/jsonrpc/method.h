// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include <aeon/sockets/jsonrpc/result.h>
#include <string>
#include <functional>
#include <json11.hpp>

namespace aeon::sockets::jsonrpc
{

class method
{
public:
    using signature = std::function<result(const json11::Json &)>;

    method(std::string name, signature func);
    ~method() = default;

    method(method &&) = default;
    auto operator=(method &&) -> method & = default;

    method(const method &) = default;
    auto operator=(const method &) -> method & = default;

    auto name() const noexcept -> const std::string &;
    auto operator()(const json11::Json &params) const -> result;

private:
    std::string name_;
    signature func_;
};

} // namespace aeon::sockets::jsonrpc
