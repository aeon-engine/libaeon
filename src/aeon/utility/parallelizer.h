/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2016 Robin Degen
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
namespace utility
{

class parallelizer : noncopyable
{
public:
    using task = std::function<void()>;
    using task_vector = std::vector<task>;

    parallelizer()
        : dispatcher_(dispatcher_stop_mode::stop_on_empty_queue)
    {
    }

    explicit parallelizer(const task_vector &tasks)
        : dispatcher_(dispatcher_stop_mode::stop_on_empty_queue)
    {
        add_jobs(tasks);
    }

    ~parallelizer() = default;

    void add_job(const task &task)
    {
        dispatcher_.post(task);
    }

    void add_jobs(const task_vector &tasks)
    {
        for (auto &task : tasks)
        {
            dispatcher_.post(task);
        }
    }

    void run(const int concurrency)
    {
        std::vector<std::thread> threads;
        for (int i = 0; i < concurrency; ++i)
        {
            threads.emplace_back(std::thread([this]() { dispatcher_.run(); }));
        }

        for (auto& thread : threads)
        {
            thread.join();
        }
    }

private:
    dispatcher dispatcher_;
};

} // namespace utility
} // namespace aeon
