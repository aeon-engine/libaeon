#ifndef aeon_curl_h__
#define aeon_curl_h__

/******************************************************************************/
/* Standard headers                                                           */
/******************************************************************************/
#include <string>
#include <set>
#include <queue>
#include <memory>
#include <utility>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <sstream>
#include <functional>

/******************************************************************************/
/* Curl headers                                                               */
/******************************************************************************/
#include <curl/curl.h>

/******************************************************************************/
/* Aeon headers                                                               */
/******************************************************************************/

#include <aeon/utility.h>
#include <aeon/streams.h>

#define AEON_CURL_DEFAULT_TIMEOUT_MS 10000

#include <aeon/curl/exceptions.h>
#include <aeon/curl/global_wrapper.h>
#include <aeon/curl/easy_wrapper.h>
#include <aeon/curl/url_downloader.h>

#endif // aeon_curl_h__
