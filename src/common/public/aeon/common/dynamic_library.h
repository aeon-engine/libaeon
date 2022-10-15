// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/common/string_view.h>
#include <filesystem>
#include <exception>

namespace aeon::common
{

class dynamic_library_load_exception final : public std::exception
{
};

class dynamic_library final
{
public:
    /*!
     * Wrap an already loaded platform-specific dynamic library handle
     */
    explicit dynamic_library(void *handle) noexcept;

    /*!
     * Load a dynamic library from the given path.
     * \throws dynamic_library_load_exception if the library could not be loaded
     */
    explicit dynamic_library(const std::filesystem::path &path);

    ~dynamic_library();

    dynamic_library(const dynamic_library &) noexcept = delete;
    auto operator=(const dynamic_library &) noexcept -> dynamic_library & = delete;

    dynamic_library(dynamic_library &&other) noexcept;
    auto operator=(dynamic_library &&other) noexcept -> dynamic_library &;

    /*!
     * Returns true if the dynamic library was loaded correctly.
     * Will also return false if the internal handle was released to the outside
     */
    [[nodiscard]] auto is_valid() const noexcept -> bool;

    /*!
     * Returns the platform-specific native handle to the loaded library or nullptr
     */
    [[nodiscard]] auto handle() const noexcept -> void *;

    /*!
     * Get the address of a proc inside of the loaded dll or nullptr
     * if it was not found.
     */
    [[nodiscard]] auto get_proc_address(const string_view &name) const noexcept -> void *;

    /*!
     * Get the address of a proc inside of the loaded dll or nullptr
     * if it was not found.
     */
    template <typename T>
    [[nodiscard]] auto get_proc_address(const char *proc) const noexcept -> T *
    {
        return reinterpret_cast<T *>(get_proc_address(proc));
    }

    /*!
     * Release the dll handle. This will return the internal handle
     * and stop it from getting removed when this class goes out of
     * scope. Be aware that free_dll_handle must be called on this
     * returned handle manually.
     */
    [[nodiscard]] auto release() noexcept -> void *;

private:
    void destroy();

    void *handle_;
};

} // namespace aeon::common
