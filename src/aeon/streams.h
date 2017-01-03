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
#include <cstring>
#include <vector>
#include <fstream>
#include <array>
#include <iostream>
#include <type_traits>
#include <memory>
#include <string>

/******************************************************************************/
/* Aeon headers                                                               */
/******************************************************************************/
#include <aeon/utility/noncopyable.h>
#include <aeon/platform.h>
#include <aeon/streams/config.h>
#include <aeon/streams/access_mode_mixin.h>
#include <aeon/streams/stream_name_mixin.h>
#include <aeon/streams/stream.h>
#include <aeon/streams/memory_stream.h>
#include <aeon/streams/file_stream.h>
#include <aeon/streams/circular_buffer_stream.h>
#include <aeon/streams/io_stream_colors_mixin.h>
#include <aeon/streams/io_stream.h>
#include <aeon/streams/stream_reader.h>
#include <aeon/streams/stream_writer.h>
