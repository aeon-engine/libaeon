#ifndef aeon_curl_url_downloader_h__
#define aeon_curl_url_downloader_h__

namespace aeon
{
namespace curl
{

class url_downloader
{
public:
    url_downloader();
    ~url_downloader();

    void download(const std::string &url, const std::string &dest_path);

    std::size_t read_event_(aeon::streams::file_stream &dest_stream, void *buffer, std::size_t size);

    easy_wrapper_ptr wrapper_;
};

} // namespace curl
} // namespace aeon

#endif // aeon_curl_url_downloader_h__
