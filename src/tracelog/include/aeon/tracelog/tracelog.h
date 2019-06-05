// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include <aeon/common/preprocessor.h>
#include <aeon/common/stdfilesystem.h>

namespace aeon::tracelog
{

namespace detail
{

struct trace_log_entry;

auto add_entry(const char *func) -> trace_log_entry *;
void add_exit(trace_log_entry *entry);
void add_event(const char *func);

class [[nodiscard]] scoped_trace_log
{
public:
    scoped_trace_log(const char *func)
    {
        entry_ = detail::add_entry(func);
    }

    ~scoped_trace_log()
    {
        detail::add_exit(entry_);
    }

    scoped_trace_log(scoped_trace_log &&) = delete;
    auto operator=(scoped_trace_log &&)->scoped_trace_log & = delete;

    scoped_trace_log(const scoped_trace_log &) = delete;
    auto operator=(const scoped_trace_log &)->scoped_trace_log & = delete;

private:
    trace_log_entry *entry_;
};

} // namespace detail

/*!
 * Must be called at the start of each thread before using aeon_scoped_tracelog.
 */
void initialize();

/*!
 * Should be called at the end of tracing. This will clear all current tracing buffers.
 * The file may not already exist.
 */
void write(const std::filesystem::path &file);

#define aeon_tracelog_scoped() aeon::tracelog::detail::scoped_trace_log aeon_anonymous_variable(trace)(__FUNCTION__)

#define aeon_event() aeon::tracelog::detail::add_trace_log_event(__FUNCTION__)

} // namespace aeon::tracelog
