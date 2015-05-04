#ifndef aeon_plugin_interface_h__
#define aeon_plugin_interface_h__

namespace aeon
{
namespace plugin
{

class plugin_interface
{
public:
    plugin_interface();
    virtual ~plugin_interface();

    virtual bool on_load() = 0;
    virtual bool on_unload() = 0;

    virtual const std::string &name() const = 0;
    virtual const std::string &type() const = 0;
    virtual const std::string &version() const = 0;

    virtual const std::string &author() const = 0;
    virtual const std::string &description() const = 0;
};

} // namespace plugin
} // namespace aeon

#ifdef _MSC_VER
#  define AEON_DLL_EXPORT extern "C" __declspec(dllexport)
#else
#  define AEON_DLL_EXPORT extern "C"
#endif

#define AEON_EXPORT_PLUGIN(name) \
    AEON_DLL_EXPORT aeon::plugin::plugin_interface * _cdecl aeon_plugin_main() \
    { \
        return (aeon::plugin::plugin_interface *) new name(); \
    } \
 \
    AEON_DLL_EXPORT void _cdecl aeon_plugin_free(aeon::plugin::plugin_interface *interface) \
    { \
        delete interface; \
    }

#endif // aeon_plugin_interface_h__
