/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2017 Robin Degen
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
#include <cstdint>
#include <cstdlib>
#include <cstddef>
#include <vector>
#include <fstream>
#include <map>
#include <list>
#include <array>
#include <cassert>
#include <cctype>
#include <chrono>
#include <exception>
#include <utility>
#include <string>
#include <sstream>
#include <algorithm>
#include <functional>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <atomic>
#include <future>

/******************************************************************************/
/* Aeon headers                                                               */
/******************************************************************************/
#include <aeon/streams.h>
#include <aeon/utility/noncopyable.h>
#include <aeon/utility/singleton.h>
#include <aeon/utility/string_traits.h>
#include <aeon/utility/configfile.h>
#include <aeon/utility/hexdump.h>
#include <aeon/utility/endianness.h>
#include <aeon/utility/timer.h>
#include <aeon/utility/optional.h>
#include <aeon/utility/linear_map.h>
#include <aeon/utility/variant.h>
#include <aeon/utility/listener_subject.h>
#include <aeon/utility/string.h>
#include <aeon/utility/dispatcher.h>
#include <aeon/utility/signals.h>
#include <aeon/utility/parameters.h>
#include <aeon/utility/parallelizer.h>
#include <aeon/utility/container.h>
#include <aeon/utility/literals.h>
#include <aeon/utility/bitflags.h>
