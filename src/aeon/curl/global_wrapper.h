#ifndef aeon_curl_global_wrapper_h__
#define aeon_curl_global_wrapper_h__

namespace aeon
{
namespace curl
{

class global_wrapper;
typedef std::shared_ptr<global_wrapper> global_wrapper_ptr;

class global_wrapper : public utility::noncopyable
{
public:
    global_wrapper();
    ~global_wrapper();

    static global_wrapper_ptr get();

protected:
    bool initialized_;
    static std::mutex mutex_;
    static global_wrapper_ptr wrapper_;
};

} // namespace curl
} // namespace aeon

#endif // aeon_curl_global_wrapper_h__
