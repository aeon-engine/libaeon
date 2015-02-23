#ifndef line_protocol_handler_h__
#define line_protocol_handler_h__

namespace aeon
{
namespace sockets
{

class line_protocol_handler :
    public tcp_server<line_protocol_handler>::protocol_handler
{
public:
    line_protocol_handler(boost::asio::ip::tcp::socket socket) :
        tcp_server<line_protocol_handler>::protocol_handler(std::move(socket))
    {
    }

    void on_data(std::uint8_t *data, std::size_t size)
    {
        circular_buffer_.write(data, size);

        for (std::size_t i = 0; i < size; ++i)
        {
            if (data[i] == '\n')
            {
                aeon::streams::stream_reader reader(circular_buffer_);
                on_line(reader.read_line());
            }
        }
    }

    virtual void on_line(const std::string &line) = 0;

private:
    aeon::streams::circular_buffer_stream<AEON_TCP_SOCKET_MAX_BUFF_LEN> circular_buffer_;
};

} // namespace sockets
} // namespace aeon

#endif // line_protocol_handler_h__
