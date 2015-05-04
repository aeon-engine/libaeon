#include <aeon/plugin.h>
#include <plugin/platform.h>

namespace aeon
{
namespace plugin
{

plugin_handle::plugin_handle(const boost::filesystem::path &path) :
    handle_(nullptr)
{
    std::string pathstr = path.string();
    handle_ = AEON_LOAD_LIBRARY(pathstr.c_str());

    if (handle_ == nullptr)
        throw std::runtime_error("Loading plugin failed: Could not load library.");
}

plugin_handle::~plugin_handle()
{
    if (handle_)
        AEON_CLOSE_LIBRARY(handle_);

    handle_ = nullptr;
}

} // namespace plugin
} // namespace aeon
