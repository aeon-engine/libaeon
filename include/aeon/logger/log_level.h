#ifndef aeon_logger_log_level_h__
#define aeon_logger_log_level_h__

namespace aeon
{
namespace logger
{

enum class log_level : int
{
    trace   = 0,
    debug   = 1,
    message = 2,
    warning = 3,
    error   = 4,
    fatal   = 5
};

static const char *log_level_str[] =
{
    "trace",
    "debug",
    "message",
    "warning",
    "error",
    "fatal"
};

} // namespace logger
} // namespace aeon

#endif // aeon_logger_log_level_h__
