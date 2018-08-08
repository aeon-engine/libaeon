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

#include "data.h"
#include <aeon/common/singleton.h>
#include <aeon/common/stdfilesystem.h>
#include <aeon/streams/file_stream_fwd.h>
#include <atomic>
#include <vector>
#include <mutex>

namespace aeon::tracelog::detail
{

class trace_log_context : public common::singleton<trace_log_context>
{
public:
    void initialize();
    auto add_scoped_log_entry(const char *func) const -> trace_log_entry *;
    void add_scoped_log_exit(trace_log_entry *entry) const;

    void add_event(const char *func) const;

    void write(const std::filesystem::path &path);

private:
    void allocate_new_list() const;
    auto generate_unique_thread_id() noexcept -> int;
    void register_threadlocal_context(trace_log_thread_context *context);

    void append_write(streams::file_stream &stream, trace_log_thread_context *context) const;

    static thread_local trace_log_thread_context context_;
    std::atomic<int> thread_index_ = 0;

    std::vector<trace_log_thread_context *> contexts_;
    std::mutex thread_container_lock_;
};

} // namespace aeon::tracelog::detail
