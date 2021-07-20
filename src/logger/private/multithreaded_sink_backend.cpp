// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/logger/multithreaded_sink_backend.h>
#include <aeon/logger/log_sink.h>

namespace aeon::logger
{

multithreaded_sink_backend::multithreaded_sink_backend()
    : base_backend(log_level::message)
    , running_(true)
{
    handle_background_thread_();
}

multithreaded_sink_backend::multithreaded_sink_backend(log_level level)
    : base_backend(level)
    , running_(true)
{
    handle_background_thread_();
}

multithreaded_sink_backend::~multithreaded_sink_backend()
{
    stop();
}

void multithreaded_sink_backend::add_sink(log_sink *sink)
{
    std::scoped_lock lock(sink_mutex_);
    sinks_.insert(sink);
}

void multithreaded_sink_backend::remove_all_sinks()
{
    std::scoped_lock lock(sink_mutex_);
    sinks_.clear();
}

void multithreaded_sink_backend::stop()
{
    if (!running_)
        return;

    running_ = false;
    cv_.notify_one();
    thread_.join();
}

void multithreaded_sink_backend::handle_background_thread_()
{
    running_ = true;

    thread_ = std::thread(
        [this]()
        {
            while (running_)
            {
                std::unique_lock lock(signal_mutex_);
                cv_.wait(lock);

                if (!running_)
                    break;

                // Move the message queue into a new copy and empty the real queue
                queue_mutex_.lock();
                log_message_queue log_queue = std::move(log_queue_);
                log_queue_ = log_message_queue();
                queue_mutex_.unlock();

                bool reprocess_queue = true;

                while (reprocess_queue)
                {
                    // Copy the sinks
                    sink_mutex_.lock();
                    sink_set sinks = sinks_;
                    sink_mutex_.unlock();

                    // Handle all messages
                    for (auto &msg : log_queue)
                    {
                        for (auto &sink : sinks)
                        {
                            sink->log(msg.message, msg.module, msg.level);
                        }
                    }

                    queue_mutex_.lock();
                    if (!log_queue_.empty())
                    {
                        log_queue = std::move(log_queue_);
                        log_queue_ = log_message_queue();
                        reprocess_queue = true;
                    }
                    else
                    {
                        reprocess_queue = false;
                    }
                    queue_mutex_.unlock();
                }
            }
        });
}

void multithreaded_sink_backend::log(const std::string &message, const std::string &module, const log_level level)
{
    std::scoped_lock lock(queue_mutex_);
    log_queue_.push_back({message, module, level});
    cv_.notify_one();
}

} // namespace aeon::logger
