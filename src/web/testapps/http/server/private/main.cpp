// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/web/http/routable_http_server.h>
#include <aeon/web/http/http_jsonrpc_route.h>
#include <aeon/web/http/static_route.h>
#include <asio/io_context.hpp>
#include "http_server_settings.h"

using namespace aeon;

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
    asio::io_context service;

    web::http::routable_http_server handler{service, 8080};

    auto route = std::make_unique<web::http::http_jsonrpc_route>("/api");
    route->register_method({"subtract", [](const auto &params) {
                                return web::jsonrpc::result{
                                    ptree::property_tree{params.object_value().at("a").integer_value() -
                                                         params.object_value().at("b").integer_value()}};
                            }});
    route->register_method({"raise_error", []([[maybe_unused]] const auto &params) {
                                return web::jsonrpc::result{1337, "This is an error!"};
                            }});

    handler.get_session().add_route(std::move(route));
    handler.get_session().add_route(std::make_unique<web::http::static_route>("/", AEON_HTTP_SERVER_WWWROOT_PATH));

    service.run();
    return 0;
}
