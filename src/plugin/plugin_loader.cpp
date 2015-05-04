#include <aeon/plugin.h>
#include <plugin/platform.h>

namespace aeon
{
namespace plugin
{

plugin_loader::plugin_loader()
{

}

plugin_loader::~plugin_loader()
{

}

bool plugin_loader::load(const std::string &path)
{
    return load(boost::filesystem::path(path));
}

bool plugin_loader::load(const boost::filesystem::path &path)
{
    boost::filesystem::path cannonical_path = boost::filesystem::canonical(path);
    return false;
}

} // namespace plugin
} // namespace aeon
