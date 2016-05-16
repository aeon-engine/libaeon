/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2016 Robin Degen
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains the property of
 * Robin Degen and its suppliers, if any. The intellectual and technical
 * concepts contained herein are proprietary to Robin Degen and its suppliers
 * and may be covered by U.S. and Foreign Patents, patents in process, and are
 * protected by trade secret or copyright law. Dissemination of this
 * information or reproduction of this material is strictly forbidden unless
 * prior written permission is obtained from Robin Degen.
 */

#pragma once

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
#define CURL_STATICLIB
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
