#ifndef aeon_logger_logger_h__
#define aeon_logger_logger_h__

#define AEON_LOG(log, level) log(level)
#define AEON_LOG_FATAL(log) AEON_LOG(log, aeon::logger::fatal)
#define AEON_LOG_ERROR(log) AEON_LOG(log, aeon::logger::error)
#define AEON_LOG_WARNING(log) AEON_LOG(log, aeon::logger::warning)
#define AEON_LOG_MESSAGE(log) AEON_LOG(log, aeon::logger::message)
#define AEON_LOG_DEBUG(log) AEON_LOG(log, aeon::logger::debug)
#define AEON_LOG_TRACE(log) AEON_LOG(log, aeon::logger::trace)

namespace aeon
{
namespace logger
{

class logger_stream
{
private:
    using endl_type = std::ostream&(std::ostream&);

public:
    logger_stream(base_backend &backend, log_level level) :
        backend_(backend),
        level_(level)
    {
    }

    void operator<<(endl_type endl)
    {
        std::string message = stream_.str();
        backend_.handle_log_(std::move(message), level_);
    }

    template<typename T>
    logger_stream &operator<<(const T& data)
    {
        stream_ << data;
        return *this;
    }
private:
    base_backend &backend_;
    log_level level_;
    std::stringstream stream_;
};

class logger
{
public:
    logger(base_backend &backend) :
        backend_(backend)
    {
    }

    logger(const logger&) = delete;

    logger_stream operator()(log_level level)
    {
        return logger_stream(backend_, level);
    }

private:
    base_backend &backend_;
};

} // namespace logger
} // namespace aeon

#endif // aeon_logger_logger_h__

