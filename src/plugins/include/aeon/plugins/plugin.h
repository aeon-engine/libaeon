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

#include <aeon/common/dll_export.h>
#include <memory>

namespace aeon::plugins
{

class plugin_loader;

/*!
 * Base class for a plugin that can be loaded with the plugin loader.
 *
 * Note: On windows it's recommended to provide overloads for new and delete
 * from the loader to the plugin, so that all allocations are done within
 * the same heap space.
 */
class plugin
{
public:
    virtual ~plugin() = default;

    /*!
     * This should return a short descriptive name of the plugin.
     */
    virtual auto plugin_name() const noexcept -> const char * = 0;

    /*!
     * This should return a version string for this plugin.
     */
    virtual auto plugin_version_string() const noexcept -> const char * = 0;

    /*!
     * Called when the plugin is being loaded, right before the interface is
     * given to the application that loaded it. Here, dependencies can be loaded.
     */
    virtual void plugin_on_load()
    {
    }

    /*!
     * Called when the plugin is about to be unloaded.
     */
    virtual void plugin_on_unload()
    {
    }

    /*!
     * Get the interface to the loader that loaded this plugin.
     */
    auto get_plugin_loader() const -> plugin_loader &;

protected:
    /*!
     * The plugin implementer must forward the given loader to this ctor.
     */
    explicit plugin(plugin_loader &loader);

    plugin_loader &loader_;
};

} // namespace aeon::plugins

#define aeon_register_plugin(plugin_class)                                                                             \
    extern "C" AEON_DLL_EXPORT aeon::plugins::plugin *aeon_initialize_plugin(aeon::plugins::plugin_loader &loader)     \
    {                                                                                                                  \
        return std::make_unique<plugin_class>(loader).release();                                                       \
    }                                                                                                                  \
                                                                                                                       \
    extern "C" AEON_DLL_EXPORT void aeon_cleanup_plugin(const aeon::plugins::plugin *plugin)                           \
    {                                                                                                                  \
        delete plugin;                                                                                                 \
    }
