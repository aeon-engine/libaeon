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
#include "context.h"
#include <iostream>

namespace aeon::tracelog
{

namespace detail
{

auto add_entry(const char *func) -> trace_log_entry *
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
