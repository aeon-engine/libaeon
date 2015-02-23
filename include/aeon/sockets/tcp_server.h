#ifndef aeon_sockets_tcp_server_h__
#define aeon_sockets_tcp_server_h__

namespace aeon
{
namespace sockets
{

template<typename socket_handler_type>
class tcp_server
{
public:
    class protocol_handler :
        public std::enable_shared_from_this<protocol_handler>
    {
    friend class tcp_server;
    public:
        protocol_handler(boost::asio::ip::tcp::socket socket) :
            socket_(std::move(socket))
        {
        }

        virtual void on_connected() = 0;
        virtual void on_disconnected() = 0;
        virtual void on_data(std::uint8_t *data, std::size_t size) = 0;
        virtual void on_error(boost::system::error_code ec) = 0;

        void send(stream_ptr stream)
        {
            std::vector<std::uint8_t> buffer(
                std::move(stream->read_to_vector()));

            memory_stream_ptr memorystream =
                std::make_shared<memory_stream>(std::move(buffer));
            send(memorystream);
        }

		void send(memory_stream_ptr stream)
        {
			send_data_queue_.push(stream);

			if (send_data_queue_.size() == 1)
				tcp_server_handle_write_();
        }

        void tcp_server_socket_start_()
        {
            tcp_server_handle_read_();
            on_connected();
        }

    private:
        void tcp_server_handle_read_()
        {
            auto self(protocol_handler::shared_from_this());

            socket_.async_read_some(
                boost::asio::buffer(
                    data_, AEON_TCP_SOCKET_MAX_BUFF_LEN),
                [self](boost::system::error_code ec,
                    std::size_t length)
                {
                    if(ec && ec != boost::asio::error::eof)
                        self->on_error(ec);

                    if(length > 0)
                    {
                        self->on_data(self->data_.data(), length);

                        if (!ec)
                            self->tcp_server_handle_read_();
                    }
                    else
                    {
                        self->on_disconnected();
                        self->socket_.shutdown(
                            boost::asio::ip::tcp::socket::shutdown_both, ec);
                        self->socket_.close();
                    }
                }
            );
        }

        void tcp_server_handle_write_()
        {
			if (send_data_queue_.empty())
				return;

			memory_stream_ptr buffer = send_data_queue_.front();
			auto self(protocol_handler::shared_from_this());

			boost::asio::async_write(
				socket_, boost::asio::buffer(buffer->data(), buffer->size()),
                [self, buffer](boost::system::error_code ec,
                    std::size_t /*length*/)
                {
					self->send_data_queue_.pop();

                    if (!ec)
                        self->tcp_server_handle_write_();
                }
            );
        }

        boost::asio::ip::tcp::socket socket_;
        std::array<std::uint8_t, AEON_TCP_SOCKET_MAX_BUFF_LEN> data_;
		std::queue<aeon::memory_stream_ptr> send_data_queue_;
    };

public:
    tcp_server(boost::asio::io_service &io_service, std::uint16_t port) :
        acceptor_(io_service, 
            boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
        socket_(io_service)
    {
        start_async_accept_();
    }

protected:
    void start_async_accept_()
    {
        acceptor_.async_accept(socket_,
            [this](boost::system::error_code ec)
            {
                if (!ec)
                {
                    std::make_shared<socket_handler_type>(
                        std::move(socket_))->tcp_server_socket_start_();
                }
                start_async_accept_();
            }
        );
    }

    boost::asio::ip::tcp::acceptor acceptor_;
    boost::asio::ip::tcp::socket socket_;
};

} // namespace sockets
} // namespace aeon

#endif // aeon_sockets_tcp_server_h__
