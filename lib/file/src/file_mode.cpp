/**
  @file         file_mode.cpp
  @brief        retains the access mode for file descriptor.
  @author       HRYKY
  @version      $Id: file_mode.cpp 360 2014-07-05 06:59:57Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/file/file_mode.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace file
{
namespace
{
} // namespace "anonymous"
} // namespace file
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
hryky::file::Mode::Mode()
	: impl_()
{
}
/**
  @brief copy constructor.
 */
hryky::file::Mode::Mode(this_type const & rhs)
	: hryky_copy_member(impl)
{
}
/**
  @brief move constructor.
 */
hryky::file::Mode::Mode(this_type && rhs)
	: hryky_move_member(impl)
{
}
/**
  @brief destructor.
 */
hryky::file::Mode::~Mode()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::file::Mode::clear()
{
	hryky::clear(this->impl_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::file::Mode::swap(this_type & src)
{
	hryky_swap_member(impl);
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
namespace file
{
namespace
{
} // namespace "anonymous"
} // namespace file
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
