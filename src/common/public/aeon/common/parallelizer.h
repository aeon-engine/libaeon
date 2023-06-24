// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/common/dispatcher.h>
#include <functional>
#include <vector>

namespace aeon::common
{

class parallelizer
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

    parallelizer(parallelizer &&) = delete;
    auto operator=(parallelizer &&) -> parallelizer & = delete;

    parallelizer(const parallelizer &) = delete;
    auto operator=(const parallelizer &) -> parallelizer & = delete;

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
        threads.reserve(concurrency);

        for (int i = 0; i < concurrency; ++i)
        {
            threads.emplace_back([this]() { dispatcher_.run(); });
        }

        for (auto &thread : threads)
        {
            thread.join();
        }
    }

private:
    dispatcher dispatcher_;
};

} // namespace aeon::common
