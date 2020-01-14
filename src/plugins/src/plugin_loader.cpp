// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#include <aeon/plugins/plugin_loader.h>
#include <aeon/common/dll_loader.h>

namespace aeon::plugins
{

static const auto aeon_initialize_plugin_proc_name = "aeon_initialize_plugin";
static const auto aeon_cleanup_plugin_proc_name = "aeon_cleanup_plugin";

plugin_loader::plugin_loader()
    : cache_{}
{
}

plugin_loader::~plugin_loader()
{
    unload_all();
}

[[nodiscard]] auto plugin_loader::is_loaded(const plugin *p) const -> bool
{
    for (const auto &cache_obj : cache_)
    {
        if (cache_obj.second.plugin_instance.get() == p)
            return true;
    }

    return false;
}

[[nodiscard]] auto plugin_loader::is_loaded(const std::string_view &name) const -> bool
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

[[nodiscard]] auto plugin_loader::load(const std::string &name) -> plugin *
{
    const auto result = find_in_cache(name);

    if (result)
        return result;

    return load_plugin(name);
}

[[nodiscard]] auto plugin_loader::load_plugin(const std::string &name) -> plugin *
{
    common::dll_loader::scoped_dll_handle handle(name);

    if (!handle.is_valid())
        return nullptr;

    const auto initialize_plugin =
        reinterpret_cast<initialize_plugin_proc>(handle.get_proc_address(aeon_initialize_plugin_proc_name));
    const auto cleanup_plugin =
        reinterpret_cast<cleanup_plugin_proc>(handle.get_proc_address(aeon_cleanup_plugin_proc_name));

    auto plugin_instance = std::unique_ptr<plugin, cleanup_plugin_proc>(initialize_plugin(), cleanup_plugin);
    const auto plugin_instance_ptr = plugin_instance.get();

    if (!plugin_instance_ptr)
        return nullptr;

    plugin_instance->set_plugin_loader_internal(*this);

    plugin_instance->plugin_on_load();

    plugin_cache cache{std::move(handle), std::move(plugin_instance)};
    cache_.insert({name, std::move(cache)});

    return plugin_instance_ptr;
}

[[nodiscard]] auto plugin_loader::find_in_cache(const std::string &name) -> plugin *
{
    const auto result = cache_.find(name);

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
