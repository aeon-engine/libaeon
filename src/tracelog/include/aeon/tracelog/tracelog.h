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

#include <aeon/common/anonymous_variable.h>

namespace aeon::tracelog
{

namespace detail
{

void add_entry(const char *func);
void add_exit(const char *func);
void add_event(const char *func);

class scoped_trace_log
{
public:
    scoped_trace_log(const char *func)
        : func_{func}
    {
        detail::add_entry(func_);
    }

    ~scoped_trace_log()
    {
        detail::add_exit(func_);
    }

    scoped_trace_log(scoped_trace_log &&) = delete;
    auto operator=(scoped_trace_log &&) -> scoped_trace_log & = delete;

    scoped_trace_log(const scoped_trace_log &) = delete;
    auto operator=(const scoped_trace_log &) -> scoped_trace_log & = delete;

private:
    const char *func_;
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
void write(const char *file);

#define aeon_tracelog_scoped() aeon::tracelog::detail::scoped_trace_log aeon_anonymous_variable(trace)(__FUNCTION__)

#define aeon_event() aeon::tracelog::detail::add_trace_log_event(__FUNCTION__)

} // namespace aeon::tracelog
