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

#include <aeon/common/noncopyable.h>
#include <string_view>
#include <string>
#include <cassert>

namespace aeon::common::dll_loader
{

using dll_handle = void *;

/*!
 * Load a dll by filename. Returns nullptr if this failed.
 * The returned handle must be cleaned up with free_dll_handle.
 *
 * The given filename should not contain any file extension
 * as it is added automatically based on the platform.
 */
[[nodiscard]] dll_handle get_dll_handle(const char *filename);

/*!
 * Free a dll by handle. If the given handle is nullptr, nothing
 * will happen.
 */
void free_dll_handle(const dll_handle handle);

/*!
 * Get the address of a proc inside of the loaded dll or nullptr
 * if it was not found.
 */
[[nodiscard]] void *get_dll_proc_address(const dll_handle handle, const char *proc);

class scoped_dll_handle : noncopyable
{
public:
    /*!
     * Attempt to load a dll by filename. Be sure to check is_valid()
     * to see if the dll was loaded correctly.
     */
    explicit scoped_dll_handle(const char *filename)
        : handle_(get_dll_handle(filename))
    {
    }

    /*!
     * Attempt to load a dll by filename. Be sure to check is_valid()
     * to see if the dll was loaded correctly.
     */
    explicit scoped_dll_handle(const std::string_view &filename)
        : scoped_dll_handle(std::string{filename}.c_str()) // TODO: There must be a better way than this...
    {
    }

    ~scoped_dll_handle()
    {
        free_dll_handle(handle_);
    }

    scoped_dll_handle(scoped_dll_handle &&other) noexcept
        : handle_(other.handle_)
    {
        other.handle_ = nullptr;
    }

    scoped_dll_handle &operator=(scoped_dll_handle &&other) noexcept
    {
        handle_ = other.handle_;
        other.handle_ = nullptr;
        return *this;
    }

    /*!
     * Returns true if the dll was loaded correctly.
     */
    [[nodiscard]] auto is_valid() const noexcept
    {
        return handle_ != nullptr;
    }

    /*!
     * Get the address of a proc inside of the loaded dll or nullptr
     * if it was not found. Be sure to check is_valid() first to see
     * if the dll was loaded correctly.
     */
    [[nodiscard]] auto get_proc_address(const char *proc) const
    {
        assert(is_valid());
        return get_dll_proc_address(handle_, proc);
    }

    /*!
     * Get the address of a proc inside of the loaded dll or nullptr
     * if it was not found. Be sure to check is_valid() first to see
     * if the dll was loaded correctly.
     */
    [[nodiscard]] auto get_proc_address(const std::string_view &proc) const
    {
        return get_proc_address(std::string{proc}.c_str()); // TODO: Find a better way.
    }

    /*!
     * Release the dll handle. This will return the internal handle
     * and stop it from getting removed when this class goes out of
     * scope. Be aware that free_dll_handle must be called on this
     * returned handle manually.
     */
    [[nodiscard]] auto release() noexcept
    {
        const auto handle = handle_;
        handle_ = nullptr;
        return handle;
    }

private:
    dll_handle handle_;
};

} // namespace aeon::common::dll_loader
