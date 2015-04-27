#ifndef aeon_streams_h__
#define aeon_streams_h__

/******************************************************************************/
/* Standard headers                                                           */
/******************************************************************************/
#include <cstdint>
#include <cstdlib>
#include <cstddef>
#include <vector>
#include <fstream>
#include <array>

/******************************************************************************/
/* Boost headers                                                              */
/******************************************************************************/
#include <boost/filesystem.hpp>

/******************************************************************************/
/* Aeon headers                                                               */
/******************************************************************************/
#include <aeon/streams/config.h>
#include <aeon/streams/access_mode_mixin.h>
#include <aeon/streams/stream_name_mixin.h>
#include <aeon/streams/stream.h>
#include <aeon/streams/memory_stream.h>
#include <aeon/streams/file_stream.h>
#include <aeon/streams/circular_buffer_stream.h>
#include <aeon/streams/io_stream.h>
#include <aeon/streams/stream_reader.h>
#include <aeon/streams/stream_writer.h>

#endif // aeon_streams_h__
