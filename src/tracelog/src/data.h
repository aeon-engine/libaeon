// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <aeon/common/timer.h>
#include "config.h"
#include <memory>
#include <cstdint>

namespace aeon::tracelog::detail
{

enum class trace_log_entry_type
{
    scope,
    event
};

struct [[nodiscard]] trace_log_entry
{
    double begin;
    double end;
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

} // namespace aeon::tracelog::detail
