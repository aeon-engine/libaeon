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

#include <aeon/plugins/plugin_loader.h>
#include <aeon/common/dll_loader.h>

namespace aeon::plugins
{

static const auto aeon_initialize_plugin_proc_name = "aeon_initialize_plugin";
static const auto aeon_cleanup_plugin_proc_name = "aeon_cleanup_plugin";

plugin_loader::plugin_loader()
    : cache_()
{
}

plugin_loader::~plugin_loader()
{
    unload_all();
}

auto plugin_loader::is_loaded(const plugin *p) const -> bool
{
    for (auto itr = cache_.begin(); itr != cache_.end(); ++itr)
    {
        if (itr->second.plugin_instance.get() == p)
            return true;
    }

    return false;
}

auto plugin_loader::is_loaded(const std::string_view &name) const -> bool
{
    const auto result = cache_.find(std::string{name});
    return result != cache_.end();
}

void plugin_loader::unload(const plugin *p)
{
    for (auto itr = cache_.begin(); itr != cache_.end(); ++itr)
    {
        if (itr->second.plugin_instance.get() == p)
        {
            unload(itr);
            return;
        }
    }
}

void plugin_loader::unload(const std::string_view &name)
{
    const auto result = cache_.find(std::string{name});

    if (result == cache_.end())
        return;

    unload(result);
}

void plugin_loader::unload_all()
{
    cache_.clear();
}

auto plugin_loader::load(const std::string_view &name) -> plugin *
{
    const auto result = find_in_cache(name);

    if (result)
        return result;

    return load_plugin(name);
}

auto plugin_loader::load_plugin(const std::string_view &name) -> plugin *
{
    common::dll_loader::scoped_dll_handle handle(name);

    if (!handle.is_valid())
        return nullptr;

    auto initialize_plugin =
        reinterpret_cast<initialize_plugin_proc>(handle.get_proc_address(aeon_initialize_plugin_proc_name));
    auto cleanup_plugin = reinterpret_cast<cleanup_plugin_proc>(handle.get_proc_address(aeon_cleanup_plugin_proc_name));

    auto plugin_instance = std::unique_ptr<plugin, cleanup_plugin_proc>(initialize_plugin(), cleanup_plugin);
    auto plugin_instance_ptr = plugin_instance.get();

    if (!plugin_instance_ptr)
        return nullptr;

    plugin_instance->set_plugin_loader_internal(*this);

    plugin_instance->plugin_on_load();

    plugin_cache cache{std::move(handle), std::move(plugin_instance)};
    cache_.insert({std::string{name}, std::move(cache)});

    return plugin_instance_ptr;
}

auto plugin_loader::find_in_cache(const std::string_view &name) -> plugin *
{
    const auto result = cache_.find(std::string{name});

    if (result == cache_.end())
        return nullptr;

    return result->second.plugin_instance.get();
}

void plugin_loader::unload(std::map<std::string, plugin_cache>::iterator itr)
{
    const auto &cache = itr->second;
    cache.plugin_instance->plugin_on_unload();

    cache_.erase(itr);
}

} // namespace aeon::plugins
