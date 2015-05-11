#ifndef aeon_logger_simple_sink_backend_h__
#define aeon_logger_simple_sink_backend_h__

namespace aeon
{
namespace logger
{

class simple_sink_backend : public base_backend
{
public:
    simple_sink_backend() :
        base_backend(log_level::message)
    {
    }

    simple_sink_backend(log_level level) :
        base_backend(level)
    {
    }

    simple_sink_backend(const simple_sink_backend&) = delete;

    void add_sink(log_sink_ptr sink)
    {
        sinks_.insert(sink);
    }

    void remove_all_sinks()
    {
        sinks_.clear();
    }

private:
    virtual void log(std::string &&message, log_level level)
    {
        for (auto &sink : sinks_)
        {
            sink->log(message, level);
        }
    }

    std::set<log_sink_ptr> sinks_;
};

} // namespace logger
} // namespace aeon

#endif // aeon_logger_simple_sink_backend_h__

