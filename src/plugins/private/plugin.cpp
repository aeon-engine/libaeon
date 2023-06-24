// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/plugins/plugin.h>
#include <cassert>

namespace aeon::plugins
{

plugin::plugin()
    : loader_(nullptr)
{
}

auto plugin::get_plugin_loader() const -> plugin_loader &
{
    assert(loader_);
    return *loader_;
}

void plugin::set_plugin_loader_internal(plugin_loader &loader)
{
    loader_ = &loader;
}

} // namespace aeon::plugins
