#ifndef aeon_plugin_loaded_plugin_h__
#define aeon_plugin_loaded_plugin_h__

namespace aeon
{
namespace plugin
{

class plugin_interface;
typedef plugin_interface *(_cdecl * aeon_plugin_main_proc)();
typedef void(_cdecl * aeon_plugin_free_proc)(plugin_interface *);

class loaded_plugin : plugin_handle
{
public:
    loaded_plugin(const boost::filesystem::path &path);
    virtual ~loaded_plugin();

    loaded_plugin(const loaded_plugin &other) = delete;
    loaded_plugin &operator=(loaded_plugin const&) = delete;

    plugin_interface *get_plugin_interface()
    {
        return interface_;
    }

private:
    aeon_plugin_main_proc aeon_plugin_main_;
    aeon_plugin_free_proc aeon_plugin_free_;
    plugin_interface *interface_;
};

typedef std::shared_ptr<loaded_plugin> loaded_plugin_ptr;

} // namespace plugin
} // namespace aeon

#endif // aeon_plugin_loaded_plugin_h__
