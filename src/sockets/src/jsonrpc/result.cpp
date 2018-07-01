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

#include <aeon/sockets/jsonrpc/result.h>

namespace aeon::sockets::jsonrpc
{

result::result(json11::Json &&result)
    : id_{std::nullopt}
    , result_type_{rpc_result_type::result}
    , result_{std::move(result)}
    , error_code_{}
    , error_description_{}
{
}

result::result(const int error_code, std::string description)
    : id_{std::nullopt}
    , result_type_{rpc_result_type::error}
    , result_{}
    , error_code_{error_code}
    , error_description_{std::move(description)}
{
}

result::result(json11::Json &&result, const std::optional<int> id)
    : id_{id}
    , result_type_{rpc_result_type::result}
    , result_{std::move(result)}
    , error_code_{}
    , error_description_{}
{
}

result::result(const int error_code, std::string description, const std::optional<int> id)
    : id_{id}
    , result_type_{rpc_result_type::error}
    , result_{}
    , error_code_{error_code}
    , error_description_{std::move(description)}
{
}

} // namespace aeon::sockets::jsonrpc
