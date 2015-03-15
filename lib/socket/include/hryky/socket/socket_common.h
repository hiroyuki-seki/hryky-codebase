/**
  @file     socket_common.h
  @brief    The common definitions for hryky::socket module.
  @author   HRYKY
  @version  $Id: socket_common.h 328 2014-02-24 02:40:42Z hryky.private@gmail.com $
 */
#ifndef SOCKET_COMMON_H_20140223100651088
#define SOCKET_COMMON_H_20140223100651088
#include "hryky/config.h"

#if HRYKY_PLATFORM_WINDOWS
#   include "hryky/socket/socket_common.win32.h"

#elif HRYKY_PLATFORM_POSIX
#   include <sys/types.h>
#   include <sys/sockets.h>
#   include <netdb.h>

#elif HRYKY_USE_BOOST_ASIO
#   include "hryky/boost.h"

#endif
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace socket
{
} // namespace socket
} // namespace hryky
//------------------------------------------------------------------------------
// declares structs
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace socket
{
} // namespace socket
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // SOCKET_COMMON_H_20140223100651088
// end of file
