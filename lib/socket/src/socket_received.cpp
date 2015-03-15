/**
  @file     socket_received.cpp
  @brief    retains the result of recv().
  @author   HRYKY
  @version  $Id: socket_received.cpp 342 2014-03-30 09:41:58Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/socket/socket_received.h"
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
hryky::socket::Received::Received()
	: size_()
	  , valid_()
{
}
/**
  @brief copy constructor.
 */
hryky::socket::Received::Received(this_type const & rhs)
	: hryky_copy_member(size)
	  , hryky_copy_member(valid)
{
}
/**
  @brief move constructor.
 */
hryky::socket::Received::Received(this_type && rhs)
	: hryky_move_member(size)
	  , hryky_move_member(valid)
{
}
/**
  @brief instantiates as a valid result.
 */
hryky::socket::Received::Received(size_t const size)
	: size_(size)
	  , valid_(true)
{
}
/**
  @brief destructor.
 */
hryky::socket::Received::~Received()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::socket::Received::clear()
{
	hryky::clear(this->size_);
	hryky::clear(this->valid_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::socket::Received::swap(this_type & src)
{
	hryky_swap_member(size);
	hryky_swap_member(valid);
}
/**
  @brief casts to a boolean value.
 */
hryky::socket::Received::operator bool() const
{
	return this->valid_;
}
/**
  @brief confirms whether the received result is FIN.
 */
bool hryky::socket::Received::shutdown() const
{
	return this->valid_ && 0u == this->size();
}
/**
  @brief retrieves the size of the sent data.
 */
hryky::size_t hryky::socket::Received::size() const
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
