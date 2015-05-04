#ifndef aeon_logger_stream_sink_h__
#define aeon_logger_stream_sink_h__

namespace aeon
{
namespace logger
{

class stream_sink : public log_sink
{
public:
    stream_sink(aeon::streams::stream_ptr stream) :
        stream_(stream)
    {
    }

private:
    virtual void log(const std::string &message, aeon::logger::log_level level)
    {
        aeon::streams::stream_writer writer(*stream_);

        stream_->write((const std::uint8_t *) "[", 1);

        std::string log_level_string = aeon::logger::log_level_str[static_cast<int>(level)];
        writer << log_level_string;

        stream_->write((const std::uint8_t *) "]: ", 3);
        
        writer.write_line(message);
    }

    aeon::streams::stream_ptr stream_;
};

} // namespace logger
} // namespace aeon

#endif // aeon_logger_stream_sink_h__
