#ifndef aeon_curl_exceptions_h__
#define aeon_curl_exceptions_h__

namespace aeon
{
namespace curl
{

class curl_exception : public std::exception {};

class global_init_exception : public curl_exception {};

class easy_init_exception : public curl_exception {};

class easy_wrapper_exception : public curl_exception {};

class url_downloader_exception : public curl_exception {};

} // namespace curl
} // namespace aeon

#endif // aeon_curl_exceptions_h__
