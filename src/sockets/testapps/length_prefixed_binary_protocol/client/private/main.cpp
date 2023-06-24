// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/sockets/length_prefixed_binary_protocol_socket.h>
#include <aeon/sockets/tcp_client.h>
#include <aeon/common/hexdump.h>

using namespace aeon;

class binary_socket : public sockets::length_prefixed_binary_protocol_socket<std::uint32_t>
{
public:
    /*!
     * Client socket ctor
     */
    explicit binary_socket(asio::io_context &service)
        : length_prefixed_binary_protocol_socket<std::uint32_t>{service}
    {
    }

    /*!
     * Server socket ctor
     */
    explicit binary_socket(asio::ip::tcp::socket socket)
        : length_prefixed_binary_protocol_socket<std::uint32_t>{std::move(socket)}
    {
    }

    void on_frame(const streams::memory_view_device<std::vector<std::byte>> &frame) final
    {
        common::hexdump::pretty_print(stdout, std::data(frame.data()), std::size(frame.data()));

        sockets::length_prefixed_binary_frame<std::uint32_t> reply;
        reply << static_cast<std::uint32_t>(2);
        reply << static_cast<std::uint32_t>(0x12345678);
        reply << static_cast<std::uint32_t>(0xabadcafe);
        send_frame(std::move(reply));
    }

    void on_connected() final
    {
        std::cout << "Connected to server.\n";

        sockets::length_prefixed_binary_frame<std::uint32_t> frame;
        frame << static_cast<std::uint32_t>(2);
        frame << static_cast<std::uint32_t>(0x12345678);
        frame << static_cast<std::uint32_t>(0xabadcafe);
        send_frame(std::move(frame));
    }

    void on_disconnected() final
    {
        std::cout << "On Disconnected.\n";
    }
};

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
    asio::io_context service;
    sockets::tcp_client<binary_socket> client{service};

    client.connect("127.0.0.1", 7777);
    service.run();

    return 0;
}
