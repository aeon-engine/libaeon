#include <aeon/curl.h>

namespace aeon
{
namespace curl
{

std::mutex global_wrapper::mutex_;
global_wrapper_ptr global_wrapper::wrapper_;

global_wrapper::global_wrapper()
    : initialized_(false)
{
    if (wrapper_)
        throw global_init_exception();

    CURLcode result = curl_global_init(CURL_GLOBAL_DEFAULT);

    if (result != 0)
        throw global_init_exception();

    initialized_ = true;
}

global_wrapper::~global_wrapper()
{
    if (initialized_)
        curl_global_cleanup();

    initialized_ = false;
}

aeon::curl::global_wrapper_ptr global_wrapper::get()
{
    std::lock_guard<std::mutex> g(mutex_);

    if (!wrapper_)
    {
        // Set to a temporary variable first, since the constructor checks for
        // the value of wrapper_ to prevent multiple instances.
        global_wrapper_ptr w = std::make_shared<global_wrapper>();
        wrapper_ = w;
    }

    return wrapper_;
}

} // namespace curl
} // namespace aeon
