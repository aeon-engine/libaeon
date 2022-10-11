// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/web/jsonrpc/result.h>
#include <aeon/ptree/ptree.h>
#include <aeon/common/string.h>
#include <functional>

namespace aeon::web::jsonrpc
{

class method
{
public:
    using signature = std::function<result(const ptree::property_tree &)>;

    method(common::string name, signature func);
    ~method() = default;

    method(method &&) noexcept = default;
    auto operator=(method &&) noexcept -> method & = default;

    method(const method &) = default;
    auto operator=(const method &) -> method & = default;

    [[nodiscard]] auto name() const noexcept -> const common::string &;
    auto operator()(const ptree::property_tree &params) const -> result;

private:
    common::string name_;
    signature func_;
};

} // namespace aeon::web::jsonrpc
