/**
  @file     mempool_ptr.cpp
  @brief    retains the implementation of mempool::Base.
  @author   HRYKY
  @version  $Id: mempool_ptr.cpp 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/mempool/mempool_ptr.h"
#include "hryky/mempool/mempool_global_registry.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace mempool
{
namespace
{
} // namespace "anonymous"
} // namespace mempool
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
  @brief constructs an instance with the implementation.
 */
hryky::mempool::Ptr::Ptr(pointer const ptr)
	: retain_type(ptr)
{
}
/**
  @brief copy constructor.
 */
hryky::mempool::Ptr::Ptr(this_type const & rhs)
	: retain_type(rhs)
{
}
/**
  @brief move constructor.
 */
hryky::mempool::Ptr::Ptr(this_type && rhs)
	: retain_type(::std::move(rhs))
{
}
/**
  @brief destructor.
 */
hryky::mempool::Ptr::~Ptr()
{
}
/**
  @brief assigns a new pointer.
 */
hryky::mempool::Ptr &
hryky::mempool::Ptr::operator=(pointer const ptr)
{
	this->assign(ptr);
	return *this;
}
/**
  @brief default constructor.
 */
hryky::mempool::Ptr::Ptr()
	: retain_type(global::Registry::instance())
{
}
/**
  @brief releases the internal resources.
 */
void hryky::mempool::Ptr::clear()
{
	this->retain_type::assign(global::Registry::instance());
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::mempool::Ptr::swap(this_type & src)
{
	this->retain_type::swap(src);
}
/**
  @brief confirms whether the internal pointer is null.
 */
bool hryky::mempool::Ptr::is_null() const
{
	return hryky_is_null(this->get());
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
namespace mempool
{
namespace
{
} // namespace "anonymous"
} // namespace mempool
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
