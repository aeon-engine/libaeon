#ifndef aeon_plugin_loader_h__
#define aeon_plugin_loader_h__

namespace aeon
{
namespace plugin
{

class plugin_loader
{
public:
    plugin_loader();
    ~plugin_loader();

    bool load(const std::string &path);
    bool load(const boost::filesystem::path &path);

private:
    std::map<boost::filesystem::path, loaded_plugin_ptr> loaded_plugins_;
};

} // namespace plugin
} // namespace aeon

#endif // aeon_plugin_loader_h__
