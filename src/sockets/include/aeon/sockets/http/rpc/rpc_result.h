/*
 * Copyright (c) 2012-2018 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include <aeon/common/stdoptional.h>
#include <json11.hpp>
#include <string>

namespace aeon::sockets::http::rpc
{

enum class rpc_result_type
{
    result,
    error
};

class rpc_result
{
    friend class http_json_rpc_route;

public:
    explicit rpc_result(json11::Json &&result);
    explicit rpc_result(const int error_code, const std::string &description);

    ~rpc_result() = default;

    rpc_result(rpc_result &&) = default;
    auto operator=(rpc_result &&) -> rpc_result & = default;

    rpc_result(const rpc_result &) = default;
    auto operator=(const rpc_result &) -> rpc_result & = default;

    auto id() const
    {
        return id_;
    }

    auto has_id() const
    {
        return id_.has_value();
    }

    auto type() const
    {
        return result_type_;
    }

    auto &result() const
    {
        return result_;
    }

    auto error_code() const
    {
        return error_code_;
    }

    auto &error_description() const
    {
        return error_description_;
    }

private:
    explicit rpc_result(json11::Json &&result, const std::optional<int> id);
    explicit rpc_result(const int error_code, const std::string &description, const std::optional<int> id);

    void set_id(const std::optional<int> id)
    {
        id_ = id;
    }

    std::optional<int> id_;
    rpc_result_type result_type_;
    json11::Json result_;
    int error_code_;
    std::string error_description_;
};

} // namespace aeon::sockets::http::rpc
