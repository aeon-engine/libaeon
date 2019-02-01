// Copyright (c) 2012-2019 Robin Degen

#include "context.h"
#include <aeon/common/assert.h>
#include <aeon/streams/stream_writer.h>

#include <iostream>

namespace aeon::tracelog::detail
{

thread_local trace_log_thread_context trace_log_context::context_;

void trace_log_context::initialize()
{
    aeon_assert(!context_.head && !context_.tail, "tracelog::initialize() already called on this thread.");

    context_.tail = std::make_unique<detail::trace_log_list>();
    context_.head = context_.tail.get();
    context_.index = 0;
    context_.thread_id = generate_unique_thread_id();

    register_threadlocal_context(&context_);
}

auto trace_log_context::add_scoped_log_entry(const char *func) const -> trace_log_entry *
{
    aeon_assert(context_.head && context_.tail, "tracelog::initialize() must be called before using the trace logger.");

    const auto entry_ptr = &context_.head->entries[context_.index];
    *entry_ptr = {context_.timer.get_time_difference(), 0.0, func, context_.thread_id, trace_log_entry_type::scope};

    if (++context_.index >= log_entry_count)
        allocate_new_list();

    return entry_ptr;
}

void trace_log_context::add_scoped_log_exit(trace_log_entry *entry) const
{
    entry->end = context_.timer.get_time_difference();
}

void trace_log_context::add_event(const char *func) const
{
    aeon_assert(context_.head && context_.tail, "tracelog::initialize() must be called before using the trace logger.");

    context_.head->entries[context_.index] = {context_.timer.get_time_difference(), 0.0f, func, context_.thread_id,
                                              trace_log_entry_type::event};

    if (++context_.index >= log_entry_count)
        allocate_new_list();
}

void trace_log_context::write(const std::filesystem::path &path)
{
    aeon_assert(context_.head && context_.tail, "tracelog::initialize() must be called before using the trace logger.");

    streams::file_sink_device file(path, streams::file_mode::text);
    streams::stream_writer writer{file};

    writer << "{\"traceEvents\": [";

    std::scoped_lock<std::mutex> lock(thread_container_lock_);
    for (auto context : contexts_)
    {
        append_write(file, context);
    }

    writer << "]}";

    file.flush();
}

void trace_log_context::allocate_new_list() const
{
    context_.head->next = std::make_unique<detail::trace_log_list>();
    context_.head = context_.head->next.get();
    context_.index = 0;
}

auto trace_log_context::generate_unique_thread_id() noexcept -> int
{
    return std::atomic_fetch_add(&thread_index_, 1);
}

void trace_log_context::register_threadlocal_context(trace_log_thread_context *context)
{
    std::scoped_lock<std::mutex> lock(thread_container_lock_);
    contexts_.emplace_back(context);
}

void trace_log_context::append_write(streams::file_sink_device &stream, trace_log_thread_context *context) const
{
    // Move the lists out 1 by 1 while parsing so that they'll get deleted non-recursively.
    // Without this, there is a chance of a stack overflow.
    auto current_list = std::move(context->tail);
    auto current_list_size = log_entry_count;

    if (current_list.get() == context->head)
        current_list_size = context->index;

    streams::stream_writer writer{stream};

    while (true)
    {
        for (std::uint64_t i = 0; i < current_list_size; ++i)
        {
            const auto entry = current_list->entries[i];
            auto str = R"({ "pid":1, "tid":)" + std::to_string(entry.thread_id) + R"(, "ts":)" +
                       std::to_string(entry.begin) + R"(, "dur":)" + std::to_string(entry.end - entry.begin) +
                       R"(, "ph":"X", "name":")" + entry.function + R"(" })";

            writer << str;

            if (i + 1 < current_list_size)
                writer << ',';

            writer << '\n';
        }

        if (current_list.get() == context->head)
            break;

        current_list = std::move(current_list->next);
    }
}

} // namespace aeon::tracelog::detail
