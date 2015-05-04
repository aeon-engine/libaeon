#ifndef aeon_logger_h__
#define aeon_logger_h__

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

/******************************************************************************/
/* Aeon headers                                                               */
/******************************************************************************/
#include <aeon/streams.h>

#include <aeon/logger/log_level.h>
#include <aeon/logger/log_sink.h>
#include <aeon/logger/base_backend.h>
#include <aeon/logger/simple_backend.h>
#include <aeon/logger/simple_sink_backend.h>
#include <aeon/logger/multithreaded_sink_backend.h>
#include <aeon/logger/logger.h>
#include <aeon/logger/stream_sink.h>
#include <aeon/logger/io_stream_sink.h>

#endif // aeon_logger_h__

