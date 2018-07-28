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

#include <aeon/tracelog/tracelog.h>
#include <aeon/common/timer.h>
#include <aeon/common/assert.h>
#include <cstdint>
#include <memory>
#include <atomic>

#include <iostream>

namespace aeon::tracelog
{

namespace detail
{

static const std::uint64_t log_entry_count = 10000000; // Around 300mb per list.

enum class trace_log_entry_type
{
    entry,
    exit,
    event
};

struct trace_log_entry
{
    double timestamp;
    const char *function;
    int thread_id;
    trace_log_entry_type type;
};

struct trace_log_list
{
    trace_log_entry entries[log_entry_count]; // Uninitialized on purpose.
    std::unique_ptr<trace_log_list> next;
};

struct trace_log_thread_context
{
    trace_log_list *head = nullptr;
    std::unique_ptr<trace_log_list> tail;
    std::uint64_t index = 0;
    common::timer timer;
    int thread_id = 0;
};

static thread_local trace_log_thread_context trace_log_context;
static std::atomic<int> thread_id_index = 0;

static void allocate_new_log_list()
{
    trace_log_context.head->next = std::make_unique<detail::trace_log_list>();
    trace_log_context.head = trace_log_context.head->next.get();
    trace_log_context.index = 0;
}

static void add_trace_log(const char *func, const trace_log_entry_type type)
{
    aeon_assert(trace_log_context.head && trace_log_context.tail,
                "tracelog::initialize() must be called before using the trace logger.");

    trace_log_context.head->entries[trace_log_context.index] = {trace_log_context.timer.get_time_difference(), func,
                                                                trace_log_context.thread_id, type};

    if (++trace_log_context.index >= log_entry_count)
        allocate_new_log_list();
}

void add_entry(const char *func)
{
    add_trace_log(func, trace_log_entry_type::entry);
}

void add_exit(const char *func)
{
    add_trace_log(func, trace_log_entry_type::exit);
}

void add_event(const char *func)
{
    add_trace_log(func, trace_log_entry_type::event);
}

} // namespace detail

void initialize()
{
    aeon_assert(!detail::trace_log_context.head && !detail::trace_log_context.tail,
                "tracelog::initialize() already called on this thread.");

    detail::trace_log_context.tail = std::make_unique<detail::trace_log_list>();
    detail::trace_log_context.head = detail::trace_log_context.tail.get();
    detail::trace_log_context.index = 0;
    detail::trace_log_context.thread_id = std::atomic_fetch_add(&detail::thread_id_index, 1);
}

void write(const char *file)
{
    aeon_assert(detail::trace_log_context.head && detail::trace_log_context.tail,
                "tracelog::initialize() must be called before using the trace logger.");

    // Move the lists out 1 by 1 while parsing so that they'll get deleted non-recursively.
    // Without this, there is a chance of a stack overflow.
    auto current_list = std::move(detail::trace_log_context.tail);
    auto current_list_size = detail::log_entry_count;

    if (current_list.get() == detail::trace_log_context.head)
        current_list_size = detail::trace_log_context.index;

    while (true)
    {
        for (std::uint64_t i = 0; i < current_list_size; ++i)
        {
            std::cout << current_list->entries[i].timestamp << " "
                      << (current_list->entries[i].type == detail::trace_log_entry_type::entry ? ">>  " : "<<  ")
                      << current_list->entries[i].function << "\n";
        }

        if (current_list.get() == detail::trace_log_context.head)
            break;

        current_list = std::move(current_list->next);
    }
}

} // namespace aeon::tracelog
