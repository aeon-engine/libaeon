#ifndef aeon_logger_simple_backend_h__
#define aeon_logger_simple_backend_h__

namespace aeon
{
namespace logger
{

class simple_backend : public base_backend
{
public:
    virtual void log(std::string &&message, log_level level)
    {
        std::cout << "[" << log_level_str[static_cast<int>(level)] << "]: " << message << std::endl;
    }
};

} // namespace logger
} // namespace aeon

#endif // aeon_logger_simple_backend_h__

