// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#include <aeon/sockets/jsonrpc/method.h>

namespace aeon::sockets::jsonrpc
{

method::method(std::string name, signature func)
    : name_{std::move(name)}
    , func_{std::move(func)}
{
}

auto method::name() const noexcept -> const std::string &
{
    return name_;
}

auto method::operator()(const json11::Json &params) const -> result
{
    return func_(params);
}

} // namespace aeon::sockets::jsonrpc
