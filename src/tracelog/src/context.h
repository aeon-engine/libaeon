// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include "data.h"
#include <aeon/streams/devices/file_device.h>
#include <aeon/common/singleton.h>
#include <filesystem>
#include <atomic>
#include <vector>
#include <mutex>

namespace aeon::tracelog::detail
{

class trace_log_context : public common::singleton<trace_log_context>
{
public:
    void initialize();
    [[nodiscard]] auto add_scoped_log_entry(const char *func) const -> trace_log_entry *;
    void add_scoped_log_exit(trace_log_entry *entry) const;

    void add_event(const char *func) const;

    void write(const std::filesystem::path &path);

private:
    void allocate_new_list() const;
    auto generate_unique_thread_id() noexcept -> int;
    void register_threadlocal_context(trace_log_thread_context *context);

    void append_write(streams::file_sink_device &stream, trace_log_thread_context *context) const;

    static thread_local trace_log_thread_context context_;
    std::atomic<int> thread_index_ = 0;

    std::vector<trace_log_thread_context *> contexts_;
    std::mutex thread_container_lock_;
};

} // namespace aeon::tracelog::detail
