/**
  @file     socket_common.win32.h
  @brief    The common definition for socket-programming.
  @author   HRYKY
  @version  $Id: socket_common.win32.h 344 2014-04-06 07:41:44Z hryky.private@gmail.com $
 */
#ifndef SOCKET_COMMON_WIN32_H_20140216182111431
#define SOCKET_COMMON_WIN32_H_20140216182111431
#include "hryky/pragma.h"
#pragma hryky_pragma_push_warning
#   pragma hryky_pragma_disable_warning_undef
#   pragma hryky_pragma_disable_warning_sign_conversion
#   pragma hryky_pragma_disable_warning_invalid_macro
#   include <winsock2.h>
#   include <ws2tcpip.h>
#   include <iphlpapi.h>
#pragma hryky_pragma_pop_warning
#pragma comment(lib, "Ws2_32.lib")

#include "hryky/string.h"
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
	typedef int getaddrinfo_error_type;
	typedef SOCKET raw_descriptor_type;
	typedef int raw_error_type;

	raw_descriptor_type const g_invalid_raw_descriptor = INVALID_SOCKET;

	int const g_shut_rdwr = SD_BOTH;
	int const g_shut_rd = SD_RECEIVE;
	int const g_shut_wr = SD_SEND;
	
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
	/// retrieves the last error.
	raw_error_type last_error();

	/// represents the error of getaddrinfo by String<>.
	hryky::String<> describe_getaddrinfo_error(
		getaddrinfo_error_type const error);

	/// represents the last error in Winsock2.
	hryky::String<> describe_last_error();

	/// closes the socket descriptor.
	void close(raw_descriptor_type const src);

	/**
	  confirms whether the last error indicate that the last
	  function is in progress.
	 */
	bool in_progress();

	/**
	  confirms whether the last error indicates which an
	  operation has been already called.
	 */
	bool already();

	/// prevent the socket from blocking.
	bool enable_nonblock(raw_descriptor_type const src);

} // namespace socket
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // SOCKET_COMMON_WIN32_H_20140216182111431
// end of file
