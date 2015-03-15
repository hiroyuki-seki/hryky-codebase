/**
  @file         mempool_base.cpp
  @brief        interface for dynamic memory allocation.
  @author       HRYKY
  @version      $Id: mempool_base.cpp 360 2014-07-05 06:59:57Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/mempool/mempool_base.h"
#include "hryky/stdint.h"
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
  @brief allocates memory.
 */
void * hryky::mempool::Base::allocate(size_t const size)
{
	return this->allocate_impl(size);
}
/**
  @brief deallocates the memory.
 */
bool hryky::mempool::Base::deallocate(void * const address)
{
	return this->deallocate_impl(address);
}
/**
  @brief retrieves the maximum size of allocate() can be successful.
 */
hryky::size_t
hryky::mempool::Base::allocatable_size() const
{
	return this->allocatable_size_impl();
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
hryky::mempool::Base::Base()
{
}
/**
  @brief move constructor.
 */
hryky::mempool::Base::Base(this_type &&)
{
}
/**
  @brief destructor.
 */
hryky::mempool::Base::~Base()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::mempool::Base::clear()
{
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::mempool::Base::swap(this_type &)
{
}
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
