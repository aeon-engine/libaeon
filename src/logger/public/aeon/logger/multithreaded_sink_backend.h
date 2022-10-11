// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/logger/base_backend.h>
#include <vector>
#include <set>
#include <mutex>
#include <thread>
#include <condition_variable>

namespace aeon::logger
{

class log_sink;

class multithreaded_sink_backend final : public base_backend
{
private:
    struct log_message_queue_entry
    {
        common::string message;
        common::string module;
        log_level level;
    };

    typedef std::vector<log_message_queue_entry> log_message_queue;
    typedef std::set<log_sink *> sink_set;

public:
    multithreaded_sink_backend();

    explicit multithreaded_sink_backend(const log_level level);

    ~multithreaded_sink_backend() final;

    multithreaded_sink_backend(const multithreaded_sink_backend &) = delete;
    auto operator=(const multithreaded_sink_backend &) noexcept -> multithreaded_sink_backend & = delete;

    multithreaded_sink_backend(multithreaded_sink_backend &&) = delete;
    auto operator=(multithreaded_sink_backend &&) noexcept -> multithreaded_sink_backend & = delete;

    void add_sink(log_sink *sink);

    void remove_all_sinks();

    void stop();

private:
    void handle_background_thread();

    void log(const common::string &message, const common::string &module, const log_level level) final;

    std::thread thread_;
    std::mutex signal_mutex_;
    std::condition_variable cv_;

    std::mutex sink_mutex_;
    sink_set sinks_;

    std::mutex queue_mutex_;
    log_message_queue log_queue_;

    volatile bool running_;
};

} // namespace aeon::logger
