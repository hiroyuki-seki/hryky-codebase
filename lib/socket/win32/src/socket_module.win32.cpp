/**
  @file     socket_module.win32.cpp
  @brief    manages all functionalities of socket module.
  @author   HRYKY
  @version  $Id: socket_module.win32.cpp 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/clear.h"
#include "hryky/log/log_definition.h"
#include "hryky/socket/socket_module.win32.h"
#include "hryky/swap.h"
#include "hryky/unique_ptr.h"
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
// static variable
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// function prototype
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
hryky::socket::Module::Module()
	: mempool_()
	  , flags_()
{
	BYTE const version_major = 2u;
	BYTE const version_minor = 2u;
	
	WORD const version = MAKEWORD(version_major, version_minor);
	WSADATA wsa_data;
	int const error = WSAStartup(version, &wsa_data);
	if (0 != error) {
		hryky_log_err(
			"failed to start Winsock2: "
			<< win32::format_error(static_cast<DWORD>(error)));
		return;
	}
	this->flag_.started_ = true;

	if (version_major != LOBYTE(wsa_data.wVersion)
		|| version_minor != HIBYTE(wsa_data.wVersion)) {
		hryky_log_err(
			"The DLL for winsock doesn't support Version "
			<< static_cast<uint16_t>(version_major) << '.'
			<< static_cast<uint16_t>(version_minor));
		return;
	}
	this->flag_.initialized_ = true;
}
/**
  @brief move constructor.
 */
hryky::socket::Module::Module(this_type && rhs)
	: hryky_move_member(mempool)
	  , hryky_move_member(flags)
{
	hryky::clear(this->mempool_);
	hryky::clear(this->flags_);
}
/**
  @brief destructor.
 */
hryky::socket::Module::~Module()
{
	this->clear();
}
/**
  @brief releases the internal resources.
 */
void hryky::socket::Module::clear()
{
	if (this->flag_.started_) {
		WSACleanup();
		this->flag_.started_ = false;
	}
	hryky::clear(this->flags_);
}
/**
  @brief rebuilds the internal resource.
 */
bool hryky::socket::Module::reset()
{
	this->clear();

	return true;
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::socket::Module::swap(this_type & src)
{
	hryky_swap_member(mempool);
	hryky_swap_member(flags);
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// static functions
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
