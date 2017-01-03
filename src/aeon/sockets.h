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
#include <array>
#include <queue>

/******************************************************************************/
/* Boost headers                                                              */
/******************************************************************************/
#include <asio.hpp>

/******************************************************************************/
/* Aeon headers                                                               */
/******************************************************************************/
#include <aeon/streams.h>

#include <aeon/sockets/config.h>
#include <aeon/sockets/tcp_server.h>
#include <aeon/sockets/line_protocol_handler.h>
