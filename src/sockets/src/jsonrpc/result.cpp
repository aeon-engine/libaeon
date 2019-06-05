// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

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
