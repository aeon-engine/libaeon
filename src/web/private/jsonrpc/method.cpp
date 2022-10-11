// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/web/jsonrpc/method.h>

namespace aeon::web::jsonrpc
{

method::method(common::string name, signature func)
    : name_{std::move(name)}
    , func_{std::move(func)}
{
}

auto method::name() const noexcept -> const common::string &
{
    return name_;
}

auto method::operator()(const ptree::property_tree &params) const -> result
{
    return func_(params);
}

} // namespace aeon::web::jsonrpc
