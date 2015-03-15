/**
  @file     socket_common.win32.cpp
  @brief    The common definitions for hryky::socket module.
  @author   HRYKY
  @version  $Id: socket_common.win32.cpp 344 2014-04-06 07:41:44Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/socket/socket_common.h"
#include "hryky/win32/win32_common.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace socket
{
namespace
{
} // namespace "anonymous"
} // namespace socket
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief retrieves the last error.
 */
hryky::socket::raw_error_type
hryky::socket::last_error()
{
	return WSAGetLastError();
}
/**
  @brief represents the error of getaddrinfo by String<>.
 */
hryky::String<> hryky::socket::describe_getaddrinfo_error(
	getaddrinfo_error_type const error)
{
	return win32::format_error(static_cast<DWORD>(error));
}
/**
  @brief represents the last error in Winsock2.
 */
hryky::String<> hryky::socket::describe_last_error()
{
	return win32::format_error(static_cast<DWORD>(last_error()));
}
/**
  @brief closes the socket descriptor.
 */
void hryky::socket::close(raw_descriptor_type const src)
{
	if (g_invalid_raw_descriptor == src) {
		return;
	}

	closesocket(src);
}
/**
  @brief confirms whether the last error indicate that the last
    function is in progress.
 */
bool hryky::socket::in_progress()
{
	switch (last_error()) {
	case WSAEWOULDBLOCK:
	case WSAEINPROGRESS:
		return true;
	default:
		return false;
	}
}
/**
  @brief confirms whether the last error indicates which an
    operation has been already called.
 */
bool hryky::socket::already()
{
	switch (last_error()) {
	case WSAEALREADY:
		return true;
	default:
		return false;
	}
}
/**
  @brief prevent the socket from blocking.
 */
bool hryky::socket::enable_nonblock(raw_descriptor_type const src)
{
	u_long arg = 1u;
	if (0 != ::ioctlsocket(src, FIONBIO, &arg)) {
		hryky_log_err(
			"failed to make the socket non-block: "
			<< describe_last_error());
		return false;
	}
	return true;
}
//------------------------------------------------------------------------------
// defines static functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace socket
{
namespace
{
} // namespace "anonymous"
} // namespace socket
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
