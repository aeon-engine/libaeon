#include <aeon/plugin.h>
#include <plugin/platform.h>

#define AEON_PLUGIN_MAIN_PROC_NAME "aeon_plugin_main"
#define AEON_PLUGIN_FREE_PROC_NAME "aeon_plugin_free"

namespace aeon
{
namespace plugin
{

loaded_plugin::loaded_plugin(const boost::filesystem::path &path) :
    plugin_handle(path),
    aeon_plugin_main_(nullptr),
    aeon_plugin_free_(nullptr),
    interface_(nullptr)
{
    aeon_plugin_main_ = (aeon_plugin_main_proc)
        AEON_GET_PROC_ADDRESS(handle_, AEON_PLUGIN_MAIN_PROC_NAME);

    if (!aeon_plugin_main_)
        throw std::runtime_error("Loading plugin failed: No main proc found.");

    aeon_plugin_free_ = (aeon_plugin_free_proc)
        AEON_GET_PROC_ADDRESS(handle_, AEON_PLUGIN_FREE_PROC_NAME);

    if (!aeon_plugin_free_)
        throw std::runtime_error("Loading plugin failed: No free proc found.");

    interface_ = aeon_plugin_main_();

    if (!interface_)
        throw std::runtime_error(
            "Loading plugin failed: Could not create interface.");

    if (!interface_->on_load())
        throw std::runtime_error(
            "Loading plugin failed: Plugin reported error during load.");
}

loaded_plugin::~loaded_plugin()
{
    aeon_plugin_main_ = nullptr;

    if (interface_)
    {
        bool result = interface_->on_unload();
        aeon_plugin_free_(interface_);

        interface_ = nullptr;
        aeon_plugin_free_ = nullptr;

        if (!result)
            throw std::runtime_error(
                "Loading plugin failed: Plugin reported error during unload.");
    }
}

} // namespace plugin
} // namespace aeon
