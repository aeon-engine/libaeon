#ifndef aeon_logger_log_sink_h__
#define aeon_logger_log_sink_h__

namespace aeon
{
namespace logger
{

class log_sink
{
public:
    virtual void log(const std::string &message, log_level level) = 0;
};

typedef std::shared_ptr<log_sink> log_sink_ptr;

} // namespace logger
} // namespace aeon

#endif // aeon_logger_log_sink_h__
