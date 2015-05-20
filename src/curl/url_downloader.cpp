#include <aeon/curl.h>

namespace aeon
{
namespace curl
{

url_downloader::url_downloader()
{
    wrapper_ = std::make_shared<easy_wrapper>();
}

url_downloader::~url_downloader()
{
    wrapper_ = nullptr;
}

void url_downloader::download(const std::string &url,
    const std::string &dest_path)
{
    aeon::streams::file_stream f(dest_path, aeon::streams::access_mode::write | aeon::streams::access_mode::truncate);

    if (!f.good())
        throw url_downloader_exception();

    auto func = std::bind(&url_downloader::read_event_, this, std::ref(f),
        std::placeholders::_1, std::placeholders::_2);
    wrapper_->get(url, func);

    f.flush();
}

std::size_t url_downloader::read_event_(aeon::streams::file_stream &dest_stream,
    void *buffer, std::size_t size)
{
    std::size_t result = dest_stream.write((std::uint8_t *) buffer, size);

    if (result != size)
        throw url_downloader_exception();

    return size;
}

} // namespace curl
} // namespace aeon
