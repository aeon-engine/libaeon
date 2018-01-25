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

#include <aeon/plugins/plugin.h>
#include <aeon/common/noncopyable.h>
#include <aeon/common/dll_loader.h>
#include <memory>
#include <map>
#include <functional>
#include <string>
#include <string_view>

namespace aeon::plugins
{

class plugin_loader : common::noncopyable
{
public:
    plugin_loader();
    ~plugin_loader();

    /*!
     * Load a plugin by name. The given template
     * must be the interface that the plugin uses.
     *
     * It's recommended to put the return value in "scoped_plugin"
     * so that the unloading and cleanup of the plugin is handled
     * RAII.
     */
    template <typename T>
    [[nodiscard]] auto load(const char *name) -> T *
    {
        return static_cast<T *>(load(name));
    }

    /*!
     * Check if a given plugin is loaded by pointer.
     */
    [[nodiscard]] auto is_loaded(const plugin *p) const -> bool;

    /*!
     * Check if a given plugin is loaded by name.
     */
    [[nodiscard]] auto is_loaded(const std::string_view &name) const -> bool;

    /*!
     * Unload a plugin by pointer. If the given plugin pointer is unknown,
     * nothing will happen.
     */
    void unload(const plugin *p);

    /*!
     * Unload a plugin by name. If the given name is unknown,
     * nothing will happen.
     */
    void unload(const std::string_view &name);

    /*!
     * Unload all loaded plugins.
     */
    void unload_all();

private:
    using initialize_plugin_proc = auto (*)() -> plugin *;
    using cleanup_plugin_proc = void (*)(const plugin *);

    /*!
     * Internal helper struct
     */
    struct plugin_cache
    {
        // Order here is important. The plugin must be deleted before the handle.
        common::dll_loader::scoped_dll_handle handle;
        std::unique_ptr<plugin, cleanup_plugin_proc> plugin;
    };

    /*!
     * Load a plugin by name.
     */
    auto load(const std::string_view &name) -> plugin *;

    /*!
     * Actually load the plugin by loading in the dll, getting the proc addresses
     * and calling them. Returns nullptr in case of an error.
     */
    auto load_plugin(const std::string_view &name) -> plugin *;

    /*!
     * Get a previously loaded plugin by name from the cache. Returns nullptr if
     * not found.
     */
    auto find_in_cache(const std::string_view &name) -> plugin *;

    /*!
     * Unload a plugin based on iterator. This is a helper method called by the
     * public unload methods.
     */
    void unload(std::map<std::string, plugin_cache>::iterator itr);

    std::map<std::string, plugin_cache> cache_;
};

template <typename T>
class[[nodiscard]] scoped_plugin
{
public:
    scoped_plugin(T * p)
        : plugin_interface_(p)
        , loader_(p ? &plugin_interface_->get_plugin_loader() : nullptr)
    {
    }

    ~scoped_plugin()
    {
        if (plugin_interface_ && loader_)
        {
            loader_->unload(plugin_interface_);
        }
    }

    scoped_plugin(scoped_plugin && other) noexcept
        : plugin_interface_(std::move(other.plugin_interface_))
        , loader_(std::move(other.loader_))
    {
        other.plugin_interface_ = nullptr;
        other.loader_ = nullptr;
    }

    scoped_plugin &operator=(scoped_plugin &&other) noexcept
    {
        plugin_interface_ = std::move(other.plugin_interface_);
        loader_ = std::move(other.loader_);
        other.plugin_interface_ = nullptr;
        other.loader_ = nullptr;
        return *this;
    }

    scoped_plugin(const scoped_plugin &other) = delete;
    scoped_plugin &operator=(const scoped_plugin &other) = delete;

    auto valid() const noexcept
    {
        return plugin_interface_ && loader_;
    }

    operator bool() const noexcept
    {
        return valid();
    }

    auto get() const noexcept
    {
        return plugin_interface_;
    }

    auto operator->() const noexcept
    {
        return plugin_interface_;
    }

    auto release() noexcept
    {
        const auto plugin = plugin_interface_;
        plugin_interface_ = nullptr;
        return plugin;
    }

private:
    T *plugin_interface_;
    plugin_loader *loader_;
};

} // namespace aeon::plugins
