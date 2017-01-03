/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2017 Robin Degen
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains the property of
 * Robin Degen and its suppliers, if any. The intellectual and technical
 * concepts contained herein are proprietary to Robin Degen and its suppliers
 * and may be covered by U.S. and Foreign Patents, patents in process, and are
 * protected by trade secret or copyright law. Dissemination of this
 * information or reproduction of this material is strictly forbidden unless
 * prior written permission is obtained from Robin Degen.
 */

#pragma once

namespace aeon
{
namespace sockets
{

class line_protocol_handler : public tcp_server<line_protocol_handler>::protocol_handler
{
public:
    line_protocol_handler(asio::ip::tcp::socket socket)
        : tcp_server<line_protocol_handler>::protocol_handler(std::move(socket))
    {
    }

    virtual ~line_protocol_handler() = default;

    void on_data(std::uint8_t *data, std::size_t size) override
    {
        circular_buffer_.write(data, size);

        for (std::size_t i = 0; i < size; ++i)
        {
            if (data[i] == '\n')
            {
                streams::stream_reader<streams::circular_buffer_stream<AEON_TCP_SOCKET_MAX_BUFF_LEN>> reader(
                    circular_buffer_);
                on_line(reader.read_line());
            }
        }
    }

    virtual void on_line(const std::string &line) = 0;

private:
    streams::circular_buffer_stream<AEON_TCP_SOCKET_MAX_BUFF_LEN> circular_buffer_;
};

} // namespace sockets
} // namespace aeon
