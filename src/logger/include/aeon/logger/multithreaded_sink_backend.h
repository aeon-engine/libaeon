/*
 * Copyright (c) 2012-2018 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

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

class multithreaded_sink_backend : public base_backend
{
private:
    struct log_message_queue_entry
    {
        std::string message;
        std::string module;
        log_level level;
    };

    typedef std::vector<log_message_queue_entry> log_message_queue;
    typedef std::set<log_sink *> sink_set;

public:
    multithreaded_sink_backend();

    explicit multithreaded_sink_backend(log_level level);

    virtual ~multithreaded_sink_backend();

    multithreaded_sink_backend(const multithreaded_sink_backend &) = delete;
    auto operator=(const multithreaded_sink_backend &) noexcept -> multithreaded_sink_backend & = delete;

    multithreaded_sink_backend(multithreaded_sink_backend &&) = delete;
    auto operator=(multithreaded_sink_backend &&) noexcept -> multithreaded_sink_backend & = delete;

    void add_sink(log_sink *sink);

    void remove_all_sinks();

    void stop();

private:
    void handle_background_thread_();

    void log(const std::string &message, const std::string &module, const log_level level) override;

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
