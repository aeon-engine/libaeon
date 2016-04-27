#ifndef aeon_curl_easy_wrapper_h__
#define aeon_curl_easy_wrapper_h__

namespace aeon
{
namespace curl
{

typedef std::function<std::size_t(void *, std::size_t)> easy_wrapper_read_event;
class easy_wrapper : public utility::noncopyable
{
public:
    easy_wrapper();
    ~easy_wrapper();

    void get(const std::string &url, easy_wrapper_read_event on_read, long milliseconds = AEON_CURL_DEFAULT_TIMEOUT_MS);

private:
    static size_t static_read_event_(void *buffer, size_t size, size_t nmemb, easy_wrapper *wrapper);

    CURL *curl_;
    global_wrapper_ptr global_wrapper_;
    easy_wrapper_read_event read_event_;
};

typedef std::shared_ptr<easy_wrapper> easy_wrapper_ptr;

} // namespace curl
} // namespace aeon

#endif // aeon_curl_easy_wrapper_h__
