// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

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
[[nodiscard]] dll_handle get_dll_handle(const std::string &filename);

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

class scoped_dll_handle
{
public:
    scoped_dll_handle() noexcept
        : handle_{nullptr}
    {
    }

    /*!
     * Attempt to load a dll by filename. Be sure to check is_valid()
     * to see if the dll was loaded correctly.
     */
    explicit scoped_dll_handle(const std::string &filename)
        : handle_(get_dll_handle(filename))
    {
    }

    ~scoped_dll_handle()
    {
        free_handle();
    }

    scoped_dll_handle(scoped_dll_handle &&other) noexcept
        : handle_(other.handle_)
    {
        other.handle_ = nullptr;
    }

    scoped_dll_handle &operator=(scoped_dll_handle &&other) noexcept
    {
        if (this != &other) [[likely]]
        {
            free_handle();
            handle_ = other.handle_;
            other.handle_ = nullptr;
        }

        return *this;
    }

    scoped_dll_handle(const scoped_dll_handle &) = delete;
    auto operator=(const scoped_dll_handle &) -> scoped_dll_handle & = delete;

    auto operator=(const dll_handle handle) -> scoped_dll_handle &
    {
        if (handle_ != &handle) [[likely]]
        {
            free_handle();
            handle_ = handle;
        }

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
    template <typename T>
    [[nodiscard]] auto get_proc_address(const char *proc) const
    {
        return reinterpret_cast<T *>(get_proc_address(proc));
    }

    /*!
     * Release the dll handle. This will return the internal handle
     * and stop it from getting removed when this class goes out of
     * scope. Be aware that free_dll_handle must be called on this
     * returned handle manually.
     */
    [[nodiscard]] auto release() noexcept
    {
        auto *const handle = handle_;
        handle_ = nullptr;
        return handle;
    }

private:
    void free_handle() const noexcept
    {
        free_dll_handle(handle_);
    }

    dll_handle handle_;
};

} // namespace aeon::common::dll_loader
