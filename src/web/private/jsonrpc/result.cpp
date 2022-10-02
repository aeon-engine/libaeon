// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/web/jsonrpc/result.h>

namespace aeon::web::jsonrpc
{

result::result(ptree::property_tree &&result)
    : id_{std::nullopt}
    , result_type_{rpc_result_type::result}
    , result_{std::move(result)}
    , error_code_{}
    , error_description_{}
{
}

result::result(const int error_code, std::u8string description)
    : id_{std::nullopt}
    , result_type_{rpc_result_type::error}
    , result_{}
    , error_code_{error_code}
    , error_description_{std::move(description)}
{
}

result::result(ptree::property_tree &&result, const std::optional<int> id)
    : id_{id}
    , result_type_{rpc_result_type::result}
    , result_{std::move(result)}
    , error_code_{}
    , error_description_{}
{
}

result::result(const int error_code, std::u8string description, const std::optional<int> id)
    : id_{id}
    , result_type_{rpc_result_type::error}
    , result_{}
    , error_code_{error_code}
    , error_description_{std::move(description)}
{
}

} // namespace aeon::web::jsonrpc
