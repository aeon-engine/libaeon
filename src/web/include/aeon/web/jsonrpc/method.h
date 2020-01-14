// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <aeon/web/jsonrpc/result.h>
#include <aeon/ptree/ptree.h>
#include <string>
#include <functional>

namespace aeon::web::jsonrpc
{

class method
{
public:
    using signature = std::function<result(const ptree::property_tree &)>;

    method(std::string name, signature func);
    ~method() = default;

    method(method &&) noexcept = default;
    auto operator=(method &&) noexcept -> method & = default;

    method(const method &) = default;
    auto operator=(const method &) -> method & = default;

    [[nodiscard]] auto name() const noexcept -> const std::string &;
    auto operator()(const ptree::property_tree &params) const -> result;

private:
    std::string name_;
    signature func_;
};

} // namespace aeon::web::jsonrpc
