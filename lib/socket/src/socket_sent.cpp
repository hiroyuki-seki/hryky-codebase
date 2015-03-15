/**
  @file     socket_sent.cpp
  @brief    retains the result of send().
  @author   HRYKY
  @version  $Id: socket_sent.cpp 342 2014-03-30 09:41:58Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/socket/socket_sent.h"
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
hryky::socket::Sent::Sent()
	: size_()
	  , valid_()
{
}
/**
  @brief copy constructor.
 */
hryky::socket::Sent::Sent(this_type const & rhs)
	: hryky_copy_member(size)
	  , hryky_copy_member(valid)
{
}
/**
  @brief move constructor.
 */
hryky::socket::Sent::Sent(this_type && rhs)
	: hryky_move_member(size)
	  , hryky_move_member(valid)
{
}
/**
  @brief instantiates as a valid result.
 */
hryky::socket::Sent::Sent(size_t const size)
	: size_(size)
	  , valid_(true)
{
}
/**
  @brief destructor.
 */
hryky::socket::Sent::~Sent()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::socket::Sent::clear()
{
	hryky::clear(this->size_);
	hryky::clear(this->valid_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::socket::Sent::swap(this_type & src)
{
	hryky_swap_member(size);
	hryky_swap_member(valid);
}
/**
  @brief casts to a boolean value.
 */
hryky::socket::Sent::operator bool() const
{
	return this->valid_;
}
/**
  @brief retrieves the size of the sent data.
 */
hryky::size_t hryky::socket::Sent::size() const
{
	return this->size_;
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
