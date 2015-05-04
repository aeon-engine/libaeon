#ifndef aeon_logger_multithreaded_sink_backend_h__
#define aeon_logger_multithreaded_sink_backend_h__

namespace aeon
{
namespace logger
{

class multithreaded_sink_backend : public base_backend
{
private:
    typedef std::queue<std::pair<std::string, log_level>> log_message_queue;
    typedef std::set<log_sink_ptr> sink_set;

public:
    multithreaded_sink_backend() :
        running_(true)
    {
        handle_background_thread_();
    }

    multithreaded_sink_backend(log_level level) :
        base_backend(level),
        running_(true)
    {
        handle_background_thread_();
    }

    multithreaded_sink_backend(const multithreaded_sink_backend&) = delete;

    virtual ~multithreaded_sink_backend()
    {
        stop();
    }

    void add_sink(log_sink_ptr sink)
    {
        std::lock_guard<std::mutex> lock(sink_mutex_);
        sinks_.insert(sink);
    }

    void remove_all_sinks()
    {
        std::lock_guard<std::mutex> lock(sink_mutex_);
        sinks_.clear();
    }

    void stop()
    {
        if (!running_)
            return;

        running_ = false;
        cv_.notify_one();
        thread_.join();
    }

private:
    void handle_background_thread_()
    {
        running_ = true;

        thread_ = std::thread([this](){
            while (running_)
            {
                std::unique_lock<std::mutex> lock(signal_mutex_);
                cv_.wait(lock);

                if (!running_)
                    break;

                bool recheck_queue = true;

                while (recheck_queue)
                {
                    // Move the message queue into a new copy and empty the real queue
                    queue_mutex_.lock();
                    log_message_queue log_queue = std::move(log_queue_);
                    log_queue_ = log_message_queue();
                    queue_mutex_.unlock();

                    // Copy the sinks
                    sink_mutex_.lock();
                    sink_set sinks = sinks_;
                    sink_mutex_.unlock();

                    // Handle all messages
                    while (!log_queue.empty())
                    {
                        auto &msg = log_queue.front();

                        for (auto &sink : sinks)
                        {
                            sink->log(msg.first, msg.second);
                        }

                        log_queue.pop();
                    }

                    queue_mutex_.lock();
                    recheck_queue = !log_queue_.empty();
                    queue_mutex_.unlock();
                }

            }
        });
    }

    virtual void log(std::string &&message, log_level level)
    {
        std::lock_guard<std::mutex> lock(queue_mutex_);
        log_queue_.push({ std::move(message), level });
        cv_.notify_one();
    }

    std::thread thread_;
    std::mutex signal_mutex_;
    std::condition_variable cv_;

    std::mutex sink_mutex_;
    sink_set sinks_;

    std::mutex queue_mutex_;
    log_message_queue log_queue_;

    volatile bool running_;
};

} // namespace logger
} // namespace aeon

#endif // aeon_logger_multithreaded_sink_backend_h__

