/**
  @file     win32_handle.cpp
  @brief    retains the HANDLE value.
  @author   HRYKY
  @version  $Id: win32_handle.cpp 363 2014-07-10 10:46:29Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/win32/win32_handle.h"
#include "hryky/swap.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace win32
{
namespace
{
} // namespace "anonymous"
} // namespace win32
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
hryky::win32::Handle::Handle()
	: raw_(INVALID_HANDLE_VALUE)
{
}
/**
  @brief creates an instance from the raw handle.
 */
hryky::win32::Handle::Handle(raw_type const raw)
	: raw_(raw)
{
}
/**
  @brief move constructor.
 */
hryky::win32::Handle::Handle(this_type && rhs)
	: hryky_move_member(raw)
{
	rhs.raw_ = INVALID_HANDLE_VALUE;
}
/**
  @brief destructor.
 */
hryky::win32::Handle::~Handle()
{
	this->clear();
}
/**
  @brief releases the internal resources.
 */
void hryky::win32::Handle::clear()
{
	if (INVALID_HANDLE_VALUE != this->raw_) {
		::CloseHandle(this->raw_);
		this->raw_ = INVALID_HANDLE_VALUE;
	}
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::win32::Handle::swap(this_type & src)
{
	hryky_swap_member(raw);
}
/**
  @brief retrieves the internal raw handle.
 */
HANDLE hryky::win32::Handle::raw() const
{
	return this->raw_;
}
/**
  @brief confirms whether the internal handle is invalid.
 */
bool hryky::win32::Handle::is_null() const
{
	return INVALID_HANDLE_VALUE == this->raw_;
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
// defines functions used in this file
//------------------------------------------------------------------------------
namespace hryky
{
namespace win32
{
namespace
{
} // namespace "anonymous"
} // namespace win32
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
