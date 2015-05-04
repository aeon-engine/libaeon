#ifndef aeon_plugin_handle_h__
#define aeon_plugin_handle_h__

namespace aeon
{
namespace plugin
{

class plugin_handle
{
public:
    plugin_handle(const boost::filesystem::path &path);
    virtual ~plugin_handle();

protected:
    void *handle_;
};

} // namespace plugin
} // namespace aeon

#endif // aeon_plugin_handle_h__
