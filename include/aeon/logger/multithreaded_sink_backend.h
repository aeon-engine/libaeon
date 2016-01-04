/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2015 Robin Degen
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains the property of
 * Robin Degen and its suppliers, if any. The intellectual and technical
 * concepts contained herein are proprietary to Robin Degen and its suppliers
 * and may be covered by U.S. and Foreign Patents, patents in process, and are
 * protected by trade secret or copyright law. Dissemination of this
 * information or reproduction of this material is strictly forbidden unless
 * prior written permission is obtained from Robin Degen.
 */

#pragma once

namespace aeon
{
namespace logger
{

class multithreaded_sink_backend : public base_backend
{
private:
    typedef std::vector<std::pair<std::string, log_level>> log_message_queue;
    typedef std::set<log_sink_ptr> sink_set;

public:
    multithreaded_sink_backend()
        : base_backend(log_level::message)
        , running_(true)
    {
        handle_background_thread_();
    }

    multithreaded_sink_backend(log_level level)
        : base_backend(level)
        , running_(true)
    {
        handle_background_thread_();
    }

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

        thread_ = std::thread([this]()
                              {
                                  while (running_)
                                  {
                                      std::unique_lock<std::mutex> lock(signal_mutex_);
                                      cv_.wait(lock);

                                      if (!running_)
                                          break;

                                      // Move the message queue into a new copy and empty the real queue
                                      queue_mutex_.lock();
                                      log_message_queue log_queue = std::move(log_queue_);
                                      log_queue_.clear();
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
                                                  sink->log(msg.first, msg.second);
                                              }
                                          }

                                          queue_mutex_.lock();
                                          if (!log_queue_.empty())
                                          {
                                              log_message_queue log_queue = std::move(log_queue_);
                                              log_queue_.clear();
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

    virtual void log(std::string &&message, log_level level)
    {
        std::lock_guard<std::mutex> lock(queue_mutex_);
        log_queue_.push_back({std::move(message), level});
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
