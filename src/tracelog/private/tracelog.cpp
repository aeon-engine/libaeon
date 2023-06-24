// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/tracelog/tracelog.h>
#include "context.h"

namespace aeon::tracelog
{

namespace detail
{

[[nodiscard]] auto add_entry(const char *func) -> trace_log_entry *
{
    return detail::trace_log_context::get_singleton().add_scoped_log_entry(func);
}

void add_exit(trace_log_entry *entry)
{
    detail::trace_log_context::get_singleton().add_scoped_log_exit(entry);
}

void add_event(const char *func)
{
    detail::trace_log_context::get_singleton().add_event(func);
}

} // namespace detail

void initialize()
{
    detail::trace_log_context::get_singleton().initialize();
}

void write(const std::filesystem::path &file)
{
    detail::trace_log_context::get_singleton().write(file);
}

} // namespace aeon::tracelog
